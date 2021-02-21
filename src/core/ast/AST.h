#ifndef SHADOW_AST_H
#define SHADOW_AST_H

#include <vector>
#include "../token/Token.h"


class ASTNodeType {
public:
    inline static const char* NUMBER = "NUMBER";
    inline static const char* STRING = "STRING";
    inline static const char* IDENT = "IDENT";
    inline static const char* VARDEC = "VARDEC";
    inline static const char* FUNCDEC = "FUNCDEC";
    inline static const char* FUNCCALL = "FUNCCALL";
    inline static const char* CALC = "CALC";
    inline static const char* ASSIGN = "ASSIGN";
};

class ASTNode;
typedef std::unique_ptr<ASTNode> astnode_ptr;
class ASTNodeList: public std::vector<astnode_ptr> {};
typedef std::unique_ptr<ASTNodeList> astnodelist_ptr;

class ASTNode {
public:
    ASTNode(const char* type, token_ptr &token);
    ASTNode(const char* type, token_ptr &token, astnodelist_ptr &children);

    const char* type;
    token_ptr token;
    astnodelist_ptr children;
};

class VarDecNode: public ASTNode {
public:
    VarDecNode(token_ptr &token, astnodelist_ptr &children, token_ptr &ident);

    token_ptr ident;
};

class FuncDecNode: public ASTNode {
public:
    FuncDecNode(token_ptr &token, astnodelist_ptr &children, token_ptr &ident, astnodelist_ptr &params);

    token_ptr ident;
    astnodelist_ptr formal_parameters;
};

#endif //SHADOW_AST_H
