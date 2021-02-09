#include "Token.h"


Token::Token(const char* type, std::unique_ptr<std::string> &lexeme): type(type), line(0), column(0), lexeme(std::move(lexeme)) {}
