#ifndef SHADOW_DIVNODE_H
#define SHADOW_DIVNODE_H

#include "base.h"


class DivNode: public CalcNode {
public:
    using CalcNode::CalcNode;

    std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) override;
};

#endif //SHADOW_DIVNODE_H
