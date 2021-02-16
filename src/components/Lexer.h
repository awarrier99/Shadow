#ifndef SHADOW_LEXER_H
#define SHADOW_LEXER_H

#include <stdexcept>
#include <string>
#include <map>
#include <set>
#include "../core/data/Token.h"


class Lexer {
public:
    explicit Lexer(std::istream* source);

    token_ptr extract_token();

    char ch = '\0';

private:
    void read();
    char peek();
    token_ptr extract_number(bool period_flag);
    token_ptr extract_string();
    token_ptr extract_ident();
    token_ptr extract_op();
    token_ptr extract_sep();

    std::istream* source;
    int line_num;
    int cursor;
    std::set<char> operators;
    std::map<char, const char*> separators;
    char _next = '\0';
};


#endif //SHADOW_LEXER_H
