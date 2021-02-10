#ifndef SHADOW_DEBUG_H
#define SHADOW_DEBUG_H

#include <iostream>
#include <queue>
#include <map>
#include "../../core/ast/AST.h"


namespace debug {
    void print_token(std::shared_ptr<Token> &token);
//    void print_ast(std::unique_ptr<ASTNode> &ast);
}

#endif //SHADOW_DEBUG_H
