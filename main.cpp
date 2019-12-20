#include <iostream>
#include <string>
#include "Lexer.h"

int main() {
    std::string source = "534";
    std::vector<TokenList*>* all_token_lists = Lexer::lex(&source);
    Token* token = (*all_token_lists)[0]->get(0);
    std::cout << "Type: " << token->type << " Length: " << token->length << " Line: " << token->line << " Column: " <<
        token->column << " Data: " <<  *((int*) token->symbol->data) << std::endl; // test
    return 0;
}
