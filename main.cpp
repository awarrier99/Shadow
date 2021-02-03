#include "Interpreter.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error: No source file was provided" << std::endl; // TODO: support REPL
        return 1;
    }

    char* source_filename = argv[1];
    std::ifstream source_file(source_filename);
    if (!source_file.is_open()) {
        std::cerr << "Error: File " << source_filename << " could not be opened" << std::endl;
        return 1;
    }

    auto* interpreter = new Interpreter(&source_file);
    interpreter->pipeline();

    return 0;
}
