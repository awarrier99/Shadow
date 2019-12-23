#ifndef FYE_PARSER_H
#define FYE_PARSER_H


#include <vector>
#include <string>
#include <map>
#include "Token.h"
#include "Lexer.h"

//should have the token list, and each tokens type and symbol
//
class Parser {

//want to pass in a token list
public:
    static Token* get_token(TokenList& token_list);

};

class ParseTree : public std::map<int, Token> {};

//class node {
//public:
//    int data;
//    class node* left;
//    class node* right;
//};






#endif //FYE_PARSER_H
