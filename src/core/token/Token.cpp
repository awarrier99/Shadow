#include "Token.h"


Token::Token(const char* type, string_ptr &lexeme): type(type), line(0), column(0), lexeme(lexeme) {}
