#include "Parser.h"


bool operator_has_higher_precedence(std::string* current, Token* op_top) {
    std::string* op_top_data = op_top->symbol->data;
    if (*op_top_data == "(" || *op_top_data == "=") return false;

    std::map<std::string, int> precedence = {
            {"*", 2},
            {"/", 2},
            {"+", 1},
            {"-", 1}
    };

    return precedence[*op_top_data] >= precedence[*current];
}

void build_expression(std::stack<ASTNode*>* expr_stack, std::stack<Token*>* op_stack) {
    auto* op_token = op_stack->top();
    op_stack->pop();
    auto* right_node = expr_stack->top();
    expr_stack->pop();
    auto* left_node = expr_stack->top();
    expr_stack->pop();

    expr_stack->push(new ASTNode(op_token, left_node, right_node));
}

AST* Parser::build_ast() const {
    std::stack<ASTNode*> expr_stack;
    std::stack<Token*> op_stack;

    for (Token* token: *this->token_list) {
        debug::print_token(token);
        std::string* data = token->symbol->data;
        if (token->type == SEP) {
            if (*data == "(") {
                op_stack.push(token);
            } else if (*data == ")") {
                while (!op_stack.empty() && *op_stack.top()->symbol->data != "(") {
                    build_expression(&expr_stack, &op_stack);
                }

                op_stack.pop();
            } else {
                break;
            }
        } else if (token->type == NUMBER || token->type == IDENT) {
            expr_stack.push(new ASTNode(token));
        } else if (token->type == OP) {
            while (!op_stack.empty() && operator_has_higher_precedence(data, op_stack.top())) {
                build_expression(&expr_stack, &op_stack);
            }

            op_stack.push(token);
        }
    }

    while (!op_stack.empty()) {
        build_expression(&expr_stack, &op_stack);
    }

    auto* ast = new AST(expr_stack.top());
    expr_stack.pop();
    debug::print_ast(ast);
    return ast;
}
