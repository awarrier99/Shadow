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
    Token(TokenType type, int length, int line, int column, Symbol symbol);

    TokenType type;
    int length;
    int line;
    int column;
    Symbol symbol {nullptr};
};

class TokenList {
public:
    int size();
    void add(Token* token);
    Token* get(int i);

private:
    std::vector<Token*> list;
    int _size;
};


#endif //FYE_TOKEN_H
