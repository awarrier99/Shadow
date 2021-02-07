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
    Token(TokenType type, std::unique_ptr<Symbol> symbol);

    TokenType type;
    int line;
    int column;
    std::unique_ptr<Symbol> symbol;
};

class TokenList : public std::vector<std::unique_ptr<Token>> {};


#endif //FYE_TOKEN_H
