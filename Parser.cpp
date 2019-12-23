#include <iostream>
#include "Parser.h"
#include<fstream>
#include<string>

Token* Parser::get_token(TokenList& token_list) {
    Token* tok = token_list.at(0);
    return tok;
}



