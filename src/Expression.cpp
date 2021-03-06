#include "Expression.h"

namespace calc {
std::string print(std::optional<PostfixExpression> tokens) {
    if (!tokens) {
        return "";
    }
    std::ostringstream output;
    while (!tokens->empty()) {
        const auto& token = tokens->front();
        std::visit(
            Overloaded{
                [&](const auto& token) { token.printTo(output); },
            },
            token);
        tokens->pop();
        if (!tokens->empty()) {
            output << ' ';
        }
    }
    return output.str();
}
} // namespace calc