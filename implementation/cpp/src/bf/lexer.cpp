#include "lexer.hpp"

#include <optional>

namespace bf {
    namespace {
        std::optional<Instruction> to_instruction(const char c, const std::uint32_t offset) {
            switch (c) {
                case '+': return Instruction{.op = Op::Add, .arg = +1, .offset = offset};
                case '-': return Instruction{.op = Op::Add, .arg = -1, .offset = offset};
                case '>': return Instruction{.op = Op::Move, .arg = +1, .offset = offset};
                case '<': return Instruction{.op = Op::Move, .arg = -1, .offset = offset};
                case '.': return Instruction{.op = Op::Output, .offset = offset};
                case ',': return Instruction{.op = Op::Input, .offset = offset};
                case '[': return Instruction{.op = Op::LoopOpen, .offset = offset};
                case ']': return Instruction{.op = Op::LoopClose, .offset = offset};
                default:  return std::nullopt;
            }
        }
    }
    std::vector<Instruction> lex(const std::string_view source) {
        std::vector<Instruction> instructions;
        instructions.reserve(source.size());

        for (std::uint32_t i = 0; i < source.size(); i++) {
            if (auto inst = to_instruction(source[i], i)) {
                instructions.push_back(*inst);
            }
        }

        return instructions;
    }
}