#include "compiler.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

void Compile() {

    std::cout << "--------------------------------------------" << std::endl;
    std::string filename = "example.asm";
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }


    std::string command =
        "nasm -f win64 example.asm -o example.obj && "
        "gcc example.obj -o example.exe -nostdlib -Wl,--entry=obsidian_program -lkernel32";

    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Compilation failed." << std::endl;
    }
}