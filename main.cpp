#include <iostream>
#include <string>
#include "Lexer.h"

int main() {
    std::string source = "str = \"hello world\";"
                         "num = 123 + 456;";
    std::vector<TokenList*>* all_token_lists = Lexer::lex(&source);
    TokenList* token_list = (*all_token_lists)[0];
    for (Token* token: *token_list) { // test
        switch(token->type) {
            case NUMBER:
                std::cout << "Type: NUMBER" << " Length: " << token->length << " Line: " << token->line << " Column: " <<
                          token->column << " Symbol: " <<  *((int*) token->symbol->data) << std::endl;
                break;
            case STRING:
                std::cout << "Type: STRING" << " Length: " << token->length << " Line: " << token->line << " Column: " <<
                          token->column << " Symbol: " <<  *((std::string*) token->symbol->data) << std::endl;
                break;
            case IDENT:
                std::cout << "Type: IDENT" << " Length: " << token->length << " Line: " << token->line << " Column: " <<
                          token->column << " Symbol: " <<  *((std::string*) token->symbol->data) << std::endl;
                break;
            case OP:
                std::cout << "Type: OP" << " Length: " << token->length << " Line: " << token->line << " Column: " <<
                          token->column << " Symbol: " <<  *((std::string*) token->symbol->data) << std::endl;
                break;
            case SEP:
                std::cout << "Type: SEP" << " Length: " << token->length << " Line: " << token->line << " Column: " <<
                          token->column << " Symbol: " <<  *((char*) token->symbol->data) << std::endl;
                break;
            case INVALID:
                std::cout << "Invalid token" << std::endl;
                break;
        }
    }
    return 0;
}
