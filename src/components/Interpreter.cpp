#include "Interpreter.h"


Interpreter::Interpreter() {
    this->executor = std::make_unique<Executor>(Executor());
    this->executor->global = std::make_shared<Scope>(Scope());
}

Interpreter::Interpreter(std::ifstream* source_file): Interpreter() { // TODO: lexing, parsing, and executing errors/exceptions
    this->source_file = source_file;
}

void Interpreter::pipeline(bool repl) {
    auto lexer = Lexer(repl ? &std::cin : this->source_file);
    auto parser = Parser(lexer);
    parser.parse();
}
