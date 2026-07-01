Run as `.\obsidian.exe <file_name>`. The tokenizer scans the source into a flat token stream. The interpreter walks that stream once to build an IR (a flat, tagged struct — see `Line` in `Interpret.cpp`), then walks the IR a second time, in a fixed order, to emit NASM x64 assembly. The compiler shells out to `nasm` + `gcc` to assemble and link the output into a `.exe`.

## IR shapes

All five reuse one flat `Line` struct — only the relevant fields get read per category.

- `Section <Specifier>, <section_type>, <value>`
- `Header  <Specifier>, <header_code>`
- `Function <Specifier>, <function_name>, <function_code>`
- `Program <Specifier>, <program_type>, <value>`
- `Info    <Specifier>, <info_require>, <info_value>`
- `Create  <Specifier>, <specifier_type>, <specifier_value>`

## Emit order (pass 2)

1. **`Create, global`** — `global obsidian_program`, always first; nothing else is valid NASM without it.
2. **`Header`, all values** — extern declarations (`GetStdHandle`, `WriteConsoleA`, `ExitProcess`, etc). Deduplicated, since each only needs to be declared once.
3. **`Info, section, .text`** — opens the `.text` section.
4. **`Function`, all entries** — every user-defined function body gets its own label + instructions, emitted before the entry point.
5. **`Create, program`** — writes the `obsidian_program:` entry label.
6. **`Program`, all types except `EXIT`** — the entry point's own instructions (print calls, etc).
7. **`Program, EXIT`** — the exit sequence, always emitted last regardless of source order, so later `print` calls can't clobber `ecx`/`eax` before the process actually exits.
8. **`Section, .bss`** — currently only `written resd 1`, deduplicated.
9. **`Section, .data`** — string literals, one auto-incrementing label (`str0`, `str1`, ...) per string.
10. **`Section, .rdata`** — `const` values, deduplicated by label.

## Example output

Source:
```obsidian
print "test";
func add() -> int { 2 + 2 };
return add();
```

Emits:
```nasm
global obsidian_program

extern GetStdHandle
extern WriteConsoleA
extern ExitProcess

section .text

add:
    mov eax, 2
    mov ebx, 2
    add eax, ebx
    ret

obsidian_program:
    sub rsp, 40
    mov ecx, -11
    call GetStdHandle
    mov rcx, rax
    lea rdx, [rel str0]
    mov r8d, 6
    lea r9, [rel written]
    mov qword [rsp+32], 0
    call WriteConsoleA
    add rsp, 40

    call add
    mov ecx, eax
    sub rsp, 40
    call ExitProcess

section .bss
    written resd 1

section .data
    str0 db "test", 13, 10
```

## Current gaps

- Function calls in `return` only support calling a previously-defined function by name — no expressions combining a call with other operators.
- Expression evaluation (`handleLambda`) is a flat left-to-right fold, no operator precedence.
- `_LET` is tokenized but not wired into codegen.
- No control flow.