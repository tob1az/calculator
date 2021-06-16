#pragma once

#include <iomanip>
#include <istream>
#include <optional>
#include <ostream>

namespace calc::tokens {
using Precedence = int;

enum class Associativity { LeftToRight, RightToLeft };

struct Operator {
    Operator(char symbol, Precedence precedence, Associativity associativity)
        : symbol{symbol},
          precedence{precedence},
          associativity{associativity} {}

    void printTo(std::ostream& stream) const { stream << symbol; }

    static std::optional<Operator> parseFrom(std::istream& stream);

    const char symbol;
    const Precedence precedence;
    const Associativity associativity;
};

}  // namespace calc::tokens
