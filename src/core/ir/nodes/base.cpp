#include "base.h"


IRNode::IRNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right):
        token(std::move(token)), left(std::move(left)), right(std::move(right)) {}

Scoped::Scoped(std::shared_ptr<Scope> &scope): scope(scope) {}

std::shared_ptr<Data> CalcNode::execute() {
    return this->compute(this->left->execute(), this->right->execute());
}
