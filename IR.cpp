#include "IR.h"


IR::IR(std::unique_ptr<IRNode> &root): root(std::move(root)) {}

IRNode::IRNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right):
    token(std::move(token)), left(std::move(left)), right(std::move(right)) {}

Scoped::Scoped(std::shared_ptr<Scope> &scope): scope(scope) {}

IdentNode::IdentNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right,
                     std::shared_ptr<Scope> &scope): IRNode(token, left, right), Scoped(scope) {}

EqNode::EqNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right,
               std::shared_ptr<Scope> &scope): IRNode(token, left, right), OpNode(token, left, right), Scoped(scope) {}

std::shared_ptr<Data> NumberNode::execute() {
    return std::shared_ptr<Data>(new Number(std::stold(*this->token->symbol->data)));
}

std::shared_ptr<Data> IdentNode::execute() {
    return this->scope->retrieve(*this->token->symbol->data);
}

std::shared_ptr<Data> CalcNode::execute() {
    return this->compute(this->left->execute(), this->right->execute());
}

std::shared_ptr<Data> AddNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    auto &a_num = dynamic_cast<Number&>(*a);
    auto &b_num = dynamic_cast<Number&>(*b);
    return std::shared_ptr<Data>(new Number(a_num.value + b_num.value));
}

std::shared_ptr<Data> SubNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    auto &a_num = dynamic_cast<Number&>(*a);
    auto &b_num = dynamic_cast<Number&>(*b);
    return std::unique_ptr<Data>(new Number(a_num.value - b_num.value));
}

std::shared_ptr<Data> MulNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    auto &a_num = dynamic_cast<Number&>(*a);
    auto &b_num = dynamic_cast<Number&>(*b);
    return std::shared_ptr<Data>(new Number(a_num.value * b_num.value));
}

std::shared_ptr<Data> DivNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    auto &a_num = dynamic_cast<Number&>(*a);
    auto &b_num = dynamic_cast<Number&>(*b);
    return std::shared_ptr<Data>(new Number(a_num.value / b_num.value));
}

std::shared_ptr<Data> EqNode::execute() {
    auto data = this->right->execute();
    this->scope->assign(*this->left->token->symbol->data, data);
    return data;
}
