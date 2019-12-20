#include "Token.h"

int TokenList::size() {
    return this->_size;
}

void TokenList::add(Token* token) {
    this->list.push_back(token);
    this->_size++;
}

Token* TokenList::get(int i) {
    return this->list[i];
}

Token::Token(TokenType type, int length, int line, int column, Symbol symbol) {
    this->type = type;
    this->length = length;
    this->line = line;
    this->column = column;
    this->symbol = symbol;
}

Symbol::Symbol(void* data) {
    this->data = data;
}
