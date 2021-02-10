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
    debug::print_token(this->token);
    if (this->token->type == type) this->token = this->lexer.extract_token();
}

std::unique_ptr<ASTNode> Parser::parse_expression() {
    std::stack<std::unique_ptr<ASTNode>> expr_stack;
    std::stack<std::shared_ptr<Token>> op_stack;

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

std::unique_ptr<ASTNode> Parser::parse_declaration() {
    auto keyword_token = this->token;
    this->consume(this->token->type);
    auto nodes = std::make_unique<ASTNodeList>(ASTNodeList());
    auto ident = this->token;
    if (keyword_token->type == TokenType::CONST) {
        nodes->push_back(this->parse_expression());
        return std::make_unique<VarDecNode>(VarDecNode(keyword_token, nodes, ident));
    }

    if (this->token->type != TokenType::SEMI) nodes->push_back(this->parse_expression());
    return std::make_unique<VarDecNode>(VarDecNode(keyword_token, nodes, ident));
}

std::unique_ptr<ASTNode> Parser::parse_statement() {
    auto &type = this->token->type;
    if (type == TokenType::NUMBER || type == TokenType::STRING || type == TokenType::IDENT) return this->parse_expression();
    if (type == TokenType::CONST || type == TokenType::DEF) return this->parse_declaration();
    return nullptr;
}

void Parser::parse() {
    auto executor = Executor();

    this->token = this->lexer.extract_token();
    while (true) {
        if (this->token->type == TokenType::INVALID || this->token->type == TokenType::FEOF) break;

        auto root = this->parse_statement();
        if (root) executor.execute(root);
    }
}
