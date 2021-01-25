#include "Parser.h"


std::map<char, int> Parser::precedence = {
        {'(', 1},
        {')', 1},
        {'*', 3},
        {'/', 3},
        {'+', 4},
        {'-', 4}
};

ASTNode::ASTNode(Token* token) {
    this->token = token;
    this->left = this->right = nullptr;
}

ASTNode::ASTNode(Token* token, ASTNode* left, ASTNode* right) {
    this->token = token;
    this->left = left;
    this->right = right;
}

AST* Parser::build_ast(TokenList* token_list) {
    auto* ast = new AST();
    auto* expr_stack = new std::stack<ASTNode*>();
    auto* op_stack = new std::stack<char>();
    for (Token* token: *token_list) {
        if (token->type == SEP) {
            char c = *((char*)token->symbol->data);
            if (c == '(') {
                op_stack->push(c);
            }

        } else if (token->type == NUMBER) {
            expr_stack->push(new ASTNode(token));
        } else if (token->type == OP) {
            op_stack->push(*((char*)token->symbol->data));

        }
    }



}



