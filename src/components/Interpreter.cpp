#include "Interpreter.h"


Interpreter::Interpreter(std::ifstream* source_file): source_file(source_file) {} // TODO: lexing, parsing, and executing errors/exceptions

void Interpreter::pipeline(bool repl) {
    auto lexer = Lexer(repl ? &std::cin : this->source_file);
    auto parser = Parser(lexer);
    parser.parse();
}
