#pragma once

#include <iomanip>
#include <istream>
#include <optional>
#include <ostream>
#include <variant>
#include <vector>

namespace calc {
namespace tokens {
struct Number final {
    using Type = double;
    const Type value;

    void printTo(std::ostream& stream) const {
        stream << std::fixed << std::setprecision(1) << value;
    }
    static std::optional<Number> parseFrom(std::istream& stream) {
        Type value{};
        if (!(stream >> value)) {
            return std::nullopt;
        }
        return Number{value};
    }
};

}  // namespace tokens

}  // namespace calc
