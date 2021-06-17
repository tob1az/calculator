#include <gtest/gtest.h>

#include "RpnCalculator.h"
#include "ShuntingYard.h"

namespace calc::tests {

struct PrnCalculation {
    std::string input;
    double output;
};
class RpnCalculatorTest : public ::testing::TestWithParam<PrnCalculation> {};

INSTANTIATE_TEST_SUITE_P(
    ValidCalculation, RpnCalculatorTest,
    ::testing::Values(PrnCalculation{"1", 1.}, PrnCalculation{"-1", -1.},
                      PrnCalculation{"(-1)*4", -4.},
                      PrnCalculation{"55342+0.6", 55342.6},
                      PrnCalculation{"11+(34*6-1)/2", 112.5},
                      PrnCalculation{"5*(6^2-2)", 170.},
                      PrnCalculation{"((3+2)^2+3)-9+3^2", 28},
                      PrnCalculation{"(2.1^2+5.2-7.2)*7.1", 17.111},
                      PrnCalculation{"(18/3)^2+((13+7)*5^2)", 536}));

TEST_P(RpnCalculatorTest, canCalculateValidExpression) {
    auto expression = ShuntingYard{GetParam().input}.tokenize();
    ASSERT_TRUE(expression);
    ASSERT_DOUBLE_EQ(*calculateRpnExpression(*expression), GetParam().output);
}

TEST_F(RpnCalculatorTest, cannotCalculateIllFormedExpression) {
    auto expression = ShuntingYard{"-"}.tokenize();
    ASSERT_TRUE(expression);
    ASSERT_FALSE(calculateRpnExpression(*expression));
}

TEST_F(RpnCalculatorTest, cannotCalculateExpressionWithDivisionBy0) {
    auto expression = ShuntingYard{"1/0"}.tokenize();
    ASSERT_TRUE(expression);
    ASSERT_FALSE(calculateRpnExpression(*expression));
}

}  // namespace calc::tests