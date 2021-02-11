#include "Executor.h"


Executor::Executor() {
    this->scope = std::make_shared<Scope>(Scope());
}

std::map<const char*, func_ptr> Executor::visitor_map = {
        {ASTNodeType::NUMBER, &Executor::visit_num},
        {ASTNodeType::STRING,  &Executor::visit_str},
        {ASTNodeType::IDENT, &Executor::visit_ident},
        {ASTNodeType::VARDEC, (func_ptr) &Executor::visit_vardec},
        {ASTNodeType::CALC, &Executor::visit_calc},
        {ASTNodeType::ASSIGN, &Executor::visit_assign}
};

std::shared_ptr<Data> Executor::visit_num(std::unique_ptr<ASTNode> &node) {
    return std::shared_ptr<Data>(new Number(std::stold(*node->token->lexeme)));
}

std::shared_ptr<Data> Executor::visit_str(std::unique_ptr<ASTNode> &node) {
    return std::shared_ptr<Data>(new String(*node->token->lexeme));
}

std::shared_ptr<Data> Executor::visit_ident(std::unique_ptr<ASTNode> &node) {
    auto symbol = this->scope->lookup(*node->token->lexeme);
    if (!symbol) throw std::runtime_error("Symbol " + *node->token->lexeme + " has not been declared yet");
    return this->memory.retrieve(symbol);
}

std::shared_ptr<Data> Executor::visit_vardec(std::unique_ptr<VarDecNode> &node) {
    bool is_const;
    if (node->token) is_const = node->token->type == TokenType::CONST;
    else is_const = false;
    auto symbol = std::make_shared<Symbol>(Symbol(*node->ident->lexeme, is_const));
    this->scope->declare(*node->ident->lexeme, symbol);
    if (node->nodes && !node->nodes->empty()) return this->visit((*node->nodes)[0]);
    return nullptr;
}

std::shared_ptr<Data> Executor::visit_funcdec(std::unique_ptr<FuncDecNode> &node) {

}

std::shared_ptr<Data> Executor::visit_calc(std::unique_ptr<ASTNode> &node) {
    auto left = this->visit((*node->nodes)[0]);
    auto right = this->visit((*node->nodes)[1]);
    return CalcOperations::operate(left, right, node->token->type);
}

std::shared_ptr<Data> Executor::visit_assign(std::unique_ptr<ASTNode> &node) {
    auto &left = (*node->nodes)[0];
    auto right = this->visit((*node->nodes)[1]);
    auto symbol = this->scope->lookup(*left->token->lexeme);
    if (!symbol) throw std::runtime_error("Symbol " + *left->token->lexeme + " has not been declared yet");
    AssignOperations::operate(symbol, right, node->token->type, &this->memory);
    return nullptr;
}

std::shared_ptr<Data> Executor::visit(std::unique_ptr<ASTNode> &node) {
    auto visit_func = Executor::visitor_map[node->type];
    return (this->*visit_func)(node);
}

void Executor::execute(std::unique_ptr<ASTNode> &root) {
    auto data = this->visit(root);
    if (data) std::cout << data->display() << std::endl;
}
