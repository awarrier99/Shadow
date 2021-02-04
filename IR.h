#ifndef FYE_IR_H
#define FYE_IR_H

#include "Token.h"


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

class IdentNode: public IRNode {
public:
    using IRNode::IRNode;
    ~IdentNode() override;

    Data* execute() override;
};

class OpNode: public IRNode {
public:
    using IRNode::IRNode;
    ~OpNode() override;

    Data* execute() override;
    virtual Data* compute(Data* a, Data* b) = 0;
};

class AddNode: public OpNode {
public:
    using OpNode::OpNode;
    ~AddNode() override;

    Data* compute(Data* a, Data* b) override;
};

class SubNode: public OpNode {
public:
    using OpNode::OpNode;
    ~SubNode() override;

    Data* compute(Data* a, Data* b) override;
};

class MulNode: public OpNode {
public:
    using OpNode::OpNode;
    ~MulNode() override;

    Data* compute(Data* a, Data* b) override;
};

class DivNode: public OpNode {
public:
    using OpNode::OpNode;
    ~DivNode() override;

    Data* compute(Data* a, Data* b) override;
};

class IR {
public:
    explicit IR(IRNode* root);
    ~IR();

    IRNode* root;
};

#endif //FYE_IR_H
