#include "ShuntingYard.h"

#include <queue>

namespace calc {

std::optional<PostfixExpression> ShuntingYard::tokenize() const {
    std::stack<tokens::Operator> operators;
    std::istringstream expression{_expression.str()};
    std::optional<Token> previousToken;

    PostfixExpression output;
    while (expression.good() && expression.peek() != EOF) {
        if (auto number = tokens::Number::parseFrom(expression); number) {
            output.push(*number);
            previousToken.emplace(*number);
        } else if (auto operatorToken = tokens::Operator::parseFrom(
                       expression, detectArity(previousToken));
                   operatorToken) {
            if (!reorderOperators(*operatorToken, operators, &output)) {
                return std::nullopt;
            }
            previousToken.emplace(*operatorToken);
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

bool ShuntingYard::reorderOperators(const tokens::Operator& currentOperator,
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

tokens::Arity ShuntingYard::detectArity(
    const std::optional<Token>& previousToken) const {
    // at the start of expression
    if (!previousToken) {
        return tokens::Arity::Unary;
    }
    if (std::holds_alternative<tokens::Operator>(*previousToken) &&
        std::get<tokens::Operator>(*previousToken).symbol != ')') {
        return tokens::Arity::Unary;
    }
    return tokens::Arity::Binary;
}

}  // namespace calc
