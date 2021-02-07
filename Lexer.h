#ifndef FYE_LEXER_H
#define FYE_LEXER_H

#include <string>
#include "Token.h"


class Lexer {
public:
    std::unique_ptr<TokenList> lex_instruction();

    std::unique_ptr<std::string> instruction;
    int line_num;
    int cursor;
    int offset;

private:
    std::unique_ptr<Token> extract_token();
    std::unique_ptr<Token> extract_number(char first_ch);
    std::unique_ptr<Token> extract_string();
    std::unique_ptr<Token> extract_ident(char first_ch);
    std::unique_ptr<Token> extract_op(char first_ch);
    std::unique_ptr<Token> extract_sep(char first_ch);
};

TokenType get_type(char ch);


#endif //FYE_LEXER_H
