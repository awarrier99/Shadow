#include "Executor.h"

std::unique_ptr<IRNode> Executor::build_ir_node(std::unique_ptr<ASTNode> &current) {
    if (current == nullptr) return nullptr;

    auto left = build_ir_node(current->left);
    auto right = build_ir_node(current->right);

    if (current->token->type == NUMBER) {
        return std::unique_ptr<IRNode>(new NumberNode(current->token, left, right));
    } else if (current->token->type == STRING) {
        return std::unique_ptr<IRNode>(new StringNode(current->token, left, right));
    } else if (current->token->type == IDENT) {
        return std::unique_ptr<IRNode>(new IdentNode(current->token, left, right, this->global));
    } else if (current->token->type == OP) {
        auto op = *current->token->symbol->data;
        if (op == "+") {
            return std::unique_ptr<IRNode>(new AddNode(current->token, left, right));
        } else if (op == "-") {
            return std::unique_ptr<IRNode>(new SubNode(current->token, left, right));
        } else if (op == "*") {
            return std::unique_ptr<IRNode>(new MulNode(current->token, left, right));
        } else if (op == "/") {
            return std::unique_ptr<IRNode>(new DivNode(current->token, left, right));
        } else if (op == "=") {
            return std::unique_ptr<IRNode>(new EqNode(current->token, left, right, this->global));
        } else if (op == "%") {
            return std::unique_ptr<IRNode>(new ModNode(current->token, left, right));
        }
    }

    return nullptr;
}

void Executor::build_ir() {
    auto root = build_ir_node(this->ast->root);
    this->ir = std::make_unique<IR>(IR(root));
}

void Executor::execute_ir() const {
    auto data = this->ir->root->execute();
    if (data) std::cout << data->display() << std::endl;
}
