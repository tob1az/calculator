#pragma once

#include <iomanip>
#include <istream>
#include <optional>
#include <ostream>
#include <cctype>

namespace calc::tokens {

struct Number final {
    using Type = double;
    const Type value;

    void printTo(std::ostream& stream) const {
        stream << std::fixed << std::setprecision(1) << value;
    }
    static std::optional<Number> parseFrom(std::istream& stream) {
        Type value{};
        if (!isdigit(stream.peek())) {
            return std::nullopt;
        }
        if (!(stream >> value)) {
            return std::nullopt;
        }
        return Number{value};
    }
};
}  // namespace calc::tokens
