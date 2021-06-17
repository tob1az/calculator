#include <iostream>

#include "RpnCalculator.h"
#include "ShuntingYard.h"

int main(int argc, char** argv) {
    if (argc > 1) {
        auto tokens = calc::ShuntingYard{std::string{argv[1]}}.tokenize();
        if (!tokens) {
            std::cout << "parsing error\n";
            return 1;
        }
        std::cout << calc::print(tokens) << '\n';

        auto result = calc::calculateRpnExpression(*tokens);
        if (result) {
            std::cout << "result: " << std::fixed << *result << '\n';
        } else {
            std::cout << "calculation error:\n";
        }
    }
    return 0;
}
