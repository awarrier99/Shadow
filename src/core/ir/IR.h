#ifndef SHADOW_IR_H
#define SHADOW_IR_H

#include "nodes/base.h"
#include "nodes/AddNode.h"
#include "nodes/DivNode.h"
#include "nodes/EqNode.h"
#include "nodes/IdentNode.h"
#include "nodes/ModNode.h"
#include "nodes/MulNode.h"
#include "nodes/NumberNode.h"
#include "nodes/StringNode.h"
#include "nodes/SubNode.h"
#include "../source/Token.h"
#include "../data/Scope.h"

class IR {
public:
    explicit IR(std::unique_ptr<IRNode> &root);

    std::unique_ptr<IRNode> root;
};

#endif //SHADOW_IR_H
