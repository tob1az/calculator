#include <iostream>

#include "Helpers.h"
#include "ShuntingYard.h"

int main(int argc, char** argv) {
    if (argc > 1) {
        std::cout << calc::print(
                         calc::ShuntingYard{std::string{argv[1]}}.tokenize())
                  << '\n';
    }
    return 0;
}

