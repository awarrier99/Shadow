#ifndef SHADOW_PARSER_H
#define SHADOW_PARSER_H

#include <string>
#include <stack>
#include <queue>
#include <map>
#include "Lexer.h"
#include "Executor.h"
#include "../core/ast/AST.h"
#include "../util/debug/debug.h"


class Parser {
public:
    explicit Parser(Lexer &lexer);

    void parse();

private:
    void consume(const char* type);
    std::unique_ptr<ASTNode> parse_expression();
    std::unique_ptr<ASTNode> parse_declaration();
    std::unique_ptr<ASTNode> parse_statement();

    Lexer lexer;
    std::shared_ptr<Token> token;
};


#endif //SHADOW_PARSER_H
