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

EqNode::~EqNode() {
    this->token = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

Data* NumberNode::execute() {
    std::string* data = this->token->symbol->data;
    return new Number(std::stold(*data));
}

Data* IdentNode::execute() {
    return this->scope->retrieve(this->token->symbol->data);
}

Data* CalcNode::execute() {
    return this->compute(this->left->execute(), this->right->execute());
}

Data* AddNode::compute(Data* a, Data* b) {
    return new Number(((Number*) a)->value + ((Number*) b)->value);
}

Data* SubNode::compute(Data* a, Data* b) {
    return new Number(((Number*) a)->value - ((Number*) b)->value);
}

Data* MulNode::compute(Data* a, Data* b) {
    return new Number(((Number*) a)->value * ((Number*) b)->value);
}

Data* DivNode::compute(Data* a, Data* b) {
    return new Number(((Number*) a)->value / ((Number*) b)->value);
}

Data* EqNode::execute() {
    Data* data = this->right->execute();
    this->scope->assign(this->left->token->symbol->data, data);
    return data;
}
