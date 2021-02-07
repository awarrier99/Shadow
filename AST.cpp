#include "AST.h"


AST::AST(std::unique_ptr<ASTNode> &root): root(std::move(root)) {}

ASTNode::ASTNode(std::unique_ptr<Token> &token): token(std::move(token)), left(nullptr), right(nullptr) {}

ASTNode::ASTNode(std::unique_ptr<Token> &token, std::unique_ptr<ASTNode> &left, std::unique_ptr<ASTNode> &right):
    token(std::move(token)), left(std::move(left)), right(std::move(right)) {}
