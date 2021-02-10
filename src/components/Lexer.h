#ifndef SHADOW_LEXER_H
#define SHADOW_LEXER_H

#include <string>
#include <map>
#include <set>
#include "../core/source/Token.h"


class Lexer {
public:
    explicit Lexer(std::istream* source);

    std::shared_ptr<Token> extract_token();

private:
    void read();
    char peek();
    std::shared_ptr<Token> extract_number(bool period_flag);
    std::shared_ptr<Token> extract_string();
    std::shared_ptr<Token> extract_ident();
    std::shared_ptr<Token> extract_op();
    std::shared_ptr<Token> extract_sep();

    std::istream* source;
    char ch = '\0';
    int line_num;
    int cursor;
    std::set<char> operators;
    std::map<char, const char*> separators;
    char _next = '\0';
};


#endif //SHADOW_LEXER_H
