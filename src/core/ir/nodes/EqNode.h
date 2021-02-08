#ifndef SHADOW_EQNODE_H
#define SHADOW_EQNODE_H

#include "base.h"


class EqNode: public OpNode, public Scoped {
public:
    EqNode(std::unique_ptr<Token> &token, std::unique_ptr<IRNode> &left, std::unique_ptr<IRNode> &right, std::shared_ptr<Scope> &scope);

    std::shared_ptr<Data> execute() override;
};


#endif //SHADOW_EQNODE_H
