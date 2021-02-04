#ifndef FYE_IR_H
#define FYE_IR_H

#include "Token.h"
#include "Scope.h"


class IRNode {
public:
    IRNode(Token* token, IRNode* left, IRNode* right);
    virtual ~IRNode() = 0;

    virtual Data* execute() = 0;

    Token* token;
    IRNode* left;
    IRNode* right;
};

class NumberNode: public IRNode {
public:
    using IRNode::IRNode;
    ~NumberNode() override;

    Data* execute() override;
};

class Scoped {
public:
    Scope* scope;
};

class IdentNode: public IRNode, public Scoped {
public:
    using IRNode::IRNode;
    ~IdentNode() override;

    Data* execute() override;
};

class OpNode: virtual public IRNode {
public:
    using IRNode::IRNode;
};

class CalcNode: public OpNode {
public:
    using OpNode::OpNode;

    virtual Data* compute(Data* a, Data* b) = 0;
    Data* execute() override;
};

class AddNode: public CalcNode {
public:
    using CalcNode::CalcNode;
    ~AddNode() override;

    Data* compute(Data* a, Data* b) override;
};

class SubNode: public CalcNode {
public:
    using CalcNode::CalcNode;
    ~SubNode() override;

    Data* compute(Data* a, Data* b) override;
};

class MulNode: public CalcNode {
public:
    using CalcNode::CalcNode;
    ~MulNode() override;

    Data* compute(Data* a, Data* b) override;
};

class DivNode: public CalcNode {
public:
    using CalcNode::CalcNode;
    ~DivNode() override;

    Data* compute(Data* a, Data* b) override;
};

class EqNode: public OpNode, public Scoped {
public:
    using OpNode::OpNode;
    ~EqNode() override;

    Data* execute() override;
};

class IR {
public:
    explicit IR(IRNode* root);
    ~IR();

    IRNode* root;
};

#endif //FYE_IR_H
