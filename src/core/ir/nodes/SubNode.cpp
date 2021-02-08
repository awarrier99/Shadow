#include "SubNode.h"


std::shared_ptr<Data> SubNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    return Operations::sub(a, b);
}
