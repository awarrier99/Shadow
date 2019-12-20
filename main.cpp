#include <iostream>
#include <string>
#include "Lexer.h"

int main() {
    std::string source;
    std::vector<TokenList> all_token_lists = Lexer::lex(&source);
    std::cout << all_token_lists.front().size() << std::endl; // test
    return 0;
}
