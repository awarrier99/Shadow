#ifndef SHADOW_PARSER_H
#define SHADOW_PARSER_H

#include <string>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include "Lexer.h"
#include "Executor.h"
#include "../core/ast/AST.h"
#include "../util/debug/debug.h"


class Parser {
public:
    explicit Parser(Lexer &lexer);

    void parse(bool repl);

private:
    void consume(const char* type);
    void reject(const char* type);
    astnodelist_ptr parse_func_arguments();
    astnode_ptr parse_expression(token_ptr tok = nullptr, bool arguments = false);
    astnode_ptr parse_var_declaration(const char* &end);
    astnodelist_ptr parse_parameter_list();
    astnode_ptr parse_func_declaration(const char* &end);
    astnode_ptr parse_statement(const char* &end);

    Lexer lexer;
    token_ptr token;
};


#endif //SHADOW_PARSER_H
