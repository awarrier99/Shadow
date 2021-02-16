#ifndef SHADOW_DEBUG_H
#define SHADOW_DEBUG_H

#include <iostream>
#include <queue>
#include <map>
#include "../../core/ast/AST.h"


namespace debug {
    void print_token(token_ptr &token);
    void print_ast_node(astnode_ptr &node);
}

#endif //SHADOW_DEBUG_H
