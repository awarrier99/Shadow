#include "Token.h"


Token::Token(TokenType type, Symbol* symbol) {
    this->type = type;
    this->line = 0;
    this->column = 0;
    this->symbol = symbol;
}

Symbol::Symbol(void* data) {
    this->data = data;
}
