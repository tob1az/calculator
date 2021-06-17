#pragma once

#include <optional>
#include <sstream>
#include <stack>
#include <string_view>

#include "Expression.h"

namespace calc {

// Shunting-yard algorithm
class ShuntingYard {
public:
    explicit ShuntingYard(std::string_view expression)
        : _expression{expression.data()} {}

    std::optional<PostfixExpression> tokenize() const;

private:
    bool reorderOperators(const tokens::Operator& currentOperator,
                          std::stack<tokens::Operator>& operators,
                          PostfixExpression* destination) const;

    tokens::Arity detectArity(const std::optional<Token>& previousToken) const;

    const std::istringstream _expression;
};

}  // namespace calc
