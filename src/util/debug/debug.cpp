#include "debug.h"


void debug::print_token(std::shared_ptr<Token> &token) {
    std::cout << "Type: " << token->type << " Line: " << token->line <<
              " Column: " << token->column << " Symbol: " << (token->lexeme ? *token->lexeme : "NULL") << std::endl;
}

//void print_ast_node(std::unique_ptr<ASTNode> &ast_node, int space) {
//    if (ast_node == nullptr) return;
//
//    space += 5;
//    print_ast_node(ast_node->right, space);
//    std::cout << std::endl;
//    for (int i = 5; i < space; i++) std::cout << ' ';
//    std::cout << *ast_node->token->lexeme << std::endl;
//    print_ast_node(ast_node->left, space);
//}
//
//void debug::print_ast(std::unique_ptr<AST> &ast) {
//    print_ast_node(ast->root, 0);
//}
