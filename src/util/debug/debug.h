#ifndef SHADOW_DEBUG_H
#define SHADOW_DEBUG_H

#include <iostream>
#include <queue>
#include <map>
#include "../../core/ast/AST.h"


namespace debug {
    void print_token(std::shared_ptr<Token> &token);
    void print_ast_node(std::unique_ptr<ASTNode> &node);
}

#endif //SHADOW_DEBUG_H
