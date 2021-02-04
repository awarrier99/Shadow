#include "IR.h"


void deallocate_ir_node(IRNode* node) {
    if (node->left != nullptr) deallocate_ir_node(node->left);
    if (node->right != nullptr) deallocate_ir_node(node->right);

    delete node;
    node = nullptr;
    std::cout << "IR node cleared" << std::endl;
}

IR::IR(IRNode* root): root(root) {}

IR::~IR() {
    deallocate_ir_node(this->root);
}

IRNode::IRNode(Token* token, IRNode* left, IRNode* right): token(token), left(left), right(right) {}

IRNode::~IRNode() = default;

NumberNode::~NumberNode() {
    this->token = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

IdentNode::~IdentNode() {
    this->token = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

OpNode::~OpNode() {
    this->token = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

AddNode::~AddNode() {
    this->token = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

SubNode::~SubNode() {
    this->token = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

MulNode::~MulNode() {
    this->token = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

DivNode::~DivNode() {
    this->token = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

Data* NumberNode::execute() {
    return this->token->symbol->data;
}

Data* IdentNode::execute() {
    return this->token->symbol->data;
}

Data* OpNode::execute() {
    return this->compute(this->left->execute(), this->right->execute());
}

Data* AddNode::compute(Data* a, Data* b) {
    return new Integer(((Integer*) a)->value + ((Integer*) b)->value);
}

Data* SubNode::compute(Data* a, Data* b) {
    return new Integer(((Integer*) a)->value - ((Integer*) b)->value);
}

Data* MulNode::compute(Data* a, Data* b) {
    return new Integer(((Integer*) a)->value * ((Integer*) b)->value);
}

Data* DivNode::compute(Data* a, Data* b) {
    return new Integer(((Integer*) a)->value / ((Integer*) b)->value);
}
