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

    std::unique_ptr<AST> ast;
    std::unique_ptr<IR> ir;
    std::shared_ptr<Scope> global;

private:
    std::unique_ptr<IRNode> build_ir_node(std::unique_ptr<ASTNode> &current);
};

#endif //FYE_EXECUTOR_H
