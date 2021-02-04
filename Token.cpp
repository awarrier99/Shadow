#include "Token.h"


Token::Token(TokenType type, Symbol* symbol): type(type), line(0), column(0), symbol(symbol) {}

//Token::~Token() {
//    if (this->type == NUMBER) {
//        delete (int*) this->symbol->data;
//    } else if (this->type == STRING || this->type == IDENT || this->type == OP) {
//        delete (std::string*) this->symbol->data;
//    } else if (this->type == SEP) {
//        delete (char*) this->symbol->data;
//    }
//    this->symbol->data = nullptr;
//    delete this->symbol;
//    this->symbol = nullptr;
//    std::cout << "Token cleared" << std::endl;
//}

TokenList::~TokenList() {
    for (Token* token: *this) {
        delete token;
        token = nullptr;
    }
    this->clear();
    this->shrink_to_fit();
}
