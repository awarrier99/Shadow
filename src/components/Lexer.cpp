#include "Lexer.h"


Lexer::Lexer(std::istream* source): source(source), line_num(1), cursor(-1) {
    this->operators = {'%', '*', '+', '-', '/', '<', '=', '>'};
    this->separators = {
            {'(', TokenType::LPAREN},
            {')', TokenType::RPAREN},
            {';', TokenType::SEMI},
            {',', TokenType::COMMA},
            {'[', TokenType::LBRACKET},
            {']', TokenType::RBRACKET},
            {'{', TokenType::LBRACE},
            {'}', TokenType::RBRACE}
    };
    this->read();
}

void Lexer::read() {
    if (this->_next == '\0') *this->source >> std::noskipws >> this->ch;
    else {
        this->ch = this->_next;
        this->_next = '\0';
    }
    this->cursor++;
}

char Lexer::peek() {
    *this->source >> std::noskipws >> this->_next;
    return this->_next;
}

bool is_alpha(char ch) {
    int code = (int) (unsigned char) ch;
    return (code >= 65 && code <= 90) || (code >= 97 && code <= 122);
}

bool is_digit(char ch) {
    int code = (int) (unsigned char) ch;
    return code >= 48 && code <= 57;
}

bool is_alpha_num(char ch) {
    return is_alpha(ch) || is_digit(ch);
}

token_ptr Lexer::extract_token() {
    if (!*this->source) {
        string_ptr lexeme = nullptr;
        return std::make_shared<Token>(Token(TokenType::FEOF, lexeme));
    }

    while (this->ch == ' ' || this->ch == '\n' || this->ch == '\t') {
        if (this->ch == '\n') this->line_num++;
        this->read();
    }

    int col = this->cursor;
    token_ptr token;


    if (this->ch == '.') {
        token = this->extract_number(true);
    } else if (is_digit(this->ch)) {
        token = this->extract_number(false);
    } else if (this->ch == '\'' || this->ch == '"') {
        token = this->extract_string();
    } else if (is_alpha(this->ch)) {
        token = this->extract_ident();
    } else if (operators.find(this->ch) != operators.end()) {
        token = this->extract_op();
        this->read();
    } else if (separators.find(this->ch) != separators.end()) {
        token = this->extract_sep();
        this->read();
    } else {
        string_ptr lexeme = nullptr;
        token = std::make_shared<Token>(Token(TokenType::INVALID, lexeme));
    }

    token->column = col;
    token->line = this->line_num;
    return token;
}

token_ptr Lexer::extract_number(bool period_flag) {
    auto lexeme = std::make_shared<std::string>(std::string(1, this->ch));
    this->read();
    while ((!period_flag && this->ch == '.') || is_digit(this->ch)) {
        if (this->ch == '.') period_flag = true;
        *lexeme += this->ch;
        this->read();
    }

    return std::make_shared<Token>(Token(TokenType::NUMBER, lexeme));
}

token_ptr Lexer::extract_string() {
    auto lexeme = std::make_shared<std::string>(std::string());
    char first_ch = this->ch;
    this->read();
    while (this->ch != first_ch) { // TODO: support escape chars
        *lexeme += this->ch;
        this->read();
    }
    this->read(); // so we don't recheck the end quote

    return std::make_shared<Token>(Token(TokenType::STRING, lexeme));
}

token_ptr Lexer::extract_ident() {
    auto lexeme = std::make_shared<std::string>(std::string(1, this->ch));
    this->read();
    while (is_alpha_num(this->ch)) {
        *lexeme += ch;
        this->read();
    }

    std::map<std::string, const char*> keywords = {
            {"const", TokenType::CONST},
            {"def", TokenType::DEF},
            {"func", TokenType::FUNC}
    };
    auto it = keywords.find(*lexeme);
    if (it != keywords.end()) return std::make_shared<Token>(Token(it->second, lexeme));

    return std::make_shared<Token>(Token(TokenType::IDENT, lexeme));
}

token_ptr Lexer::extract_op() {
    auto lexeme = std::make_shared<std::string>(std::string(1, this->ch));

    if (this->ch == '+') {
        if (this->peek() == '=') {
            this->read();
            *lexeme += this->ch;
            return std::make_shared<Token>(Token(TokenType::PLUSEQ, lexeme));
        }
        return std::make_shared<Token>(Token(TokenType::PLUS, lexeme));
    }

    if (this->ch == '-') {
        if (this->peek() == '=') {
            this->read();
            *lexeme += this->ch;
            return std::make_shared<Token>(Token(TokenType::MINUSEQ, lexeme));
        }
        return std::make_shared<Token>(Token(TokenType::MINUS, lexeme));
    }

    if (this->ch == '*') {
        if (this->peek() == '=') {
            this->read();
            *lexeme += this->ch;
            return std::make_shared<Token>(Token(TokenType::MULEQ, lexeme));
        } else if (this->_next == '*') {
            this->read();
            *lexeme += this->ch;
            if (this->peek() == '=') {
                this->read();
                *lexeme += this->ch;
                return std::make_shared<Token>(Token(TokenType::EXPEQ, lexeme));
            }
            return std::make_shared<Token>(Token(TokenType::EXP, lexeme));
        }
        return std::make_shared<Token>(Token(TokenType::MUL, lexeme));
    }

    if (this->ch == '/') {
        if (this->peek() == '=') {
            this->read();
            *lexeme += this->ch;
            return std::make_shared<Token>(Token(TokenType::DIVEQ, lexeme));
        }
        return std::make_shared<Token>(Token(TokenType::DIV, lexeme));
    }

    if (this->ch == '%') {
        if (this->peek() == '=') {
            this->read();
            *lexeme += this->ch;
            return std::make_shared<Token>(Token(TokenType::MODEQ, lexeme));
        }
        return std::make_shared<Token>(Token(TokenType::MOD, lexeme));
    }

    if (this->ch == '=') {
        if (this->peek() == '=') {
            this->read();
            *lexeme += this->ch;
            return std::make_shared<Token>(Token(TokenType::EQEQ, lexeme));
        }
        return std::make_shared<Token>(Token(TokenType::EQ, lexeme));
    }

    return std::make_shared<Token>(Token(TokenType::INVALID, lexeme));
}

token_ptr Lexer::extract_sep() {
    auto lexeme = std::make_shared<std::string>(std::string(1, this->ch));
    return std::make_shared<Token>(Token(this->separators[this->ch], lexeme));
}
