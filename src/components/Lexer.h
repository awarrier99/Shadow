#ifndef SHADOW_LEXER_H
#define SHADOW_LEXER_H

#include <string>
#include "../core/source/Token.h"


class Lexer {
public:
    Lexer();

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


#endif //SHADOW_LEXER_H
