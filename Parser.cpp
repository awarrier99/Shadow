#include <iostream>
#include "Parser.h"
#include<fstream>
#include<string>

Token* Parser::get_token(TokenList* token_list) {
//    Token* tok = token_list->at(2);
    for (Token* token: *token_list) { // test
        switch(token->type) {
            case NUMBER:
                std::cout << "This token is a number ";
                break;
        }
    }
}



