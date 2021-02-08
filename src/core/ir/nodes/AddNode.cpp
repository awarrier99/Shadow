#include "AddNode.h"


std::shared_ptr<Data> AddNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    return Operations::add(a, b);
}
