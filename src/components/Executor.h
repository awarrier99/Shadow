#ifndef SHADOW_EXECUTOR_H
#define SHADOW_EXECUTOR_H

#include <iostream>
#include "../core/data/Scope.h"
#include "../core/data/Namespace.h"
#include "../core/ast/AST.h"
#include "../core/data/Operations.h"


class Executor;
typedef data_ptr(Executor::*execfunc_ptr)(astnode_ptr&);
class Executor {
public:
    explicit Executor(bool repl);
    void load_builtins();
    void execute(astnode_ptr &root);

private:
    static std::map<const char*, execfunc_ptr> visitor_map;

    data_ptr visit(astnode_ptr &node);
    data_ptr visit_num(astnode_ptr &node);
    data_ptr visit_str(astnode_ptr &node);
    data_ptr visit_ident(astnode_ptr &node);
    data_ptr visit_vardec(std::unique_ptr<VarDecNode> &node);
    data_ptr visit_funcdec(std::unique_ptr<FuncDecNode> &node);
    data_ptr visit_funccall(astnode_ptr &node);
    data_ptr visit_calc(astnode_ptr &node);
    data_ptr visit_assign(astnode_ptr &node);

    bool repl;
    scope_ptr scope;
    namespace_ptr _namespace;
};

#endif //SHADOW_EXECUTOR_H
