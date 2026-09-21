#include "interpreter.hpp"

#include <algorithm>
#include <cstdio>
#include <print>

namespace bf {
    void interpret(const std::vector<Instruction>& program) {
        std::vector<std::uint8_t> tape(30000);
        std::size_t ptr = 0;

        for (std::size_t pc = 0; pc < program.size(); pc++) {
            const auto& inst = program[pc];
            switch (inst.op) {
                case Op::Input: {
                    const int c = std::getchar();
                    tape[ptr] = static_cast<std::uint8_t>(std::max(c, 0));
                    break;
                }
                case Op::Output:
                    std::print("{}", static_cast<char>(tape[ptr]));
                    break;
                case Op::Add:
                    tape[ptr] += static_cast<std::uint8_t>(inst.arg);
                    break;
                case Op::Move:
                    ptr += inst.arg;
                    break;
                case Op::LoopOpen:
                    if (tape[ptr] == 0) pc = inst.arg;
                    break;
                case Op::LoopClose:
                    if (tape[ptr] != 0) pc = inst.arg;
                    break;
            }
        }
    }
}
