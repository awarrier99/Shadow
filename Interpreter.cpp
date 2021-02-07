#include "Interpreter.h"


Interpreter::Interpreter(std::unique_ptr<std::ifstream> &source_file) { // TODO: lexing, parsing, and executing errors/exceptions
    this->source_file = std::move(source_file);
    this->lexer = std::make_unique<Lexer>(Lexer());
    this->parser = std::make_unique<Parser>(Parser());
    this->executor = std::make_unique<Executor>(Executor());
    this->executor->global = std::make_shared<Scope>(Scope());
}

void Interpreter::pipeline() {
    char ch;
    std::stringstream buffer;
    this->lexer->line_num = 1;
    this->lexer->cursor = 0;
    this->lexer->offset = 0;

    TokenType type = IDENT; // arbitrary, just so it's not invalid
    while (type != INVALID) {
        *this->source_file >> std::noskipws >> ch;
        if (this->source_file->eof()) break;

        if (ch == '\n') {
            this->lexer->line_num++;
            this->lexer->cursor = 0;
        }
        else if (ch == ';') {
            buffer << ch;
            this->lexer->instruction = std::make_unique<std::string>(buffer.str());
            auto token_list = this->lexer->lex_instruction();
            type = token_list->back()->type;
            buffer.str(std::string());

//            debug::print_token_list(token_list);

            this->parser->token_list = std::move(token_list);
            auto ast = this->parser->build_ast();

            this->executor->ast = std::move(ast);
            this->executor->build_ir();
            this->executor->execute_ir();
        } else {
            buffer << ch;
        }
    }
}
