#pragma once

#include <optional>
#include <queue>
#include <sstream>
#include <stack>
#include <string_view>

#include "Helpers.h"
#include "Tokens.h"

namespace calc {
using PostfixTokens = std::queue<Token>;

// Shunting-yard algorithm
class ShuntingYard {
public:
    explicit ShuntingYard(std::string_view expression)
        : _expression{expression.data()} {}

    std::optional<PostfixTokens> tokenize() {
        std::stack<tokens::Operator> operators;
        std::istringstream expression{_expression.str()};

        PostfixTokens output;
        while (!expression.eof()) {
            if (auto number = tokens::Number::parseFrom(expression); number) {
                output.push(*number);
            } else if (auto operatorToken =
                           tokens::Operator::parseFrom(expression);
                       operatorToken) {
                reorderOperators(*operatorToken, operators, &output);
                operators.push(*operatorToken);
            } else {
                return std::nullopt;
            }
        }
        while (!operators.empty()) {
            output.push(operators.top());
            operators.pop();
        }
        return output;
    }

private:
    void reorderOperators(const tokens::Operator& currentOperator,
                          std::stack<tokens::Operator>& operators,
                          PostfixTokens* destination) const {
        while (!operators.empty()) {
            const auto& last = operators.top();

            const bool isOfHigherPrecedence =
                (currentOperator.associativity ==
                     tokens::Associativity::RightToLeft &&
                 currentOperator.precedence <= last.precedence) ||
                (currentOperator.associativity ==
                     tokens::Associativity::LeftToRight &&
                 currentOperator.precedence < last.precedence);

            if (isOfHigherPrecedence) {
                destination->push(last);
                operators.pop();
            } else {
                break;
            }
        }
    }

    std::istringstream _expression;
};

}  // namespace calc
