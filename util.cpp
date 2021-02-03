#include "util.h"


void debug::print_token_list(TokenList* token_list) {
    for (Token* token: *token_list) { // test
        switch(token->type) {
            case NUMBER:
                std::cout << "Type: NUMBER" << " Line: " << token->line <<
                          " Column: " << token->column << " Symbol: " << *((int*) token->symbol->data) << std::endl;
                break;
            case STRING:
                std::cout << "Type: STRING" << " Line: " << token->line <<
                          " Column: " << token->column << " Symbol: " << *((std::string*) token->symbol->data) << std::endl;
                break;
            case IDENT:
                std::cout << "Type: IDENT" << " Line: " << token->line <<
                          " Column: " << token->column << " Symbol: " << *((std::string*) token->symbol->data) << std::endl;
                break;
            case OP:
                std::cout << "Type: OP" << " Line: " << token->line <<
                          " Column: " << token->column << " Symbol: " << *((std::string*) token->symbol->data) << std::endl;
                break;
            case SEP:
                std::cout << "Type: SEP" << " Line: " << token->line <<
                          " Column: " << token->column << " Symbol: " << *((char*) token->symbol->data) << std::endl;
                break;
            case INVALID:
                std::cout << "Type: INVALID" << " Line: " << token->line << " Column: " << token->column << std::endl;
                break;
        }
    }
}
