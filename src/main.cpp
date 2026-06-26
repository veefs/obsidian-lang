#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Tokens.h"
#include "Interpret.h"
#include "Compiler.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "incorrect usage: ./obsidian.exe <filename.obs>";
        return EXIT_FAILURE;
    }

    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<Tokens> tokens;
    std::string line;

    std::cout << "Input File Contents: " << std::endl;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
        Tokenize(line, tokens);
    }
    inputFile.close();

    std::ofstream asmFile("example.asm");

    if (asmFile.is_open()) {
        

        std::cout << std::endl << "Interpreting" << std::endl;


        Interpret(tokens, asmFile);

        std::cout << std::endl << "Compiling" << std::endl;
        asmFile.close();

        Compile();

    } else {
        std::cerr << "Error opening asm output file!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}