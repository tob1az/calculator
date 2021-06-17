#include "RpnCalculator.h"

#include <cmath>
#include <stack>

#include "Expression.h"

namespace calc {
namespace {
bool applyOperator(const tokens::Operator& token, std::stack<double>* numbers) {
    if (token.arity == tokens::Arity::Unary && numbers->size() >= 1) {
        const double x = numbers->top();
        numbers->pop();
        if (token.symbol == '-') {
            numbers->push(-x);
        } else {
            return false;
        }
    } else if (token.arity == tokens::Arity::Binary && numbers->size() >= 2) {
        const double y = numbers->top();
        numbers->pop();
        const double x = numbers->top();
        numbers->pop();

        switch (token.symbol) {
            case '+':
                numbers->push(x + y);
                break;
            case '-':
                numbers->push(x - y);
                break;
            case '*':
                numbers->push(x * y);
                break;
            case '/':
                if (y == 0) {
                    return false;
                }
                numbers->push(x / y);
                break;
            case '^':
                numbers->push(std::pow(x, y));
                break;
            default:
                return false;
        }
    }
    return true;
}

bool applyToken(const Token& token, std::stack<double>* numbers) {
    return std::visit(Overloaded{
                          [numbers](const tokens::Number& number) {
                              numbers->push(number.value);
                              return true;
                          },
                          [numbers](const tokens::Operator& token) {
                              return applyOperator(token, numbers);
                          },
                      },
                      token);
}
}  // namespace

std::optional<double> calculateRpnExpression(PostfixExpression tokens) {
    // pass tokens by copy since we need to change it anyway
    std::stack<double> numbers;

    while (!tokens.empty()) {
        const auto& token = tokens.front();
        bool error = false;
        if (!applyToken(token, &numbers)) {
            return std::nullopt;
        }
        tokens.pop();
    }
    if (numbers.size() == 1) {
        return numbers.top();
    }
    return std::nullopt;
}

}  // namespace calc