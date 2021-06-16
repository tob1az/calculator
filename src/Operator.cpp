#include "Operator.h"

#include <array>
#include <tuple>

namespace calc::tokens {

namespace {
std::array<Operator, 7> kSupportedOperators{
    Operator{'+', 1, Associativity::LeftToRight},
    Operator{'-', 1, Associativity::LeftToRight},
    Operator{'*', 2, Associativity::LeftToRight},
    Operator{'/', 2, Associativity::LeftToRight},
    Operator{'^', 3, Associativity::RightToLeft},
    Operator{'(', 0, Associativity::None},
    Operator{')', 0, Associativity::None},
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