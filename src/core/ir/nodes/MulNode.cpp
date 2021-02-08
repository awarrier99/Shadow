#include "MulNode.h"


std::shared_ptr<Data> MulNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    auto &a_num = dynamic_cast<Number&>(*a);
    auto &b_num = dynamic_cast<Number&>(*b);
    return std::shared_ptr<Data>(new Number(a_num.value * b_num.value));
}
