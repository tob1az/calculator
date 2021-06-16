#pragma once
#include "Number.h"
#include "Operator.h"

namespace calc {
// abstract token
using Token = std::variant<tokens::Number, tokens::Operator>;

}  // namespace calc