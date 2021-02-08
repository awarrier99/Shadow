#ifndef SHADOW_MODNODE_H
#define SHADOW_MODNODE_H

#include "base.h"


class ModNode: public CalcNode {
public:
    using CalcNode::CalcNode;

    std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) override;
};


#endif //SHADOW_MODNODE_H
