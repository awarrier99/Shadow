#include "Lexer.h"


TokenList* Lexer::lex_instruction() {
    auto* token_list = new TokenList();
    this->offset = 0;
    while (true) {
        Token* token = Lexer::extract_token();
        token_list->push_back(token);
        if (token->type == INVALID) break;
        if (token->type == SEP && *token->symbol->data == ";") break;
    }
    this->cursor += this->offset;

    return token_list;
}

Token* Lexer::extract_token() {
    char ch = (*this->instruction)[this->offset];
    while (ch == ' ' || ch == '\n' || ch == '\t') {
        this->offset++;
        ch = (*this->instruction)[this->offset];
    }
    int col = this->cursor + this->offset;
    this->offset++;

    Token* token;
    TokenType type = get_type(ch);
    switch(type) {
        case NUMBER:
            token = Lexer::extract_number(ch);
            break;
        case STRING:
            token = Lexer::extract_string();
            break;
        case IDENT:
            token = Lexer::extract_ident(ch);
            break;
        case OP:
            token = Lexer::extract_op(ch);
            break;
        case SEP:
            token = Lexer::extract_sep(ch);
            break;
        default:
            token = new Token(INVALID, nullptr);
            break;
    }
    token->line = this->line_num;
    token->column = col;

    return token;
}

Token* Lexer::extract_number(char first_ch) { // TODO: support floats
    auto* data = new std::string(1, first_ch);
    char ch = (*this->instruction)[this->offset];
    while (get_type(ch) == NUMBER) {
        *data += ch;
        this->offset++;
        ch = (*this->instruction)[this->offset];
    }

    return new Token(NUMBER, new Symbol(data));
}

Token* Lexer::extract_string() {
    auto* data = new std::string();
    char ch = (*this->instruction)[this->offset];
    while (get_type(ch) != STRING) { // TODO: support escape chars
        *data += ch;
        this->offset++;
        ch = (*this->instruction)[this->offset];
    }
    this->offset++; // so we don't recheck the end quote

    return new Token(STRING, new Symbol(data));
}

Token* Lexer::extract_ident(char first_ch) {
    auto* data = new std::string(1, first_ch);
    char ch = (*this->instruction)[this->offset];
    while (get_type(ch) == IDENT) {
        *data += ch;
        this->offset++;
        ch = (*this->instruction)[this->offset];
    }

    return new Token(IDENT, new Symbol(data));
}

Token* Lexer::extract_op(char first_ch) {
    auto* data = new std::string(1, first_ch);
    return new Token(OP, new Symbol(data));
}

Token* Lexer::extract_sep(char first_ch) {
    auto* data = new std::string(1, first_ch);
    return new Token(SEP, new Symbol(data));
}

TokenType get_type(char ch) {
//    int extra_ident_codes[] = {}; TODO: allow for non alpha characters in identifier
    //%,*,+,-,/,<,=,>
    int op_codes[] = {37, 42, 43, 45, 47, 60, 61, 62}; // TODO: add more operators, allow for += and other combos
    int code = (int) ch;
    if (code == 46 || (code >= 48 && code <= 57)) return NUMBER;
    if (code == 34) return STRING;
    if ((code >= 65 && code <= 90) || (code >= 97 && code <= 122)) return IDENT; // TODO: allow for non alpha characters in identifier
    if (std::find(std::begin(op_codes), std::end(op_codes), code) != std::end(op_codes)) return OP;
    // (,),;
    if (code == 40 || code == 41 || code == 59) return SEP;
    return INVALID;
}