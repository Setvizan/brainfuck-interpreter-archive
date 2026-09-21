#pragma once

#include <string_view>
#include <vector>

#include "ir.hpp"

namespace bf {
    std::vector<Instruction> lex(std::string_view source);
}
