#ifndef FYE_IR_H
#define FYE_IR_H

#include "Token.h"
#include "Scope.h"


class IRNode {
public:
    IRNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right);
    virtual ~IRNode() = default;

    virtual std::shared_ptr<Data> execute() = 0;

    std::unique_ptr<Token> token;
    std::unique_ptr<IRNode> left;
    std::unique_ptr<IRNode> right;
};

class NumberNode: public IRNode {
public:
    using IRNode::IRNode;

    std::shared_ptr<Data> execute() override;
};

class Scoped {
public:
    explicit Scoped(std::shared_ptr<Scope> &scope);

    std::shared_ptr<Scope> scope;
};

class IdentNode: public IRNode, public Scoped {
public:
    IdentNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right, std::shared_ptr<Scope> &scope);

    std::shared_ptr<Data> execute() override;
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

class AddNode: public CalcNode {
public:
    using CalcNode::CalcNode;

    std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) override;
};

class SubNode: public CalcNode {
public:
    using CalcNode::CalcNode;

    std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) override;
};

class MulNode: public CalcNode {
public:
    using CalcNode::CalcNode;

    std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) override;
};

class DivNode: public CalcNode {
public:
    using CalcNode::CalcNode;

    std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) override;
};

class EqNode: public OpNode, public Scoped {
public:
    EqNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right, std::shared_ptr<Scope> &scope);

    std::shared_ptr<Data> execute() override;
};

class IR {
public:
    explicit IR(std::unique_ptr<IRNode> &root);

    std::unique_ptr<IRNode> root;
};

#endif //FYE_IR_H
