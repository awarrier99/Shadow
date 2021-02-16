#include "Parser.h"


Parser::Parser(Lexer &lexer): lexer(std::move(lexer)) {}

bool operator_has_higher_precedence(const char* type, token_ptr &op_top) {
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

void build_expression(std::stack<astnode_ptr> &expr_stack, std::stack<token_ptr> &op_stack) {
    auto op_token = op_stack.top();
    op_stack.pop();
    auto right_node = std::move(expr_stack.top());
    expr_stack.pop();
    auto left_node = std::move(expr_stack.top());
    expr_stack.pop();

    auto children = std::make_unique<ASTNodeList>(ASTNodeList());
    children->push_back(std::move(left_node));
    children->push_back(std::move(right_node));

    const char* type;
    if (std::string(op_token->type).find("EQ") == std::string::npos) type = ASTNodeType::CALC;
    else type = ASTNodeType::ASSIGN;

    expr_stack.push(std::make_unique<ASTNode>(ASTNode(type, op_token, children)));
}

void Parser::consume(const char* type) {
    if (this->token->type == type) this->token = this->lexer.extract_token();
    else throw std::invalid_argument("Unexpected token: " + std::string(this->token->type) + "; Expected: " + std::string(type));
}

void Parser::reject(const char* type) {
    if (this->token->type == type) throw std::invalid_argument("Unexpected token: " + std::string(type));
}

astnodelist_ptr Parser::parse_func_arguments() {
    astnodelist_ptr children = std::make_unique<ASTNodeList>(ASTNodeList());
    if (this->token->type == TokenType::RPAREN) return children;
    while (true) {
        children->push_back(this->parse_expression(nullptr, true));
        if (this->token->type == TokenType::RPAREN) break;
        this->consume(TokenType::COMMA);
    }

    return children;
}

astnode_ptr Parser::parse_expression(token_ptr tok, bool arguments) {
    std::stack<astnode_ptr> expr_stack;
    std::stack<token_ptr> op_stack;

    if (tok) {
        expr_stack.push(std::make_unique<ASTNode>(ASTNode(ASTNodeType::IDENT, tok)));
    }

    this->reject(TokenType::SEMI);
    while (true) {
        auto type = this->token->type;
        if (type == TokenType::LPAREN) {
            op_stack.push(this->token);
            this->consume(TokenType::LPAREN);
        } else if (type == TokenType::RPAREN) {
            if (arguments) break;
            while (!op_stack.empty() && *op_stack.top()->lexeme != "(") {
                build_expression(expr_stack, op_stack);
            }

            op_stack.pop();
            this->consume(TokenType::RPAREN);
        } else if (type == TokenType::IDENT) {
            if (this->lexer.ch == '(') {
                auto ident = this->token;
                this->consume(TokenType::IDENT);
                this->consume(TokenType::LPAREN);
                auto children = this->parse_func_arguments();
                this->consume(TokenType::RPAREN);
                expr_stack.push(std::make_unique<ASTNode>(ASTNode(ASTNodeType::FUNCCALL, ident, children)));
            } else {
                expr_stack.push(std::make_unique<ASTNode>(ASTNode(type, this->token)));
                this->consume(TokenType::IDENT);
            }
        } else if (type == TokenType::NUMBER || type == TokenType::STRING) {
            expr_stack.push(std::make_unique<ASTNode>(ASTNode(type, this->token))); // in these cases, token type is same string as node type
            this->consume(type);
        } else if (type == TokenType::SEMI || type == TokenType::COMMA) {
            break;
        } else {
            while (!op_stack.empty() && operator_has_higher_precedence(type, op_stack.top())) {
                build_expression(expr_stack, op_stack);
            }

            op_stack.push(this->token);
            this->consume(type);
        }
    }

    while (!op_stack.empty()) {
        build_expression(expr_stack, op_stack);
    }

    auto root = std::move(expr_stack.top());
    expr_stack.pop();
    return root;
}

astnode_ptr Parser::parse_var_declaration(const char* &end) {
    auto keyword_token = this->token;
    this->consume(this->token->type);
    auto ident = this->token;
    this->consume(TokenType::IDENT);
    auto children = std::make_unique<ASTNodeList>(ASTNodeList());
    if (keyword_token->type == TokenType::CONST) {
        children->push_back(this->parse_expression(ident));
        end = TokenType::SEMI;
        return astnode_ptr(new VarDecNode(keyword_token, children, ident));
    }

    if (this->token->type != TokenType::SEMI) children->push_back(this->parse_expression(ident));
    end = TokenType::SEMI;
    return astnode_ptr(new VarDecNode(keyword_token, children, ident));
}

astnodelist_ptr Parser::parse_parameter_list() {
    astnodelist_ptr children = std::make_unique<ASTNodeList>(ASTNodeList());
    if (this->token->type == TokenType::RPAREN) return children;

    token_ptr keyword_token = nullptr;
    astnodelist_ptr param_children = nullptr;

    while (true) {
        children->push_back(astnode_ptr(new VarDecNode(keyword_token, param_children, this->token)));
        this->consume(TokenType::IDENT);
        if (this->token->type == TokenType::RPAREN) break;
        this->consume(TokenType::COMMA);
    }
    return children;
}

astnode_ptr Parser::parse_func_declaration(const char* &end) {
    auto tok = this->token;
    this->consume(TokenType::FUNC);
    auto ident = this->token;
    this->consume(TokenType::IDENT);

    this->consume(TokenType::LPAREN);
    auto params = this->parse_parameter_list();
    this->consume(TokenType::RPAREN);

    this->consume(TokenType::LBRACE);
    auto children = std::make_unique<ASTNodeList>(ASTNodeList());
    while (this->token->type != TokenType::RBRACE) {
        const char* end_null = nullptr;
        children->push_back(this->parse_statement(end_null));
    }
    end = TokenType::RBRACE;
    return astnode_ptr(new FuncDecNode(tok, children, ident, params));
}

astnode_ptr Parser::parse_statement(const char* &end) {
    auto &type = this->token->type;
    if (type == TokenType::NUMBER || type == TokenType::STRING || type == TokenType::IDENT) {
        auto node = this->parse_expression();
        if (end) end = TokenType::SEMI;
        else this->consume(TokenType::SEMI);
        return node;
    }
    if (type == TokenType::CONST || type == TokenType::DEF) {
        if (end) return this->parse_var_declaration(end);
        auto node = this->parse_var_declaration(end);
        this->consume(end);
        return node;
    }
    if (type == TokenType::FUNC) {
        if (end) return this->parse_func_declaration(end);
        auto node = this->parse_func_declaration(end);
        this->consume(end);
        return node;
    }
    return nullptr;
}

void Parser::parse(bool repl) {
    auto executor = Executor(repl);
    executor.load_builtins();

    this->token = this->lexer.extract_token();
    while (true) {
        if (this->token->type == TokenType::INVALID || this->token->type == TokenType::FEOF) break;

        const char* type;
        auto root = this->parse_statement(type);
//        debug::print_ast_node(root);
        if (root) executor.execute(root);
        if (repl) std::cout << "> ";
        this->consume(type);
    }
}
