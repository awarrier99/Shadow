#ifndef FYE_AST_H
#define FYE_AST_H

#include "Token.h"


class ASTNode {
public:
    explicit ASTNode(Token* token);
    ASTNode(Token* token, ASTNode* left, ASTNode* right);
    ~ASTNode();

    Token* token;
    ASTNode* left;
    ASTNode* right;
};

class AST {
public:
    explicit AST(ASTNode* root);
    ~AST();

    ASTNode* root;
};

#endif //FYE_AST_H
