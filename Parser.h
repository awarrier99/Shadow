#ifndef FYE_PARSER_H
#define FYE_PARSER_H


#include <vector>
#include <string>
#include <map>
#include "Token.h"
#include "Lexer.h"

//should have the token list, and each tokens type and symbol
//
class Parser {

//want to pass in a token list
public:
    static Token* get_token(TokenList* token_list);

};

class ParseTree : public std::map<int, Token> {};

class ASTNode {
public:
    void* data;
    ASTNode* left;
    ASTNode* right;

    ASTNode() {
        data = 0;
        left = NULL;
        right = NULL;
    }

    ASTNode* CreateNode(void* data, ASTNode*left, ASTNode* right) {
        ASTNode* node = new ASTNode();
        node->data = data;
        node->left = left;
        node->right = right;
    }
};






#endif //FYE_PARSER_H
