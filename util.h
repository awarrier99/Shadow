#ifndef FYE_UTIL_H
#define FYE_UTIL_H

#include <iostream>
#include <queue>
#include "AST.h"
#include "IR.h"


namespace debug {
    void print_token(std::unique_ptr<Token> &token);
    void print_token_list(std::unique_ptr<TokenList> &token_list);
    void print_ast(std::unique_ptr<AST> &ast);
}

#endif //FYE_UTIL_H
