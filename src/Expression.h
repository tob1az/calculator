#pragma once

#include <queue>

#include "Tokens.h"

namespace calc {
using PostfixExpression = std::queue<Token>;
}  // namespace calc