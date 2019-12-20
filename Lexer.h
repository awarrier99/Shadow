#ifndef FYE_LEXER_H
#define FYE_LEXER_H

#include <vector>
#include <string>
#include "Token.h"


class Lexer {
public:
    static std::vector<TokenList*>* lex(std::string* source);

private:
    static TokenList* lex_line(std::string* line);
    static Token* extract_token(std::string* line, int* i);
    static Token* extract_number(std::string* line, int* i, char first);
};

TokenType get_type(char ch);


#endif //FYE_LEXER_H
