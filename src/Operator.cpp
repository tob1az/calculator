#include "Operator.h"

#include <array>
#include <tuple>

namespace calc::tokens {

namespace {
std::array<Operator, 10> kSupportedOperators{
    Operator{'+', 1, Associativity::LeftToRight, Arity::Binary},
    Operator{'-', 3, Associativity::LeftToRight, Arity::Unary},
    Operator{'-', 1, Associativity::LeftToRight, Arity::Binary},
    Operator{'*', 2, Associativity::LeftToRight, Arity::Binary},
    Operator{'/', 2, Associativity::LeftToRight, Arity::Binary},
    Operator{'^', 4, Associativity::RightToLeft, Arity::Binary},
    Operator{'(', 0, Associativity::None, Arity::Binary},
    Operator{')', 0, Associativity::None, Arity::Binary},
    Operator{'(', 0, Associativity::None, Arity::Unary},
    Operator{')', 0, Associativity::None, Arity::Unary},
};
}

std::optional<Operator> Operator::parseFrom(std::istream& stream, Arity arity) {
    if (!stream) {
        return std::nullopt;
    }
    char next = stream.peek();
    for (const auto& supported : kSupportedOperators) {
        if (next == supported.symbol && supported.arity == arity) {
            // eat character
            stream.get();
            return supported;
        }
    }

    return std::nullopt;
}
}  // namespace calc::tokens