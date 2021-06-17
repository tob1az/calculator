#pragma once

#include <iomanip>
#include <istream>
#include <optional>
#include <ostream>

namespace calc::tokens {
using Precedence = int;

enum class Associativity { LeftToRight, RightToLeft, None };

enum class Arity { Binary, Unary };

struct Operator {
    Operator(char symbol, Precedence precedence, Associativity associativity,
             Arity arity)
        : symbol{symbol},
          precedence{precedence},
          associativity{associativity},
          arity{arity} {}

    void printTo(std::ostream& stream) const { stream << symbol; }

    static std::optional<Operator> parseFrom(std::istream& stream, Arity arity);

    const char symbol;
    const Precedence precedence;
    const Associativity associativity;
    const Arity arity;
};

}  // namespace calc::tokens
