#ifndef SHADOW_MULNODE_H
#define SHADOW_MULNODE_H

#include "base.h"


class MulNode: public CalcNode {
public:
    using CalcNode::CalcNode;

    std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) override;
};

#endif //SHADOW_MULNODE_H
