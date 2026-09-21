#pragma once

#include <vector>

#include "ir.hpp"

namespace bf {
    void interpret(const std::vector<Instruction>& program);
}
