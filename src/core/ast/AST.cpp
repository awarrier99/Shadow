#include "AST.h"


ASTNode::ASTNode(const char* type, std::shared_ptr<Token> &token): type(type), token(token) {}

ASTNode::ASTNode(const char* type, std::shared_ptr<Token> &token, std::unique_ptr<ASTNodeList> &nodes):
    type(type), token(token), nodes(std::move(nodes)) {}

VarDecNode::VarDecNode(std::shared_ptr<Token> &token, std::unique_ptr<ASTNodeList> &nodes,
                       std::shared_ptr<Token> &ident): ASTNode(ASTNodeType::VARDEC, token, nodes), ident(ident) {}

FuncDecNode::FuncDecNode(std::shared_ptr<Token> &token, std::unique_ptr<ASTNodeList> &nodes,
                         std::shared_ptr<Token> &ident, std::unique_ptr<ASTNodeList> &params):
                            ASTNode(ASTNodeType::FUNCDEC, token, nodes), ident(ident), params(std::move(params)) {}
