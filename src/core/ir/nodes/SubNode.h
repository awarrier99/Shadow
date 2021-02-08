#ifndef SHADOW_SUBNODE_H
#define SHADOW_SUBNODE_H

#include "base.h"


class SubNode: public CalcNode {
public:
    using CalcNode::CalcNode;

    std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) override;
};

#endif //SHADOW_SUBNODE_H
