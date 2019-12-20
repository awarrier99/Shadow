#ifndef FYE_TOKEN_H
#define FYE_TOKEN_H


#include <vector>

enum TokenType {
    NUMBER,
    STRING,
    IDENT,
    OP,
    SEP
};

class Token {
    TokenType type;
    int length;
};

class TokenList {
public:
    int size();

private:
    std::vector<Token> list;
    int _size;
};


#endif //FYE_TOKEN_H
