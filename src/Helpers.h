#pragma once

#include <type_traits>
#include <variant>

namespace calc {
template <class... Types>
struct Overloaded : Types... {
    using Types::operator()...;
};
// explicit deduction guide
template <class... Types>
Overloaded(Types...) -> Overloaded<Types...>;

}  // namespace calc
