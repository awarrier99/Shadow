#ifndef SHADOW_AST_H
#define SHADOW_AST_H

#include <vector>
#include "../source/Token.h"


class ASTNodeType {
public:
    inline static const char* NUMBER = "NUMBER";
    inline static const char* STRING = "STRING";
    inline static const char* IDENT = "IDENT";
    inline static const char* VARDEC = "VARDEC";
    inline static const char* FUNCDEC = "FUNCDEC";
    inline static const char* CALC = "CALC";
    inline static const char* ASSIGN = "ASSIGN";
};

class ASTNode;
class ASTNodeList: public std::vector<std::unique_ptr<ASTNode>> {};

class ASTNode {
public:
    ASTNode(const char* type, std::shared_ptr<Token> &token);
    ASTNode(const char* type, std::shared_ptr<Token> &token, std::unique_ptr<ASTNodeList> &nodes);

    const char* type;
    std::shared_ptr<Token> token;
    std::unique_ptr<ASTNodeList> nodes;
};

class VarDecNode: public ASTNode {
public:
    VarDecNode(std::shared_ptr<Token> &token, std::unique_ptr<ASTNodeList> &nodes, std::shared_ptr<Token> &ident);

    std::shared_ptr<Token> ident;
};

class FuncDecNode: public ASTNode {
public:
    FuncDecNode(std::shared_ptr<Token> &token, std::unique_ptr<ASTNodeList> &nodes, std::shared_ptr<Token> &ident, std::unique_ptr<ASTNodeList> &params);

    std::shared_ptr<Token> ident;
    std::unique_ptr<ASTNodeList> params;
};

#endif //SHADOW_AST_H
