global obsidian_program
section .text
obsidian_program:
extern GetStdHandle
extern WriteConsoleA
extern ExitProcess
    sub rsp, 32
    mov ecx, 12
    call ExitProcess
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
section .bss
    written resd 1
section .data
    str0 db "test", 13, 10
