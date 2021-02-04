#include "AST.h"


void deallocate_ast_node(ASTNode* node) {
    if (node->left != nullptr) deallocate_ast_node(node->left);
    if (node->right != nullptr) deallocate_ast_node(node->right);

    delete node;
    node = nullptr;
    std::cout << "AST node cleared" << std::endl;
}

AST::AST(ASTNode* root): root(root) {}

AST::~AST() {
    deallocate_ast_node(this->root);
}

ASTNode::ASTNode(Token* token): token(token), left(nullptr), right(nullptr) {}

ASTNode::ASTNode(Token* token, ASTNode* left, ASTNode* right): token(token), left(left), right(right) {}

ASTNode::~ASTNode() {
    this->token = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}
