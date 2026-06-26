

Text -> Tokenizer / Parser (Tokenize.cpp) -> Interepter (Interpret.cpp) -> compiler (compiler.cpp) 

First you input the text into your obs file, then you then the entire script onto the file. `.\obsidian.exe <file_name>` the tokenizer will then convert all the lines into things called **Tokens** which represent steps that need to be done by the interepter andcompiler. 

## Tokenizer
Picks up all possible tokens so far:

`_RETURN`
`_STRING`
`_INT_LIT`
`_PRINT`
`_SEMI`

and sends them to interepter which tokenizes them again for an easier style of sorting by interepter token later on.

## Interepter 

Interepter Token Types:

- `Section <Specificier>, <Section_type>, <value_in_section>`

- `Header <Specificier>, <header code>`

- `Program <Specificer>, <program_type>, <value>`

- `Info <Specificer>, <info_require>, <info_value>`

- `Create <specificer>, <specificer_type>, <specificer_value>`

After the interepter breaks everything down into sorting we apply an alogirthim to search by this following order:

1.

`Create, global, global obsidian_program` 
**This is the first token we look for this is because its what declares the start of assembly file without this it wouldn't work**

2. 

`Header, all values`
**We then look for all headers within the InterepterToken vector this is because next in an assembly file is where you would import your external libraries, note that we first remove duplciate elemenets for headers because we only need to include each one a single time**

3.

`Info, section, .text`
**This is the next thing we look for, if this is needed it likely means someone needed to print something or something else, then is 3rd in line of what needs to be created**

4.

`Create, program, obsidian_program`
**This is what is next because we need to create the `obsidian_program:` within the assembly file**

5.

`Program, all types`
**Now we insert all the program code into the program section, remember data can be stored underneeth so this can be next in line.**

6.

`Program, call ExitProcess`
**Now we all our ExitProcess to this note that we have to delete the duplicates for this file as well because you only need to exit the program one time**

7. 

`Section, .bss, written resd 1` (writtetn resd 1 only scope in .bss currently)

**the only thing we need to do here is create the `section .bss` here and then write `written resd 1` under it. **

8. 

`Section, .data, <data_inputs>`

**This will have to be done dynamically but it should be easy, just set the str name to incriment for every data type and then use that later on shouldn't be that bad, and then the string is just whatever you throw into it.**

### Assembly File

Because currently our only real tokens are

`_PRINT` & `_RETURN` im coding around just adjusting for multiple print statemenets, more features will be added later on.


```global obsidian_program

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
```
