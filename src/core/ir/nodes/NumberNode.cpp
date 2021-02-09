#include "NumberNode.h"


std::shared_ptr<Data> NumberNode::execute() {
    return std::shared_ptr<Data>(new Number(std::stold(*this->token->lexeme)));
}
