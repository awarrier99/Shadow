#ifndef SHADOW_NUMBERNODE_H
#define SHADOW_NUMBERNODE_H

#include "base.h"


class NumberNode: public IRNode {
public:
    using IRNode::IRNode;

    std::shared_ptr<Data> execute() override;
};


#endif //SHADOW_NUMBERNODE_H
