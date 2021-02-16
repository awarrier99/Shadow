#include "Executor.h"


Executor::Executor(bool repl): repl(repl) {
    this->scope = std::make_shared<Scope>(Scope());
    namespace_ptr rec = nullptr;
    this->_namespace = std::make_shared<Namespace>(Namespace(0, rec));
}

std::map<const char*, execfunc_ptr> Executor::visitor_map = {
        {ASTNodeType::NUMBER, &Executor::visit_num},
        {ASTNodeType::STRING,  &Executor::visit_str},
        {ASTNodeType::IDENT, &Executor::visit_ident},
        {ASTNodeType::VARDEC, (execfunc_ptr) &Executor::visit_vardec},
        {ASTNodeType::FUNCDEC, (execfunc_ptr) &Executor::visit_funcdec},
        {ASTNodeType::FUNCCALL, &Executor::visit_funccall},
        {ASTNodeType::CALC, &Executor::visit_calc},
        {ASTNodeType::ASSIGN, &Executor::visit_assign}
};

void Executor::load_builtins() {

}

data_ptr Executor::visit_num(astnode_ptr &node) {
    auto data = void_ptr(new long double(std::stold(*node->token->lexeme)));
    return std::make_unique<Data>(Data(Datatype::NUMBER, data));
}

data_ptr Executor::visit_str(astnode_ptr &node) {
    auto data = void_ptr(new std::string(*node->token->lexeme));
    return std::make_unique<Data>(Data(Datatype::STRING, data));
}

data_ptr Executor::visit_ident(astnode_ptr &node) {
    auto symbol = this->scope->lookup(*node->token->lexeme);
    if (!symbol) throw std::runtime_error("Symbol " + *node->token->lexeme + " has not been declared yet");
    return this->_namespace->retrieve(symbol);
}

data_ptr Executor::visit_vardec(std::unique_ptr<VarDecNode> &node) {
    bool is_const = false;
    if (node->token) is_const = node->token->type == TokenType::CONST;
    auto symbol = std::make_shared<Symbol>(Symbol(node->ident->lexeme, is_const, this->_namespace->level));
    this->scope->declare(*node->ident->lexeme, symbol);
    if (node->children && !node->children->empty()) return this->visit((*node->children)[0]);

    return nullptr;
}

data_ptr Executor::visit_funcdec(std::unique_ptr<FuncDecNode> &node) {
    auto symbol = this->scope->lookup(*node->ident->lexeme);
    if (!symbol) {
        symbol = std::make_shared<Symbol>(Symbol(node->ident->lexeme, false, this->_namespace->level));
        this->scope->declare(*node->ident->lexeme, symbol);
    }
    auto func = data_ptr(new Function(node->formal_parameters, node->children));
    this->_namespace->assign(symbol, func);

    return nullptr;
}

data_ptr Executor::visit_funccall(astnode_ptr &node) {
    auto symbol = this->scope->lookup(*node->token->lexeme);
    auto func = this->_namespace->retrieve(symbol);
    if (func->type != Datatype::FUNCTION) throw std::runtime_error("Symbol " + *symbol->name + " is not a function");
    auto func_cast = std::static_pointer_cast<Function>(func);
    this->scope = std::make_shared<Scope>(Scope(this->scope));
    this->_namespace = std::make_unique<Namespace>(Namespace(this->_namespace->level + 1, this->_namespace));

    for (int i = 0; i < func_cast->formal_parameters->size(); i++) {
        auto &param = (*func_cast->formal_parameters)[i];
        auto &param_cast = static_cast<VarDecNode&>(*param);
        auto param_symbol = std::make_shared<Symbol>(Symbol(param_cast.ident->lexeme, false, this->_namespace->level));
        auto &arg = (*node->children)[i];
        auto arg_value = this->visit(arg);

        this->scope->declare(*param_cast.ident->lexeme, param_symbol);
        this->_namespace->assign(param_symbol, arg_value);
    }

    for (auto &child: *func_cast->children) {
        this->execute(child);
    }

    this->scope = this->scope->parent;
    this->_namespace = this->_namespace->parent;

    return nullptr;
}

data_ptr Executor::visit_calc(astnode_ptr &node) {
    auto left = this->visit((*node->children)[0]);
    auto right = this->visit((*node->children)[1]);
    auto data = CalcOperations::operate(left, right, node->token->type);
    if (!data) throw std::invalid_argument("Operation " + std::string(left->type)
        + " " + *node->token->lexeme + " " + std::string(right->type) + " is not defined");

    return data;
}

data_ptr Executor::visit_assign(astnode_ptr &node) {
    auto &left = (*node->children)[0];
    auto right = this->visit((*node->children)[1]);
    auto symbol = this->scope->lookup(*left->token->lexeme);
    if (!symbol) throw std::runtime_error("Symbol " + *node->token->lexeme + " has not been declared yet");
    if (symbol->is_const && this->_namespace->retrieve(symbol))
        throw std::runtime_error(("Const symbol " + *symbol->name + " cannot be reassigned"));
    AssignOperations::operate(symbol, right, node->token->type, this->_namespace);

    return nullptr;
}

data_ptr Executor::visit(astnode_ptr &node) {
    auto visit_func = Executor::visitor_map[node->type];
    return (this->*visit_func)(node);
}

void Executor::execute(astnode_ptr &root) {
    auto data = this->visit(root);
    if (this->repl && data) std::cout << data->display() << std::endl;
}
