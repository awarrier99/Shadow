#ifndef FYE_TOKEN_H
#define FYE_TOKEN_H

#include <vector>


enum TokenType {
    NUMBER,
    STRING,
    IDENT,
    OP,
    SEP,
    INVALID
};

class Symbol {
public:
    explicit Symbol(void* data);

    void* data;
};

class Token {
public:
    Token(TokenType type, int length, int line, int column, Symbol* symbol);

    TokenType type;
    int length;
    int line;
    int column;
    Symbol* symbol;
};

class TokenList : public std::vector<Token*> {};


#endif //FYE_TOKEN_H
