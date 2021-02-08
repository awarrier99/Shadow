#include "Parser.h"


bool operator_has_higher_precedence(std::string &current, std::unique_ptr<Token> &op_top) {
    auto &op_top_data = *op_top->symbol->data;
    if (op_top_data == "(" || op_top_data == "=") return false;

    std::map<std::string, int> precedence = {
            {"*", 2},
            {"/", 2},
            {"+", 1},
            {"-", 1}
    };

    return precedence[op_top_data] >= precedence[current];
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

std::unique_ptr<AST> Parser::build_ast() const {
    std::stack<std::unique_ptr<ASTNode>> expr_stack;
    std::stack<std::unique_ptr<Token>> op_stack;

    for (auto &token: *this->token_list) {
        auto &data = *token->symbol->data;
        if (token->type == SEP) {
            if (data == "(") {
                op_stack.push(std::move(token));
            } else if (data == ")") {
                while (!op_stack.empty() && *op_stack.top()->symbol->data != "(") {
                    build_expression(expr_stack, op_stack);
                }

                op_stack.pop();
            } else {
                break;
            }
        } else if (token->type == NUMBER || token->type == STRING || token->type == IDENT) {
            expr_stack.push(std::make_unique<ASTNode>(ASTNode(token)));
        } else if (token->type == OP) {
            while (!op_stack.empty() && operator_has_higher_precedence(data, op_stack.top())) {
                build_expression(expr_stack, op_stack);
            }

            op_stack.push(std::move(token));
        }
    }

    while (!op_stack.empty()) {
        build_expression(expr_stack, op_stack);
    }

    auto ast = std::make_unique<AST>(AST(expr_stack.top()));
    expr_stack.pop();
    return ast;
}
