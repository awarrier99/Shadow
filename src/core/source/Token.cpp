#include "Token.h"


Token::Token(TokenType type, std::unique_ptr<Symbol> symbol): type(type), line(0), column(0), symbol(std::move(symbol)) {}
