#include "Executor.h"

IRNode* build_ir_node(ASTNode* current) {
    if (current == nullptr) return nullptr;

    IRNode* left = build_ir_node(current->left);
    IRNode* right = build_ir_node(current->right);

    if (current->token->type == NUMBER) {
        return new NumberNode(current->token, left, right);
    } else if (current->token->type == IDENT) {

    } else if (current->token->type == OP) {
        std::string op = ((Op*) current->token->symbol->data)->value;
        if (op == "+") {
            return new AddNode(current->token, left, right);
        } else if (op == "-") {
            return new SubNode(current->token, left, right);
        } else if (op == "*") {
            return new MulNode(current->token, left, right);
        } else if (op == "/") {
            return new DivNode(current->token, left, right);
        }
    }

    return nullptr;
}

void Executor::build_ir() {
    this->ir = new IR(build_ir_node(this->ast->root));
}

void Executor::execute_ir() const {
    Data* data = this->ir->root->execute();
    std::cout << "Data: " << ((Integer*) data)->value << std::endl;
}
