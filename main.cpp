#include "Interpreter.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error: No source file was provided" << std::endl; // TODO: support REPL
        return 1;
    }

    char* source_filename = argv[1];
    auto source_file = std::make_unique<std::ifstream>(std::ifstream(source_filename));
    if (!source_file->is_open()) {
        std::cerr << "Error: File " << source_filename << " could not be opened" << std::endl;
        return 1;
    }

    auto interpreter = Interpreter(source_file);
    interpreter.pipeline();

    return 0;
}
