#include "Interpret.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

// ---------------------------------------------------------------------------
// Interpreter Token (docs/archecture.md):
//
//   Section <Specifier>, <Section_type>,  <value_in_section>
//   Header  <Specifier>, <header code>
//   Program <Specifier>, <program_type>,  <value>
//   Info    <Specifier>, <info_require>,  <info_value>
//   Create  <Specifier>, <specifier_type>,<specifier_value>
//
// All five shapes reuse one flat struct - we just read whichever fields
// matter for a given "category".
// ---------------------------------------------------------------------------
struct Line {
    std::string category; // Section | Header | Program | Info | Create
    std::string label;    // the "specifier" / sub-type
    std::string text;     // the value / emitted code
};

namespace {

// One WriteConsoleA call, with the CRLF byte count baked in.
std::string buildPrintBlock(const std::string& strValue, const std::string& label, int byteCount) {
    return
        "    ; print \"" + strValue + "\"\n"
        "    sub rsp, 40\n"
        "    mov ecx, -11              ; STD_OUTPUT_HANDLE\n"
        "    call GetStdHandle\n"
        "    mov rcx, rax\n"
        "    lea rdx, [rel " + label + "]\n"
        "    mov r8d, " + std::to_string(byteCount) +
            "                ; \"" + strValue + "\" + CRLF = " + std::to_string(byteCount) + " bytes\n"
        "    lea r9, [rel written]\n"
        "    mov qword [rsp+32], 0\n"
        "    call WriteConsoleA\n"
        "    add rsp, 40";
}

// return's register setup + the ExitProcess call are built as ONE block on
// purpose - see the comment near sawReturn below for why.
std::string buildExitBlock(int code) {
    return
        "    ; return " + std::to_string(code) + "\n"
        "    sub rsp, 40\n"
        "    mov ecx, " + std::to_string(code) + "\n"
        "    call ExitProcess";
}

} // namespace

void Interpret(const std::vector<Tokens>& tokens, std::ofstream& outputFile) {

    std::vector<Line> lines;

    struct StrLiteral { std::string label; std::string text; };
    std::vector<StrLiteral> dataStrings;

    bool sawReturn  = false;
    int  returnCode = 0; // default exit code if `return` is never written

    // ---- Pass 1: tokens -> IR ---------------------------------------------

    // Steps 1, 3, 4 are unconditional right now - every program gets a
    // global directive, a .text section, and the obsidian_program label.
    lines.push_back({"Create", "global",  "global obsidian_program"});
    lines.push_back({"Create", "program", "obsidian_program"});
    lines.push_back({"Info",   "section", ".text"});

    for (size_t i = 0; i < tokens.size(); i++) {
        const auto& t = tokens[i];

        switch (t.keywords) {

            case Tokens::_RETURN: {
                if (i + 1 >= tokens.size() || tokens[i + 1].keywords != Tokens::_INT_LIT) {
                    std::cerr << "Interpret: 'return' must be followed by an integer literal\n";
                    break;
                }
                // No branching exists yet, so whichever `return` is
                // lexically last is the one that actually wins at runtime -
                // just remember the value, the real exit code/call is
                // emitted once at the very end (see sawReturn below).
                returnCode = tokens[i + 1].value;
                sawReturn  = true;
                lines.push_back({"Header", "extern ExitProcess", "NA"});
                i++; // consume the int literal we just looked ahead at
                break;
            }

            case Tokens::_PRINT: {
                if (i + 1 >= tokens.size() || tokens[i + 1].keywords != Tokens::_STRING) {
                    std::cerr << "Interpret: 'print' must be followed by a string literal\n";
                    break;
                }
                const std::string& strValue = tokens[i + 1].strValue;

                std::string label = "str" + std::to_string(dataStrings.size());
                dataStrings.push_back({label, strValue});

                int byteCount = static_cast<int>(strValue.size()) + 2; // + CRLF (13,10)

                lines.push_back({"Header",  "extern GetStdHandle",  "NA"});
                lines.push_back({"Header",  "extern WriteConsoleA", "NA"});
                lines.push_back({"Program", "PRINT", buildPrintBlock(strValue, label, byteCount)});
                lines.push_back({"Section", ".bss",  "written resd 1"});

                i++; // consume the string literal we just looked ahead at
                break;
            }

            case Tokens::_SEMI:
            case Tokens::_INT_LIT:
                break; // pure separator / already consumed via lookahead

            case Tokens::_STRING:
                std::cout << "STRING(" << t.strValue << ") - not attached to a statement, ignored\n";
                break;
        }
    }

    // A program always has to exit somehow. If the source never wrote an
    // explicit `return`, fall back to `return 0` instead of falling off
    // the end of .text into .bss/.data.
    if (!sawReturn) {
        lines.push_back({"Header", "extern ExitProcess", "NA"});
    }

    // Step 6: the exit sequence is exactly one block, always emitted last.
    // It's built fresh here (rather than at the `return` token's source
    // position) so that any print statements written *after* a `return`
    // can't clobber ecx before ExitProcess actually runs.
    lines.push_back({"Program", "EXIT", buildExitBlock(returnCode)});

    for (const auto& s : dataStrings) {
        lines.push_back({"Section", ".data", s.label + " db \"" + s.text + "\", 13, 10"});
    }

    // ---- Pass 2: IR -> assembly, fixed order from docs/archecture.md -----

    // 1. Create, global, global obsidian_program
    for (const auto& l : lines) {
        if (l.category == "Create" && l.label == "global") {
            outputFile << l.text << "\n\n";
            break;
        }
    }

    // 2. Header, all values 
    {
        std::unordered_set<std::string> seen;
        for (const auto& l : lines) {
            if (l.category == "Header" && seen.insert(l.label).second) {
                outputFile << l.label << "\n";
            }
        }
        outputFile << "\n";
    }

    // 3. Info, section, .text
    for (const auto& l : lines) {
        if (l.category == "Info" && l.label == "section" && l.text == ".text") {
            outputFile << "section " << l.text << "\n";
            break;
        }
    }

    // 4. Create, program, obsidian_program
    for (const auto& l : lines) {
        if (l.category == "Create" && l.label == "program") {
            outputFile << l.text << ":\n";
            break;
        }
    }

    // 5 & 6. Program, all types
    {
        bool first = true;
        for (const auto& l : lines) {
            if (l.category != "Program" || l.label == "EXIT") continue;
            if (!first) outputFile << "\n";
            outputFile << l.text << "\n";
            first = false;
        }
        for (const auto& l : lines) {
            if (l.category == "Program" && l.label == "EXIT") {
                if (!first) outputFile << "\n";
                outputFile << l.text << "\n";
            }
        }
        outputFile << "\n";
    }

    // 7. Section, .bss, written resd 1 
    {
        bool wroteHeader = false;
        std::unordered_set<std::string> seen;
        for (const auto& l : lines) {
            if (l.category != "Section" || l.label != ".bss") continue;
            if (!seen.insert(l.text).second) continue;
            if (!wroteHeader) { outputFile << "section .bss\n"; wroteHeader = true; }
            outputFile << "    " << l.text << "\n";
        }
        if (wroteHeader) outputFile << "\n";
    }

    // 8. Section, .data, <data_inputs> 
    {
        bool wroteHeader = false;
        for (const auto& l : lines) {
            if (l.category != "Section" || l.label != ".data") continue;
            if (!wroteHeader) { outputFile << "section .data\n"; wroteHeader = true; }
            outputFile << "    " << l.text << "\n";
        }
    }
}
