#ifndef FYE_LEXER_H
#define FYE_LEXER_H

#include <vector>
#include <string>
#include "Token.h"


class Lexer {
public:
    static std::vector<TokenList*>* lex(std::string* source);

private:
    static TokenList* lex_line(std::string* line, int line_num, int* i);
    static Token* extract_token(std::string* line, int line_num, int i, int* j);
    static Token* extract_number(std::string* line, int i, int* j, char first_ch);
    static Token* extract_string(std::string* line, int i, int* j);
    static Token* extract_ident(std::string* line, int i, int* j, char first_ch);
    static Token* extract_op(char first_ch);
    static Token* extract_sep(char first_ch);
};

TokenType get_type(char ch);


#endif //FYE_LEXER_H
