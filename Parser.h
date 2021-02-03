#ifndef FYE_PARSER_H
#define FYE_PARSER_H


#include <string>
#include <stack>
#include <map>
#include "Token.h"


class ASTNode {
public:
    Token* token;
    ASTNode* left;
    ASTNode* right;

    explicit ASTNode(Token* token);
    ASTNode(Token* token, ASTNode* left, ASTNode* right);
};

class AST {
public:
    ASTNode* root;
};

class Parser {
public:
    static AST* build_ast(TokenList* token_list);

    static std::map<char, int> precedence;
};


#endif //FYE_PARSER_H
