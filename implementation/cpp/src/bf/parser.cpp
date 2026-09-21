#include "parser.hpp"

#include <format>
#include <stdexcept>

namespace bf {
    std::vector<Instruction> parse(const std::vector<Instruction>& tokens) {
        std::vector<Instruction> program;

        std::vector<std::size_t> open_loops;

        for (const auto& token : tokens) {
            switch (token.op) {
                case Op::Add:
                case Op::Move:
                    if (program.empty() == false && program.back().op == token.op) {
                        program.back().arg += token.arg;
                    } else {
                        program.push_back(token);
                    }
                    break;
                case Op::LoopOpen:
                    open_loops.push_back(program.size());
                    program.push_back(token);
                    break;
                case Op::LoopClose: {
                    if (open_loops.empty())
                        throw std::runtime_error(std::format("unmatched ']' at offset {}", token.offset));

                    const size_t openLoop = open_loops.back();
                    open_loops.pop_back();
                    program[openLoop].arg = static_cast<int32_t>(program.size());
                    program.push_back(token);
                    program.back().arg = static_cast<int32_t>(openLoop);
                    break;
                }

                default:
                    program.push_back(token);
            }
        }

        if (!open_loops.empty())
            throw std::runtime_error(std::format("unmatched '[' at offset {}", program[open_loops.back()].offset));

        return program;
    }
}
