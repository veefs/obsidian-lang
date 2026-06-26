#include "Tokens.h"
#include <cctype>
#include <iostream>

void Tokenize(std::string line, std::vector<Tokens>& tokens) {
    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (std::isspace(c)) continue;

        if (c == ';') {
            tokens.push_back(Tokens(Tokens::_SEMI));
            continue;
        }

        if (c == '"') {
            i++; 
            std::string word;
            while (i < line.size() && line[i] != '"') {
                word += line[i];
                i++;
            }
           
            tokens.push_back(Tokens(Tokens::_STRING, word));
          
            continue;
        }

        if (std::isdigit(c)) {
            std::string number;
            while (i < line.size() && std::isdigit(line[i])) {
                number += line[i];
                i++;
            }
            i--;
            tokens.push_back(Tokens(Tokens::_INT_LIT, std::stoi(number)));
            continue;
        }

        if (std::isalpha(c)) {
            std::string word;
            while (i < line.size() && std::isalnum(line[i])) {
                word += line[i];
                i++;
            }
            i--;

            if (word == "return") {
                tokens.push_back(Tokens(Tokens::_RETURN));
            } else if (word == "print") {
                tokens.push_back(Tokens(Tokens::_PRINT));
            }
        }
    }
}