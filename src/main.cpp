#include <iostream>

#include "Helpers.h"
#include "ShuntingYard.h"

namespace calc {
std::string print(std::optional<calc::PostfixTokens> tokens) {
    if (!tokens) {
        return "parsing error";
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
        output << ' ';
    }
    return output.str();
}
}  // namespace calc

int main(int argc, char** argv) {
    if (argc > 1) {
        std::cout << calc::print(
                         calc::ShuntingYard{std::string{argv[1]}}.tokenize())
                  << '\n';
    }
    return 0;
}
