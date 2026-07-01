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
        _OPEN_BRACKET,
        _CLOSE_BRACKET,
	_OPEN_PARAM,
	_CLOSE_PARAM,


        // Variable Types
        _STRING,
        _INT_LIT,
        _INT,
        _IDENT,

        // Variable scopes
        _LET,
        _CONST
        
    };

    static const char* tokenName(Tokens::Keywords k) {
    switch (k) {
        case Tokens::_RETURN:        return "_RETURN";
        case Tokens::_PRINT:         return "_PRINT";
        case Tokens::_FUNCTION:      return "_FUNCTION";

        case Tokens::_SEMI:          return "_SEMI";
        case Tokens::_EQUAL:         return "_EQUAL";
        case Tokens::_RET_OP:        return "_RET_OP";
        case Tokens::_PLUS:          return "_PLUS";
        case Tokens::_MINUS:         return "_MINUS";
        case Tokens::_MULTIPLY:      return "_MULTIPLY";
        case Tokens::_DIVIDE:        return "_DIVIDE";
        case Tokens::_OPEN_BRACKET:  return "_OPEN_BRACKET";
        case Tokens::_CLOSE_BRACKET: return "_CLOSE_BRACKET";

        case Tokens::_STRING:        return "_STRING";
        case Tokens::_INT_LIT:       return "_INT_LIT";
        case Tokens::_INT:           return "_INT";
        case Tokens::_IDENT:         return "_IDENT";

        case Tokens::_LET:           return "_LET";
        case Tokens::_CONST:         return "_CONST";
    }
    return "_UNKNOWN";
}

    Tokens(Keywords kw) : keywords(kw), value(0) {}
    Tokens(Keywords kw, int val) : keywords(kw), value(val) {}
    Tokens(Keywords kw, std::string str) : keywords(kw), value(0), strValue(str) {}

    Keywords keywords;
    int value;
    std::string strValue;
};

void Tokenize(std::string line, std::vector<Tokens>& tokens);
