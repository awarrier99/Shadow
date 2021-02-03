#ifndef FYE_LEXER_H
#define FYE_LEXER_H

#include <string>
#include "Token.h"


class Lexer {
public:
    TokenList* lex_instruction();

    std::string* instruction;
    int line_num;
    int cursor;
    int offset;

private:
    Token* extract_token();
    Token* extract_number(char first_ch);
    Token* extract_string();
    Token* extract_ident(char first_ch);
    Token* extract_op(char first_ch);
    Token* extract_sep(char first_ch);
};

TokenType get_type(char ch);


#endif //FYE_LEXER_H
