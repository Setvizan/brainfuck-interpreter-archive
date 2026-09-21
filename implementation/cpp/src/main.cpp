#include <format>
#include <fstream>
#include <iterator>
#include <print>
#include <stdexcept>
#include <string>

#include "bf/interpreter.hpp"
#include "bf/lexer.hpp"
#include "bf/parser.hpp"

namespace {
    std::string read_file(const std::string& path) {
        std::ifstream file(path, std::ios::binary);
        if (!file)
            throw std::runtime_error(std::format("could not open '{}'", path));
        return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    }
}

int main(const int argc, char* argv[]) {
    if (argc != 2) {
        std::println(stderr, "usage: {} <file.bf>", argv[0]);
        return 1;
    }

    try {
        const std::string source = read_file(argv[1]);

        const auto tokens = bf::lex(source);
        const auto program = bf::parse(tokens);
        bf::interpret(program);
    } catch (const std::exception& e) {
        std::println(stderr, "error: {}", e.what());
        return 1;
    }

    return 0;
}
