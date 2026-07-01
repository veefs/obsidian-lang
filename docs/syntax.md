# Obsidian Lang — Syntax Reference

## Tokens

### Keywords
- `_FUNCTION` — declares a function
- `_RETURN` — returns from a function / exits the program
- `_PRINT` — prints a string
- `_LET` — mutable variable binding (tokenized, not yet wired to codegen)
- `_CONST` — immutable variable binding

### Types
- `_INT` — the `int` type keyword
- `_STRING` — string literal
- `_INT_LIT` — integer literal
- `_IDENT` — identifier (variable/function names)

### Operators
- `_EQUAL` — `=`
- `_RET_OP` — `->` (return type annotation)
- `_PLUS` — `+`
- `_MINUS` — `-`
- `_MULTIPLY` — `*`
- `_DIVIDE` — `/`

### Grouping
- `_OPEN_PARAM` / `_CLOSE_PARAM` — `(` `)`
- `_OPEN_BRACKET` / `_CLOSE_BRACKET` — `{` `}`

### Terminators
- `_SEMI` — `;`

## Syntax examples

```obsidian
print "hello";

const int x = 5;

func test() -> int { 2 + 2 };

return test();
```

## Known limitations
- No operator precedence — expressions evaluate strictly left to right
- Expression operands must be int literals (`_IDENT` operands not yet supported)
- No control flow (`if`/`else`, loops)
- Function bodies support a single expression, not multiple statements