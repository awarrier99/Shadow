#ifndef FYE_EXECUTOR_H
#define FYE_EXECUTOR_H

#include <iostream>
#include "AST.h"
#include "IR.h"
#include "Scope.h"


class Executor {
public:
    void build_ir();
    void execute_ir() const;

    AST* ast;
    IR* ir;
    Scope* global;

private:
    IRNode* build_ir_node(ASTNode* current);
};

#endif //FYE_EXECUTOR_H
