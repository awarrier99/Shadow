#ifndef SHADOW_EXECUTOR_H
#define SHADOW_EXECUTOR_H

#include <iostream>
#include "../core/data/Scope.h"
#include "../core/data/Memory.h"
#include "../core/ast/AST.h"
#include "../core/data/Operations.h"


class Executor;
typedef std::shared_ptr<Data>(Executor::*func_ptr)(std::unique_ptr<ASTNode>&);


class Executor {
public:
    Executor();
    void execute(std::unique_ptr<ASTNode> &root);

private:
    static std::map<const char*, func_ptr> visitor_map;

    std::shared_ptr<Data> visit(std::unique_ptr<ASTNode> &node);
    std::shared_ptr<Data> visit_num(std::unique_ptr<ASTNode> &node);
    std::shared_ptr<Data> visit_str(std::unique_ptr<ASTNode> &node);
    std::shared_ptr<Data> visit_ident(std::unique_ptr<ASTNode> &node);
    std::shared_ptr<Data> visit_vardec(std::unique_ptr<VarDecNode> &node);
    std::shared_ptr<Data> visit_funcdec(std::unique_ptr<FuncDecNode> &node);
    std::shared_ptr<Data> visit_calc(std::unique_ptr<ASTNode> &node);
    std::shared_ptr<Data> visit_assign(std::unique_ptr<ASTNode> &node);

    std::shared_ptr<Scope> scope;
    Memory memory;
};

#endif //SHADOW_EXECUTOR_H
