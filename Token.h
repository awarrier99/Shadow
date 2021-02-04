#ifndef FYE_TOKEN_H
#define FYE_TOKEN_H

#include <vector>
#include <string>
#include <iostream>
#include "Symbol.h"


enum TokenType {
    NUMBER,
    STRING,
    IDENT,
    OP,
    SEP,
    INVALID
};

class Token {
public:
    Token(TokenType type, Symbol* symbol);
//    ~Token();

    TokenType type;
    int line;
    int column;
    Symbol* symbol;
};

class TokenList : public std::vector<Token*> {
public:
    ~TokenList();
};


#endif //FYE_TOKEN_H
