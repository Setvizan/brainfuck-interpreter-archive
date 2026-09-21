#pragma once

#include <vector>

#include "ir.hpp"

namespace bf {
    std::vector<Instruction> parse(const std::vector<Instruction>& tokens);
}
