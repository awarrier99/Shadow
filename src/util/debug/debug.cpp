#include "debug.h"


void debug::print_token(token_ptr &token) {
    std::cout << "Type: " << token->type << " Line: " << token->line <<
              " Column: " << token->column << " Symbol: " << (token->lexeme ? *token->lexeme : "NULL") << std::endl;
}

void print_ast_node(astnode_ptr &node, std::string prefix) {
    if (!node) return;

    std::cout << prefix << "Node: " << std::endl;
    prefix += "\t";

    std::cout << prefix << "Type: " << node->type << std::endl;
    if (node->token) std::cout << prefix << "Token: " << *node->token->lexeme << std::endl;

    if (node->type == ASTNodeType::VARDEC) {
        auto &node_cast = static_cast<VarDecNode&>(*node);
        std::cout << prefix << "Ident: " << *node_cast.ident->lexeme << std::endl;
    } else if (node->type == ASTNodeType::FUNCDEC) {
        auto &node_cast = static_cast<FuncDecNode&>(*node);
        std::cout << prefix << "Ident: " << *node_cast.ident->lexeme << std::endl;
        std::cout << prefix << "Params: " << std::endl;
        for (auto &n: *node_cast.formal_parameters) {
            print_ast_node(n, prefix + "\t");
        }
    }

    if (node->children && !node->children->empty()) {
        std::cout << prefix << "Children: " << std::endl;
        for (auto &n: *node->children) {
            print_ast_node(n, prefix + "\t");
        }
    }
}

void debug::print_ast_node(astnode_ptr &node) {
    std::string prefix;
    print_ast_node(node, prefix);
}

//void print_ast_node(astnode_ptr &ast_node, int space) {
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
