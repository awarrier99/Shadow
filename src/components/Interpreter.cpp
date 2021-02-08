#include "Interpreter.h"


Interpreter::Interpreter() {
    this->lexer = std::make_unique<Lexer>(Lexer());
    this->parser = std::make_unique<Parser>(Parser());
    this->executor = std::make_unique<Executor>(Executor());
    this->executor->global = std::make_shared<Scope>(Scope());
}

Interpreter::Interpreter(std::unique_ptr<std::ifstream> &source_file): Interpreter() { // TODO: lexing, parsing, and executing errors/exceptions
    this->source_file = std::move(source_file);
}

void Interpreter::pipeline(bool repl) {
    char ch;
    std::stringstream buffer;

    if (repl) {
        std::cout << "> ";
    }
    auto &source = repl ? std::cin : *this->source_file;
    while (source >> std::noskipws >> ch) {
        if (ch == '\n') {
            this->lexer->line_num++;
            this->lexer->cursor = 0;
            if (repl) {
                std::cout << "> ";
            }
        }
        else if (ch == ';') {
            buffer << ch;
            this->lexer->instruction = std::make_unique<std::string>(buffer.str());
            auto token_list = this->lexer->lex_instruction();
            if (token_list->back()->type == INVALID) break;

            buffer.str(std::string());

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
