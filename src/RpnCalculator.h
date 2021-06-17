#pragma once

#include <optional>

#include "Expression.h"

namespace calc {
// Reverse Polish Notation expressions calculator
std::optional<double> calculateRpnExpression(PostfixExpression tokens);

}  // namespace calc