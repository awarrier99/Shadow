#ifndef FYE_LEXER_H
#define FYE_LEXER_H

#include <vector>
#include <string>
#include "Token.h"


class Lexer {
public:
    static std::vector<TokenList> lex(std::string* source);

private:
    static TokenList lex_line(std::string* line);
};


#endif //FYE_LEXER_H
