#ifndef SHADOW_DEBUG_H
#define SHADOW_DEBUG_H

#include <iostream>
#include <queue>
#include "../../core/ast/AST.h"
#include "../../core/ir/IR.h"


namespace debug {
    void print_token(std::unique_ptr<Token> &token);
    void print_token_list(std::unique_ptr<TokenList> &token_list);
    void print_ast(std::unique_ptr<AST> &ast);
}

#endif //SHADOW_DEBUG_H
