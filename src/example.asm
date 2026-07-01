global obsidian_program

extern GetStdHandle
extern WriteConsoleA
extern ExitProcess

section .text

test:
    mov eax, 2
    ret 

obsidian_program:
    sub rsp, 40
    mov ecx, -11
    call GetStdHandle
    mov rcx, rax
    lea rdx, [rel str0]
    mov r8d, 51
    lea r9, [rel written]
    mov qword [rsp+32], 0
    call WriteConsoleA
    add rsp, 40

    sub rsp, 40
    mov ecx, -11
    call GetStdHandle
    mov rcx, rax
    lea rdx, [rel str1]
    mov r8d, 14
    lea r9, [rel written]
    mov qword [rsp+32], 0
    call WriteConsoleA
    add rsp, 40

    sub rsp, 40
    mov ecx, 12
    call ExitProcess

section .bss
    written resd 1

section .data
    str0 db "Hello everyone this is the obsidian lang release!", 13, 10
    str1 db "Please enjoy", 13, 10


