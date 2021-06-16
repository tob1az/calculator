#include "Operator.h"

#include <array>
#include <tuple>

namespace calc::tokens {

namespace {
std::array<Operator, 5> kSupportedOperators{
    Operator{'+', 1, Associativity::LeftToRight},
    Operator{'-', 1, Associativity::LeftToRight},
    Operator{'*', 2, Associativity::LeftToRight},
    Operator{'/', 2, Associativity::LeftToRight},
    Operator{'^', 3, Associativity::RightToLeft},
};
}

std::optional<Operator> Operator::parseFrom(std::istream& stream) {
    if (!stream) {
        return std::nullopt;
    }
    char next = stream.peek();
    for (const auto& supported : kSupportedOperators) {
        if (next == supported.symbol) {
            // eat character
            stream >> next;
            return supported;
        }
    }

    return std::nullopt;
}
}  // namespace calc::tokens