#include "ModNode.h"


std::shared_ptr<Data> ModNode::compute(std::shared_ptr<Data> a, std::shared_ptr<Data> b) {
    return Operations::mod(a, b);
}
