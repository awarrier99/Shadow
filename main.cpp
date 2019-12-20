#include <iostream>
#include <string>
#include "Lexer.h"

int main() {
    std::string source = "hello 123 world";
    std::vector<TokenList*>* all_token_lists = Lexer::lex(&source);
    TokenList* token_list = (*all_token_lists)[0];
    for (Token* token: *token_list) { // test
        switch(token->type) {
            case NUMBER:
                std::cout << "Type: " << token->type << " Length: " << token->length << " Line: " << token->line << " Column: " <<
                          token->column << " Symbol: " <<  *((int*) token->symbol->data) << std::endl;
                break;
            case STRING:
                break;
            case IDENT:
                std::cout << "Type: " << token->type << " Length: " << token->length << " Line: " << token->line << " Column: " <<
                          token->column << " Symbol: " <<  *((std::string*) token->symbol->data) << std::endl;
                break;
            case OP:
                break;
            case SEP:
                break;
            case INVALID:
                break;
        }
    }
    return 0;
}
