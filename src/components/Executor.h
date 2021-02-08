#ifndef SHADOW_EXECUTOR_H
#define SHADOW_EXECUTOR_H

#include <iostream>
#include "../core/ast/AST.h"
#include "../core/ir/IR.h"
#include "../core/data/Scope.h"


class Executor {
public:
    void build_ir();
    void execute_ir() const;

    std::unique_ptr<AST> ast;
    std::unique_ptr<IR> ir;
    std::shared_ptr<Scope> global;

private:
    std::unique_ptr<IRNode> build_ir_node(std::unique_ptr<ASTNode> &current);
};

#endif //SHADOW_EXECUTOR_H
