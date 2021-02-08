#include "MulNode.h"


std::shared_ptr<Data> MulNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    return Operations::mul(a, b);
}
