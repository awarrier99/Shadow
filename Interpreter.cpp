#include "Interpreter.h"


Interpreter::Interpreter(std::ifstream* source_file) {
    this->source_file = source_file;
    this->lexer = new Lexer();
    this->parser = new Parser();
}

void Interpreter::pipeline() {
    char ch;
    std::stringstream buffer;
    std::string instruction;
    this->lexer->instruction = &instruction;
    this->lexer->line_num = 1;
    this->lexer->cursor = 0;
    this->lexer->offset = 0;

    TokenType type = IDENT; // arbitrary, just so it's not invalid
    while (type != INVALID) {
        *this->source_file >> std::noskipws >> ch;
        if (this->source_file->eof()) break;

        buffer << ch;

        if (ch == '\n') {
            this->lexer->line_num++;
            this->lexer->cursor = 0;
        }
        else if (ch == ';') {
            instruction = buffer.str();
            buffer.str(std::string());

            auto* token_list = this->lexer->lex_instruction();
            type = token_list->back()->type;

            debug::print_token_list(token_list);
        }
    }
}
