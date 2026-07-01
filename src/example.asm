global obsidian_program

extern GetStdHandle
extern WriteConsoleA
extern ExitProcess

section .text

test:
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
    mov r8d, 47
    lea r9, [rel written]
    mov qword [rsp+32], 0
    call WriteConsoleA
    add rsp, 40

    call test
    mov ecx, eax 


    sub rsp, 40
    call ExitProcess

section .bss
    written resd 1

section .data
    str0 db "lambda functions and function calls now work!", 13, 10


