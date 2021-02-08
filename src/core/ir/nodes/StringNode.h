#ifndef SHADOW_STRINGNODE_H
#define SHADOW_STRINGNODE_H

#include "base.h"


class StringNode: public IRNode {
public:
    using IRNode::IRNode;

    std::shared_ptr<Data> execute() override;
};

#endif //SHADOW_STRINGNODE_H
