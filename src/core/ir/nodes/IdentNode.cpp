#include "IdentNode.h"


IdentNode::IdentNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right,
                     std::shared_ptr<Scope> &scope): IRNode(token, left, right), Scoped(scope) {}

std::shared_ptr<Data> IdentNode::execute() {
    return this->scope->retrieve(*this->token->lexeme);
}
