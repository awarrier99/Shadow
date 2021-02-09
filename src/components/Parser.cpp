#include "Parser.h"


Parser::Parser(Lexer lexer): lexer(lexer) {}

bool operator_has_higher_precedence(std::string &current, std::unique_ptr<Token> &op_top) {
    auto &op_top_lexeme = *op_top->lexeme;
    if (op_top_lexeme == "(" || op_top_lexeme == "=") return false;

    std::map<std::string, int> precedence = {
            {"*", 2},
            {"/", 2},
            {"+", 1},
            {"-", 1}
    };

    return precedence[op_top_lexeme] >= precedence[current];
}

void build_expression(std::stack<std::unique_ptr<ASTNode>> &expr_stack, std::stack<std::unique_ptr<Token>> &op_stack) {
    auto op_token = std::move(op_stack.top());
    op_stack.pop();
    auto right_node = std::move(expr_stack.top());
    expr_stack.pop();
    auto left_node = std::move(expr_stack.top());
    expr_stack.pop();

    expr_stack.push(std::make_unique<ASTNode>(ASTNode(op_token, left_node, right_node)));
}

void Parser::consume(const char* type) {
    if (this->token->type == type) this->token = this->lexer.extract_token();
}

std::unique_ptr<AST> Parser::parse() {
//    std::stack<std::unique_ptr<ASTNode>> expr_stack;
//    std::stack<std::unique_ptr<Token>> op_stack;

    while (true) {
        this->token = this->lexer.extract_token();
        debug::print_token(this->token);
        if (this->token->type == TokenType::INVALID || this->token->type == TokenType::FEOF) break;


    }

//    for (int i = 0; i < token_list->size(); i++) {
//        auto &token = (*token_list)[i];
//        auto &lexeme = *token->lexeme;
//        if (token->type == SEP) {
//            if (lexeme == "(") {
//                op_stack.push(std::move(token));
//            } else if (lexeme == ")") {
//                while (!op_stack.empty() && *op_stack.top()->lexeme != "(") {
//                    build_expression(expr_stack, op_stack);
//                }
//
//                op_stack.pop();
//            } else {
//                break;
//            }
//        } else if (token->type == NUMBER || token->type == STRING || token->type == IDENT) {
//            expr_stack.push(std::make_unique<ASTNode>(ASTNode(token)));
//        } else if (token->type == KEYWORD) {
//            auto root = std::make_unique<ASTNode>(ASTNode(token));
//            ASTNode* prev = root.get();
//
//            while ((*token_list)[i + 1]->type == KEYWORD) { // consume next tokens until ident
//                prev->right = std::make_unique<ASTNode>((*token_list)[i + 1]);
//                prev = prev->right.get();
//                i++;
//            }
//            if ((*token_list)[i + 1]->type == IDENT) {
//                prev->right = std::make_unique<ASTNode>((*token_list)[i + 1]);
//                prev = nullptr;
//                i++;
//                expr_stack.push(std::move(root));
//            }
//        } else if (token->type == OP) {
//            while (!op_stack.empty() && operator_has_higher_precedence(lexeme, op_stack.top())) {
//                build_expression(expr_stack, op_stack);
//            }
//
//            op_stack.push(std::move(token));
//        }
//    }

//    while (!op_stack.empty()) {
//        build_expression(expr_stack, op_stack);
//    }
//
//    auto ast = std::make_unique<AST>(AST(expr_stack.top()));
//    debug::print_ast(ast);
//    expr_stack.pop();
//    return ast;
    return nullptr;
}
