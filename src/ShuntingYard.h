#pragma once

#include <optional>
#include <queue>
#include <sstream>
#include <stack>
#include <string_view>

#include "Expression.h"
#include "Helpers.h"

namespace calc {

// Shunting-yard algorithm
class ShuntingYard {
public:
    explicit ShuntingYard(std::string_view expression)
        : _expression{expression.data()} {}

    std::optional<PostfixExpression> tokenize() {
        std::stack<tokens::Operator> operators;
        std::istringstream expression{_expression.str()};

        PostfixExpression output;
        while (expression.good() && expression.peek() != EOF) {
            if (auto number = tokens::Number::parseFrom(expression); number) {
                output.push(*number);
            } else if (auto operatorToken =
                           tokens::Operator::parseFrom(expression);
                       operatorToken) {
                if (!reorderOperators(*operatorToken, operators, &output)) {
                    return std::nullopt;
                }
            } else {
                return std::nullopt;
            }
        }
        while (!operators.empty()) {
            auto top = operators.top();
            if (top.symbol == '(') {
                return std::nullopt;
            }
            output.push(top);
            operators.pop();
        }
        return output;
    }

private:
    bool reorderOperators(const tokens::Operator& currentOperator,
                          std::stack<tokens::Operator>& operators,
                          PostfixExpression* destination) const {
        // handle brackets
        if (currentOperator.symbol == '(') {
            operators.push(currentOperator);
            return true;
        }
        if (currentOperator.symbol == ')') {
            while (!operators.empty()) {
                auto last = operators.top();
                operators.pop();
                if (last.symbol == '(') {
                    return true;
                }
                destination->push(last);
            }
            // no (
            return false;
        }
        // handle other operators
        while (!operators.empty()) {
            const auto& last = operators.top();

            const bool isOfHigherPrecedence =
                (currentOperator.associativity ==
                     tokens::Associativity::LeftToRight &&
                 currentOperator.precedence <= last.precedence) ||
                (currentOperator.associativity ==
                     tokens::Associativity::RightToLeft &&
                 currentOperator.precedence < last.precedence);

            if (isOfHigherPrecedence) {
                destination->push(last);
                operators.pop();
            } else {
                break;
            }
        }
        operators.push(currentOperator);
        return true;
    }

    std::istringstream _expression;
};

}  // namespace calc
