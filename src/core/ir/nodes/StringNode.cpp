#include "StringNode.h"


std::shared_ptr<Data> StringNode::execute() {
    return std::shared_ptr<Data>(new String(*this->token->symbol->data));
}
