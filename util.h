#ifndef FYE_UTIL_H
#define FYE_UTIL_H

#include <iostream>
#include <queue>
#include "AST.h"
#include "IR.h"


namespace debug {
    void print_token(Token* token);
    void print_token_list(TokenList* token_list);
    void print_ast(AST* ast);
}

#endif //FYE_UTIL_H
