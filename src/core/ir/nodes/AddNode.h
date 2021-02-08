#ifndef SHADOW_ADDNODE_H
#define SHADOW_ADDNODE_H

#include "base.h"


class AddNode: public CalcNode {
public:
    using CalcNode::CalcNode;

    std::shared_ptr<Data> compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) override;
};


#endif //SHADOW_ADDNODE_H
