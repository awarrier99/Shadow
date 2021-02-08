#ifndef SHADOW_IDENTNODE_H
#define SHADOW_IDENTNODE_H

#include "base.h"


class IdentNode: public IRNode, public Scoped {
public:
    IdentNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right, std::shared_ptr<Scope> &scope);

    std::shared_ptr<Data> execute() override;
};

#endif //SHADOW_IDENTNODE_H
