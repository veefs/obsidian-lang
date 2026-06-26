global obsidian_program

extern GetStdHandle
extern WriteConsoleA
extern ExitProcess

section .text
obsidian_program:
    ; print "test"
    sub rsp, 40
    mov ecx, -11              ; STD_OUTPUT_HANDLE
    call GetStdHandle
    mov rcx, rax
    lea rdx, [rel str0]
    mov r8d, 6                 ; "test" + CRLF = 6 bytes
    lea r9, [rel written]
    mov qword [rsp+32], 0
    call WriteConsoleA
    add rsp, 40

    ; print "hello"
    sub rsp, 40
    mov ecx, -11
    call GetStdHandle
    mov rcx, rax
    lea rdx, [rel str1]
    mov r8d, 7                 ; "hello" + CRLF = 7 bytes
    lea r9, [rel written]
    mov qword [rsp+32], 0
    call WriteConsoleA
    add rsp, 40

    ; return 12
    sub rsp, 40
    mov ecx, 12
    call ExitProcess

section .bss
    written resd 1

section .data
    str0 db "test", 13, 10
    str1 db "hello", 13, 10
