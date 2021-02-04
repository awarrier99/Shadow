#include "util.h"


void debug::print_token(Token* token) {
    switch(token->type) {
        case NUMBER:
            std::cout << "Type: NUMBER" << " Line: " << token->line <<
                      " Column: " << token->column << " Symbol: " << ((Integer*) token->symbol->data)->value << std::endl;
            break;
        case STRING:
            std::cout << "Type: STRING" << " Line: " << token->line <<
                      " Column: " << token->column << " Symbol: " << ((String*) token->symbol->data)->value << std::endl;
            break;
        case IDENT:
            std::cout << "Type: IDENT" << " Line: " << token->line <<
                      " Column: " << token->column << " Symbol: " << ((Ident*) token->symbol->data)->value << std::endl;
            break;
        case OP:
            std::cout << "Type: OP" << " Line: " << token->line <<
                      " Column: " << token->column << " Symbol: " << ((Op*) token->symbol->data)->value << std::endl;
            break;
        case SEP:
            std::cout << "Type: SEP" << " Line: " << token->line <<
                      " Column: " << token->column << " Symbol: " << ((Sep*) token->symbol->data)->value << std::endl;
            break;
        case INVALID:
            std::cout << "Type: INVALID" << " Line: " << token->line << " Column: " << token->column << std::endl;
            break;
    }
}

void debug::print_token_list(TokenList* token_list) {
    for (Token* token: *token_list) {
        print_token(token);
    }
}

void print_ast_node(ASTNode* ast_node, int space) {
    if (ast_node == nullptr) return;

    space += 5;
    print_ast_node(ast_node->right, space);
    std::cout << std::endl;
    for (int i = 5; i < space; i++) std::cout << ' ';
    switch (ast_node->token->type) {
        case NUMBER:
            std::cout << ((Integer*) ast_node->token->symbol->data)->value << std::endl;
            break;
        case IDENT:
            std::cout << ((Ident*) ast_node->token->symbol->data)->value << std::endl;
            break;
        case OP:
            std::cout << ((Op*) ast_node->token->symbol->data)->value << std::endl;
            break;
        default:
            break;
    }
    print_ast_node(ast_node->left, space);
}

void debug::print_ast(AST* ast) {
    print_ast_node(ast->root, 0);
}
