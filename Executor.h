#ifndef FYE_EXECUTOR_H
#define FYE_EXECUTOR_H

#include <iostream>
#include "AST.h"
#include "IR.h"


class Executor {
public:
    void build_ir();
    void execute_ir() const;

    AST* ast;
    IR* ir;
};

#endif //FYE_EXECUTOR_H
