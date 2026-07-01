#pragma once
#include <string>
#include <vector>

class Tokens {
public:
    enum Keywords {

        // Functions
        _RETURN,
        _PRINT,
        _FUNCTION,

        //Opperators
        _SEMI,
        _EQUAL,
        _RET_OP,
        _PLUS,
        _MINUS,
        _MULTIPLY,
        _DIVIDE,

        // Variable Types
        _STRING,
        _INT_LIT,
        _INT,
        _IDENT,

        // Variable scopes
        _LET,
        _CONST
        
    };

    Tokens(Keywords kw) : keywords(kw), value(0) {}
    Tokens(Keywords kw, int val) : keywords(kw), value(val) {}
    Tokens(Keywords kw, std::string str) : keywords(kw), value(0), strValue(str) {}

    Keywords keywords;
    int value;
    std::string strValue;
};

void Tokenize(std::string line, std::vector<Tokens>& tokens);
