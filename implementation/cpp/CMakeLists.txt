cmake_minimum_required(VERSION 4.3)
project(brainfuck-interpreter)

set(CMAKE_CXX_STANDARD 23)

# Default Install to ~/.local so it lands on PATH without sudo.
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "Install prefix" FORCE)
endif()

add_executable(bf src/main.cpp
        src/bf/interpreter.cpp
        src/bf/interpreter.hpp
        src/bf/lexer.cpp
        src/bf/lexer.hpp
        src/bf/parser.cpp
        src/bf/parser.hpp
        src/bf/ir.hpp)

install(TARGETS bf)
