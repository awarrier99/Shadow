#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "A source file must be provided!" << std::endl;
        return 1;
    }
    char* source_file = argv[1];
    std::ifstream file(source_file);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str(); // TODO: read incrementally rather than storing entire contents in memory

    TokenList* token_list = Lexer::lex(&source);
    Token* tok = Parser::get_token(token_list);
//    std::cout << "Tok " << &tok  << std::endl;

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
    return 0;
}
