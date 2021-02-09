#ifndef SHADOW_TOKEN_H
#define SHADOW_TOKEN_H

#include <vector>
#include <string>
#include <iostream>


class TokenType {
public:
    inline static const char* NUMBER = "NUMBER";
    inline static const char* STRING = "STRING";
    inline static const char* IDENT = "IDENT";
    inline static const char* CONST = "CONST";
    inline static const char* DEF = "DEF";
    inline static const char* PLUS = "PLUS";
    inline static const char* PLUSEQ = "PLUSEQ";
    inline static const char* MINUS = "MINUS";
    inline static const char* MINUSEQ = "MINUSEQ";
    inline static const char* MUL = "MUL";
    inline static const char* MULEQ = "MULEQ";
    inline static const char* DIV = "DIV";
    inline static const char* DIVEQ = "DIVEQ";
    inline static const char* EXP = "EXP";
    inline static const char* EXPEQ = "EXPEQ";
    inline static const char* MOD = "MOD";
    inline static const char* MODEQ = "MODEQ";
    inline static const char* EQ = "EQ";
    inline static const char* EQEQ = "EQEQ";
    inline static const char* LPAREN = "LPAREN";
    inline static const char* RPAREN = "RPAREN";
    inline static const char* SEMI = "SEMI";
    inline static const char* COMMA = "COMMA";
    inline static const char* LBRACKET = "LBRACKET";
    inline static const char* RBRACKET = "RBRACKET";
    inline static const char* LBRACE = "LBRACE";
    inline static const char* RBRACE = "RBRACE";
    inline static const char* INVALID = "INVALID";
    inline static const char* FEOF = "FEOF";
};

class Token {
public:
    Token(const char* type, std::unique_ptr<std::string> &lexeme);

    const char* type;
    int line;
    int column;
    std::unique_ptr<std::string> lexeme;
};

class TokenList : public std::vector<std::unique_ptr<Token>> {};


#endif //SHADOW_TOKEN_H
