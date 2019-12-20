#include "Token.h"


Token::Token(TokenType type, int length, int line, int column, Symbol* symbol) {
    this->type = type;
    this->length = length;
    this->line = line;
    this->column = column;
    this->symbol = symbol;
}

Symbol::Symbol(void* data) {
    this->data = data;
}
