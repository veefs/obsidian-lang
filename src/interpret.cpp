#include "Interpret.h"
#include <iostream>
#include <vector>

struct StringLit { std::string label; std::string value; };

std::vector<StringLit> strings;

void Interpret(const std::vector<Tokens>& tokens, std::ofstream& outputFile) {

    // pass 1: collect every string literal, give each a label
    for (const auto& t : tokens) {
        if (t.keywords == Tokens::_STRING) {
            strings.push_back({"str" + std::to_string(strings.size()), t.strValue});
        }
    }

    outputFile << "extern GetStdHandle\n";
    outputFile << "extern WriteConsoleA\n";
    outputFile << "extern ExitProcess\n";

    // pass 2: emit instructions
    size_t strIdx = 0;
    for (size_t i = 0; i < tokens.size(); i++) {
        const auto& t = tokens[i];

        switch (t.keywords) {

          case Tokens::_RETURN: {
            int code = tokens[i + 1].value;
            std::cout << "_RETURN(" << code << ")" << std::endl;
            outputFile << "    sub rsp, 32\n";
            outputFile << "    mov ecx, " << code << "\n";
            outputFile << "    call ExitProcess\n";
            break;
          }

          case Tokens::_SEMI:
            std::cout << "_SEMI" << std::endl;
            break;

          case Tokens::_INT_LIT:
            std::cout << "INT LIT(" << t.value << ")" << std::endl;
            break;

          case Tokens::_PRINT: {
            const auto& lit = strings[strIdx++];
            std::cout << "_PRINT -> " << lit.label << std::endl;
            outputFile << "    sub rsp, 40\n";
            outputFile << "    mov ecx, -11\n";
            outputFile << "    call GetStdHandle\n";
            outputFile << "    mov rcx, rax\n";
            outputFile << "    lea rdx, [rel " << lit.label << "]\n";
            outputFile << "    mov r8d, " << (lit.value.size() + 2) << "\n";
            outputFile << "    lea r9, [rel written]\n";
            outputFile << "    mov qword [rsp+32], 0\n";
            outputFile << "    call WriteConsoleA\n";
            outputFile << "    add rsp, 40\n";
            break;
          }

          case Tokens::_STRING:
            std::cout << "STRING(" << t.strValue << ")" << std::endl;
            break;
        }
    }

    // data emitted last, from what pass 1 collected
    outputFile << "section .bss\n";
    outputFile << "    written resd 1\n";
    outputFile << "section .data\n";
    for (const auto& s : strings) {
        outputFile << "    " << s.label << " db \"" << s.value << "\", 13, 10\n";
    }
}
