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
        
        if (c == '-' && i + 1 < line.size() && line[i + 1] == '>') {
            tokens.push_back(Tokens(Tokens::_RET_OP));
            i++; // consume the '>' too
            continue;
        }

        if (c == '+') {
            tokens.push_back(Tokens(Tokens::_PLUS));
            continue;
        }

        if (c == '-') {
            tokens.push_back(Tokens(Tokens::_MINUS));
            continue;
        }

        if (c == '*') {
            tokens.push_back(Tokens(Tokens::_MULTIPLY));
            continue;
        }

        if (c == '/') {
            tokens.push_back(Tokens(Tokens::_DIVIDE));
            continue;
        }


        char equal = '=';
        if (c == equal) {
            tokens.push_back(Tokens(Tokens::_EQUAL));
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
            } 
            else if (word == "print") {
                tokens.push_back(Tokens(Tokens::_PRINT));
            } else if(word == "let") {
                tokens.push_back(Tokens(Tokens::_LET));
            } else if(word == "int") {
                tokens.push_back(Tokens(Tokens::_INT));
            } else if(word == "const") {
              tokens.push_back(Tokens(Tokens::_CONST));
            } else if(word == "func") {
                tokens.push_back(Tokens(Tokens::_FUNCTION));
            } else {
                tokens.push_back(Tokens(Tokens::_IDENT, word));
            }
        }
    }
}
