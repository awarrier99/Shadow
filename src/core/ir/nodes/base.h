#ifndef SHADOW_BASE_H
#define SHADOW_BASE_H

#include "../../source/Token.h"
#include "../../data/Scope.h"


class IRNode {
public:
    IRNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right);
    virtual ~IRNode() = default;

    virtual std::shared_ptr<Data> execute() = 0;

    std::unique_ptr<Token> token;
    std::unique_ptr<IRNode> left;
    std::unique_ptr<IRNode> right;
};

class Scoped {
public:
    explicit Scoped(std::shared_ptr<Scope> &scope);

    std::shared_ptr<Scope> scope;
};

class OpNode: virtual public IRNode {
public:
    using IRNode::IRNode;
};

class CalcNode: public OpNode {
public:
    using OpNode::OpNode;

    virtual std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) = 0;
    std::shared_ptr<Data> execute() override;
};

#endif //SHADOW_BASE_H
