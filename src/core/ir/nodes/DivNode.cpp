#include "DivNode.h"


std::shared_ptr<Data> DivNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    return Operations::div(a, b);
}
