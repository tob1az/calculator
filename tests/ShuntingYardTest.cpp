#include <gtest/gtest.h>

#include "ShuntingYard.h"

namespace calc::tests {

struct InfixToPrefix {
    std::string input;
    std::string output;
};

class ShuntingYardTest : public ::testing::TestWithParam<InfixToPrefix> {};

INSTANTIATE_TEST_SUITE_P(
    ValidExressions, ShuntingYardTest,
    ::testing::Values(
        InfixToPrefix{"1", "1.0"}, InfixToPrefix{"55342+0.6", "55342.0 0.6 +"},
        InfixToPrefix{"11+(34*6-1)/3.33", "11.0 34.0 6.0 * 1.0 - 3.3 / +"},
        InfixToPrefix{"5*(6^2-2)", "5.0 6.0 2.0 ^ 2.0 - *"},
        InfixToPrefix{"((3+2)^2+3)-9+3^2",
                      "3.0 2.0 + 2.0 ^ 3.0 + 9.0 - 3.0 2.0 ^ +"},
        InfixToPrefix{"(2.1^2+5.2-7.2)*7.1",
                      "2.1 2.0 ^ 5.2 + 7.2 - 7.1 *"},
        InfixToPrefix{"(18/3)^2+((13+7)*5^2)",
                      "18.0 3.0 / 2.0 ^ 13.0 7.0 + 5.0 2.0 ^ * +"}));

TEST_P(ShuntingYardTest, canTokenizeInfixExpression) {
    ShuntingYard tokenizer{GetParam().input};
    ASSERT_EQ(print(tokenizer.tokenize()), GetParam().output);
}

TEST_F(ShuntingYardTest, failsIfNoRightBracket) {
    ShuntingYard tokenizer{"(1+1.4"};
    ASSERT_FALSE(tokenizer.tokenize());
}

TEST_F(ShuntingYardTest, failsIfNoLeftBracket) {
    ShuntingYard tokenizer{"1+1.4)"};
    ASSERT_FALSE(tokenizer.tokenize());
}

TEST_F(ShuntingYardTest, failsIfBracketsOrderIsWrong) {
    ShuntingYard tokenizer{")(1*4"};
    ASSERT_FALSE(tokenizer.tokenize());
}
}  // namespace calc::tests