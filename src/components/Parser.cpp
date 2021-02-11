#include "Parser.h"


Parser::Parser(Lexer &lexer): lexer(std::move(lexer)) {}

bool operator_has_higher_precedence(const char* type, std::shared_ptr<Token> &op_top) {
    if (op_top->type == TokenType::LPAREN) return false;

    std::map<const char*, int> precedence = {
            {TokenType::MUL, 3},
            {TokenType::DIV, 3},
            {TokenType::PLUS, 2},
            {TokenType::MINUS, 2},
            {TokenType::EQ, 1}
    };

    return precedence[op_top->type] >= precedence[type];
}

void build_expression(std::stack<std::unique_ptr<ASTNode>> &expr_stack, std::stack<std::shared_ptr<Token>> &op_stack) {
    auto op_token = op_stack.top();
    op_stack.pop();
    auto right_node = std::move(expr_stack.top());
    expr_stack.pop();
    auto left_node = std::move(expr_stack.top());
    expr_stack.pop();

    auto nodes = std::make_unique<ASTNodeList>(ASTNodeList());
    nodes->push_back(std::move(left_node));
    nodes->push_back(std::move(right_node));

    const char* type;
    if (std::string(op_token->type).find("EQ") == std::string::npos) type = ASTNodeType::CALC;
    else type = ASTNodeType::ASSIGN;

    expr_stack.push(std::make_unique<ASTNode>(ASTNode(type, op_token, nodes)));
}

void Parser::consume(const char* type) {
    if (this->token->type == type) this->token = this->lexer.extract_token();
    else throw std::invalid_argument("Unexpected token: " + std::string(this->token->type) + "; Expected: " + std::string(type));
}

void Parser::reject(const char* type) {
    if (this->token->type == type) throw std::invalid_argument("Unexpected token: " + std::string(type));
}

std::unique_ptr<ASTNode> Parser::parse_expression(std::shared_ptr<Token> tok) {
    std::stack<std::unique_ptr<ASTNode>> expr_stack;
    std::stack<std::shared_ptr<Token>> op_stack;

    if (tok) {
        expr_stack.push(std::make_unique<ASTNode>(ASTNode(ASTNodeType::IDENT, tok)));
    }

    this->reject(TokenType::SEMI);
    while (true) {
        auto &type = this->token->type;
        if (type == TokenType::LPAREN) {
            op_stack.push(this->token);
        } else if (type == TokenType::RPAREN) {
            while (!op_stack.empty() && *op_stack.top()->lexeme != "(") {
                build_expression(expr_stack, op_stack);
            }

            op_stack.pop();
        } else if (type == TokenType::NUMBER || type == TokenType::STRING || type == TokenType::IDENT) {
            expr_stack.push(std::make_unique<ASTNode>(ASTNode(type, this->token))); // in these cases, token type is same string as node type
        } else if (type == TokenType::SEMI) {
            break;
        } else {
            while (!op_stack.empty() && operator_has_higher_precedence(type, op_stack.top())) {
                build_expression(expr_stack, op_stack);
            }

            op_stack.push(this->token);
        }
        this->consume(type);
    }
    this->consume(TokenType::SEMI);

    while (!op_stack.empty()) {
        build_expression(expr_stack, op_stack);
    }

    auto root = std::move(expr_stack.top());
    expr_stack.pop();
    return root;
}

std::unique_ptr<ASTNode> Parser::parse_var_declaration() {
    auto keyword_token = this->token;
    this->consume(this->token->type);
    auto ident = this->token;
    this->consume(TokenType::IDENT);
    auto nodes = std::make_unique<ASTNodeList>(ASTNodeList());
    if (keyword_token->type == TokenType::CONST) {
        nodes->push_back(this->parse_expression(ident));
        return std::make_unique<VarDecNode>(VarDecNode(keyword_token, nodes, ident));
    }

    if (this->token->type != TokenType::SEMI) nodes->push_back(this->parse_expression(ident));
    else this->consume(TokenType::SEMI);
    return std::make_unique<VarDecNode>(VarDecNode(keyword_token, nodes, ident));
}

std::unique_ptr<ASTNodeList> Parser::parse_parameter_list() {
    std::unique_ptr<ASTNodeList> nodes = nullptr;
    if (this->token->type == TokenType::RPAREN) return nodes;

    nodes = std::make_unique<ASTNodeList>(ASTNodeList());
    std::shared_ptr<Token> keyword_token = nullptr;
    std::unique_ptr<ASTNodeList> param_nodes = nullptr;

    while (true) {
        nodes->push_back(std::make_unique<VarDecNode>(VarDecNode(keyword_token, param_nodes, this->token)));
        this->consume(TokenType::IDENT);
        if (this->token->type == TokenType::RPAREN) break;
        this->consume(TokenType::COMMA);
    }
    return nodes;
}

std::unique_ptr<ASTNode> Parser::parse_func_declaration() {
    auto tok = this->token;
    this->consume(TokenType::FUNC);
    auto ident = this->token;
    this->consume(TokenType::IDENT);

    this->consume(TokenType::LPAREN);
    auto params = this->parse_parameter_list();
    this->consume(TokenType::RPAREN);

    this->consume(TokenType::LBRACE);
    auto nodes = std::make_unique<ASTNodeList>(ASTNodeList());
    while (this->token->type != TokenType::RBRACE) {
        nodes->push_back(this->parse_statement());
    }
    this->consume(TokenType::RBRACE);
    return std::make_unique<FuncDecNode>(FuncDecNode(tok, nodes, ident, params));
}

std::unique_ptr<ASTNode> Parser::parse_statement() {
    auto &type = this->token->type;
    if (type == TokenType::NUMBER || type == TokenType::STRING || type == TokenType::IDENT) return this->parse_expression();
    if (type == TokenType::CONST || type == TokenType::DEF) return this->parse_var_declaration();
    if (type == TokenType::FUNC) return this->parse_func_declaration();
    return nullptr;
}

void Parser::parse() {
    auto executor = Executor();

    this->token = this->lexer.extract_token();
    while (true) {
        if (this->token->type == TokenType::INVALID || this->token->type == TokenType::FEOF) break;

        auto root = this->parse_statement();
        debug::print_ast_node(root);
        if (root) executor.execute(root);
    }
}
