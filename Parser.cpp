#include <iostream>
#include "Parser.h"
#include<fstream>
#include<string>

Token* Parser::get_token(TokenList* token_list) {
//    Token* tok = token_list->at(2);
    int num;
    std::string ops;

    for (Token* token: *token_list) { // test
        switch(token->type) {
            case NUMBER:
                num = *(int*)token->symbol->data;
                std::cout <<num<< std::endl;
                break;
            case STRING: //temporarily commenting out will come back after numbers
//                std::cout <<*(std::string*)token->symbol->data << std::endl;
                break;
            case IDENT:
//                std::cout <<*(std::string*)token->symbol->data << std::endl;
                break;
            case OP:
                ops = *(std::string*)token->symbol->data;
                std::cout <<ops<< std::endl;
                break;
            case SEP:
                std::cout << *(char*)token->symbol->data << std::endl;
                break;
            case INVALID:
                break;
        }
    }



}



