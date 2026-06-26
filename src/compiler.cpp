#include "compiler.h"
#include <cstdlib>
#include <string>
#include <iostream>

void Compile() {
    std::string command =
        "nasm -f win64 example.asm -o example.obj && "
        "gcc example.obj -o example.exe -nostdlib -Wl,--entry=obsidian_program";

    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Compilation failed." << std::endl;
    }
}