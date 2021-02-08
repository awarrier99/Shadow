#include "debug.h"


void debug::print_token(std::unique_ptr<Token> &token) {
    switch(token->type) {
        case NUMBER:
            std::cout << "Type: NUMBER";
            break;
        case STRING:
            std::cout << "Type: STRING";
            break;
        case IDENT:
            std::cout << "Type: IDENT";
            break;
        case OP:
            std::cout << "Type: OP";
            break;
        case SEP:
            std::cout << "Type: SEP";
            break;
        case INVALID:
            std::cout << "Type: INVALID" << " Line: " << token->line << " Column: " << token->column << std::endl;
            return;
    }
    std::cout << " Line: " << token->line <<
                 " Column: " << token->column << " Symbol: " << *token->symbol->data << std::endl;
}

void debug::print_token_list(std::unique_ptr<TokenList> &token_list) {
    for (auto &token: *token_list) {
        print_token(token);
    }
}

void print_ast_node(std::unique_ptr<ASTNode> &ast_node, int space) {
    if (ast_node == nullptr) return;

    space += 5;
    print_ast_node(ast_node->right, space);
    std::cout << std::endl;
    for (int i = 5; i < space; i++) std::cout << ' ';
    std::cout << *ast_node->token->symbol->data << std::endl;
    print_ast_node(ast_node->left, space);
}

void debug::print_ast(std::unique_ptr<AST> &ast) {
    print_ast_node(ast->root, 0);
}
