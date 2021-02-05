#include "Executor.h"

IRNode* Executor::build_ir_node(ASTNode* current) {
    if (current == nullptr) return nullptr;

    IRNode* left = build_ir_node(current->left);
    IRNode* right = build_ir_node(current->right);

    if (current->token->type == NUMBER) {
        return new NumberNode(current->token, left, right);
    } else if (current->token->type == IDENT) {
        auto* node = new IdentNode(current->token, left, right);
        node->scope = this->global;
        return node;
    } else if (current->token->type == OP) {
        std::string* op = current->token->symbol->data;
        if (*op == "+") {
            return new AddNode(current->token, left, right);
        } else if (*op == "-") {
            return new SubNode(current->token, left, right);
        } else if (*op == "*") {
            return new MulNode(current->token, left, right);
        } else if (*op == "/") {
            return new DivNode(current->token, left, right);
        } else if (*op == "=") {
            auto* node = new EqNode(current->token, left, right);
            node->scope = this->global;
            return node;
        }
    }

    return nullptr;
}

void Executor::build_ir() {
    this->ir = new IR(build_ir_node(this->ast->root));
}

void Executor::execute_ir() const {
    Data* data = this->ir->root->execute();
    std::cout << "Data: " << ((Number*) data)->value << std::endl;
}
