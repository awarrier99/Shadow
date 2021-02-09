#ifndef SHADOW_PARSER_H
#define SHADOW_PARSER_H

#include <string>
#include <stack>
#include <queue>
#include <map>
#include "Lexer.h"
#include "../core/ast/AST.h"
#include "../util/debug/debug.h"


class Parser {
public:
    explicit Parser(Lexer lexer);

    std::unique_ptr<AST> parse();

private:
    void consume(const char* type);

    Lexer lexer;
    std::unique_ptr<Token> token;
};


#endif //SHADOW_PARSER_H
