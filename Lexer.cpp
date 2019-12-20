#include <iostream>
#include "Lexer.h"


std::vector<TokenList*>* Lexer::lex(std::string* source) {
//    std::string line;
    return new std::vector<TokenList*> { lex_line(source) };
}

TokenList* Lexer::lex_line(std::string* line) {
    TokenList* token_list = new TokenList {};
    int i = 0;
//    while (i < line->length()) {
//        char ch = (*line)[i];
//        i++;
//    }
    token_list->add(Lexer::extract_token(line, &i));

    return token_list;
}

Token* Lexer::extract_token(std::string* line, int* i) {
    char ch = (*line)[*i];
    (*i)++;
    Token* token;
    TokenType type = get_type(ch);
    switch(type) {
        case NUMBER:
            token = Lexer::extract_number(line, i, ch);
            break;
        case IDENT:
            break;
        case STRING:
            break;
        case OP:
            break;
        case SEP:
            break;
        case INVALID:
            break;
    }

    return token;
}

Token* Lexer::extract_number(std::string* line, int* i, char first) { // TODO: support floats
    std::string num_str = std::string(1, first);
    char ch = (*line)[*i];
    while (get_type(ch) == NUMBER) {
        num_str += ch;
        (*i)++;
        ch = (*line)[*i];
    }

    int num = std::stoi(num_str);
    std::cout << "hello" << std::endl;
    Symbol sym = Symbol(reinterpret_cast<void *>(num));
    std::cout << "hello2" << std::endl;
    std::cout << "Data: " << *((int*) sym.data) << std::endl;
    Token* token = new Token(NUMBER, 32, 0, *i, sym);

    return token;
}

TokenType get_type(char ch) {
//    int extra_ident_codes[] = {}; TODO: allow for non alpha characters in identifier
    int op_codes[] = {37, 42, 43, 45, 60, 61, 62}; // TODO: add more operators, allow for += and other combos
    int code = (int) ch;
    if (code >= 48 && code <= 57) return NUMBER;
    if ((code >= 65 && code <= 90) || (code >= 97 && code <= 122)) return IDENT; // TODO: allow for non alpha characters in identifier
    if (code == 34) return STRING;
    if (std::find(std::begin(op_codes), std::end(op_codes), code) != std::end(op_codes)) return OP;
    if (code == 40 || code == 41 || code == 59) return SEP;
    return INVALID;
}