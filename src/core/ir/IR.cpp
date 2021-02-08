#include "IR.h"


IR::IR(std::unique_ptr<IRNode> &root): root(std::move(root)) {}
