#include "Lexer.h"


std::vector<TokenList> Lexer::lex(std::string* source) {
    std::string line;
    return std::vector<TokenList> { lex_line(&line) };
}

TokenList Lexer::lex_line(std::string* line) {
    return TokenList {};
}