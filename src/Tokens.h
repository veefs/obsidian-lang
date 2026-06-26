#pragma once
#include <string>
#include <vector>

class Tokens {
public:
    enum Keywords {
        _RETURN,
        _PRINT,
        _SEMI,
        _STRING,
        _INT_LIT
    };

    Tokens(Keywords kw) : keywords(kw), value(0) {}
    Tokens(Keywords kw, int val) : keywords(kw), value(val) {}
    Tokens(Keywords kw, std::string str) : keywords(kw), value(0), strValue(str) {}

    Keywords keywords;
    int value;
    std::string strValue;
};

void Tokenize(std::string line, std::vector<Tokens>& tokens);