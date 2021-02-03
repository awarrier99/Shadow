cmake_minimum_required(VERSION 3.15)
project(Fye)

set(CMAKE_CXX_STANDARD 17)

add_executable(Fye main.cpp Lexer.cpp Lexer.h Token.cpp Token.h Parser.cpp Parser.h Interpreter.cpp Interpreter.h)