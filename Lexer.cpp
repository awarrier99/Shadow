#include <iostream>
#include "Lexer.h"


std::vector<TokenList*>* Lexer::lex(std::string* source) {
//    std::string line;
    return new std::vector<TokenList*> { lex_line(source) };
}

//adds the token to the end of TokenList
TokenList* Lexer::lex_line(std::string* line) {
    auto* token_list = new TokenList {};
    int i = 0;
    while (i < line->length()) {
        token_list->push_back(Lexer::extract_token(line, &i));
    }

    return token_list;
}
//extract token by line number excluding white space and new lines
Token* Lexer::extract_token(std::string* line, int* i) {
    char ch = (*line)[*i];
    while (ch == ' ' || ch == '\n' || ch == '\t') {
        (*i)++;
        ch = (*line)[*i];
    }
    (*i)++;
    Token* token;
    TokenType type = get_type(ch);
    switch(type) {
        case NUMBER:
            token = Lexer::extract_number(line, i, ch, *i - 1);
            break;
        case STRING:
            break;
        case IDENT:
            token = Lexer::extract_ident(line, i, ch, *i - 1);
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

Token* Lexer::extract_number(std::string* line, int* i, char first_ch, int first_i) { // TODO: support floats
    std::string num_str = std::string(1, first_ch);
    char ch = (*line)[*i];
    while (get_type(ch) == NUMBER) {
        num_str += ch;
        (*i)++;
        ch = (*line)[*i];
    }

    auto* num = new int;
    *num = std::stoi(num_str);
    auto* sym = new Symbol((void*) num);
    return new Token(NUMBER, 32, 0, first_i, sym); // TODO: implement line number
}

Token* Lexer::extract_ident(std::string* line, int* i, char first_ch, int first_i) {
    auto* ident = new std::string(1, first_ch);
    char ch = (*line)[*i];
    while (get_type(ch) == IDENT) {
        *ident += ch;
        (*i)++;
        ch = (*line)[*i];
    }

    auto* sym = new Symbol((void*) ident);
    return new Token(IDENT, 0, 0, first_i, sym);
}

TokenType get_type(char ch) {
//    int extra_ident_codes[] = {}; TODO: allow for non alpha characters in identifier
    int op_codes[] = {37, 42, 43, 45, 60, 61, 62}; // TODO: add more operators, allow for += and other combos
    int code = (int) ch;
    if (code >= 48 && code <= 57) return NUMBER;
    if (code == 34) return STRING;
    if ((code >= 65 && code <= 90) || (code >= 97 && code <= 122)) return IDENT; // TODO: allow for non alpha characters in identifier
    if (std::find(std::begin(op_codes), std::end(op_codes), code) != std::end(op_codes)) return OP;
    if (code == 40 || code == 41 || code == 59) return SEP;
    return INVALID;
}