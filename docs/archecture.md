

Text -> Tokenizer / Parser (Tokenize.cpp) -> Interepter (Interpret.cpp) -> compiler (compiler.cpp) 


## Tokenizer

Picks up all possible tokens so far:

_RETURN
_STRING
_INT_LIT
_PRINT
_SEMI
and sends them to interepter which tokenizes them again

## Interepter 

Token Types:

push w/

lines.push_back({"Header", "ExternReadme", "extern GetStdHandle"});

- Section <Specificier>, <Section_type>, <value_in_section>

- Header <Specificier>, <header code>

- Program <Specificer>, <program_type>, <value>