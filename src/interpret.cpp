#include "Interpret.h"
#include <iostream>
#include <vector>

struct Line { std::string category; std::string label; std::string text; };

std::vector<Line> lines;

void Interpret(const std::vector<Tokens>& tokens, std::ofstream& outputFile) {

    for (const auto& t : tokens) {
        if (t.keywords == Tokens::_STRING) {
            strings.push_back({"str" + std::to_string(strings.size()), t.strValue});
        }
    }

    // Create global obsidian_program
    lines.push_back({"Create", "global", "global obsidian_program"});
    
    		
    lines.push_back({"Create", "RETURN", return_token});
    lines.push_back({"Create", "RETURN", return_token}); 
    lines.push_back({"Create", "RETURN", return_token}); 


    for (size_t i = 0; i < tokens.size(); i++) {
        const auto& t = tokens[i];

        switch (t.keywords) {

          case Tokens::_RETURN: {
		
	    const auto& return_token = tokens[i + 1];
	    lines.push_back({"Program", "RETURN", return_token});


            break;
          }

          case Tokens::_SEMI:
  
            
	    break;

          case Tokens::_INT_LIT:

            break;


          case Tokens::_PRINT: {
            
            const auto& ideal_token = tokens[i + 1];
            lines.push_back({"Header", "extern GetStdHandle", "NA"});
            lines.push_back({"Header", "extern WriteConsoleA", "NA"});
            lines.push_back({"Program", "PRINT", ideal_token});
            lines.push_back({"Section", ".bss", "written resd 1"});
	    lines.push_back({"Section", "data", "str0 db " + '"' + ideal_token + '"' + ", 13,10" });
	    lines.push_back({"Info", "section", ".bss"}); 
            lines.push_back({"Info", "section", ".data"}); 
	    lines.push_back({"Info", "section", ".text"}); 

		
            break;
          }

          case Tokens::_STRING:
            break;
        }
    }

}
