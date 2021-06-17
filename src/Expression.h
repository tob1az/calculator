#pragma once

#include <optional>
#include <queue>
#include <sstream>

#include "Helpers.h"
#include "Tokens.h"

namespace calc {
using PostfixExpression = std::queue<Token>;
// returns "" in unable to print it
std::string print(std::optional<PostfixExpression> tokens);
}  // namespace calc