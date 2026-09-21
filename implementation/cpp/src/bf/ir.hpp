#pragma once
#include <cstdint>

namespace bf {
    enum class Op : std::uint8_t {
        Add, Move, Output, Input, LoopOpen, LoopClose,
    };

    struct Instruction {
        Op op{}; // initializes 0, i don't like how this looks though...
        std::int32_t arg = 0;
        std::uint32_t offset = 0;
    };
}
