#include "EqNode.h"


EqNode::EqNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right,
               std::shared_ptr<Scope> &scope): IRNode(token, left, right), OpNode(token, left, right), Scoped(scope) {}

std::shared_ptr<Data> EqNode::execute() {
    auto data = this->right->execute();
    this->scope->assign(*this->left->token->symbol->data, data);
    return data;
}
