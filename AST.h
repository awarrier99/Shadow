#ifndef FYE_AST_H
#define FYE_AST_H

#include "Token.h"


class ASTNode {
public:
    explicit ASTNode(std::unique_ptr<Token> &token);
    ASTNode(std::unique_ptr<Token> &token, std::unique_ptr<ASTNode> &left, std::unique_ptr<ASTNode> &right);

    std::unique_ptr<Token> token;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
};

class AST {
public:
    explicit AST(std::unique_ptr<ASTNode> &root);

    std::unique_ptr<ASTNode> root;
};

#endif //FYE_AST_H
