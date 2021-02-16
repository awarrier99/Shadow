#include "AST.h"


ASTNode::ASTNode(const char* type, token_ptr &token): type(type), token(token) {}

ASTNode::ASTNode(const char* type, token_ptr &token, astnodelist_ptr &children):
    type(type), token(token), children(std::move(children)) {}

VarDecNode::VarDecNode(token_ptr &token, astnodelist_ptr &children, token_ptr &ident):
        ASTNode(ASTNodeType::VARDEC, token, children), ident(ident) {}

FuncDecNode::FuncDecNode(token_ptr &token, astnodelist_ptr &children, token_ptr &ident, astnodelist_ptr &params):
        ASTNode(ASTNodeType::FUNCDEC, token, children), ident(ident), formal_parameters(std::move(params)) {}
