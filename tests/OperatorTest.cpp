#include <gtest/gtest.h>

#include "Operator.h"

namespace calc::tests {

class OperatorTest : public ::testing::TestWithParam<char> {
};

INSTANTIATE_TEST_SUITE_P(AllOperators, OperatorTest,
                         ::testing::Values('+', '-', '*', '/', '^'));


TEST_P(OperatorTest, canPrintOperator) {
    std::stringstream printed{};
    tokens::Operator{GetParam(), {}, {}}.printTo(printed);
    ASSERT_EQ(printed.str(), std::string(1, GetParam()));
}

TEST_P(OperatorTest, canParseOperatorByOperationSymbol) {
    std::stringstream expression{};
    expression << GetParam();
    expression << 'x';
    ASSERT_TRUE(tokens::Operator::parseFrom(expression));
    ASSERT_FALSE(tokens::Operator::parseFrom(expression));
}

TEST_P(OperatorTest, failOperatorParseIfStreamIsBad) {
    std::stringstream expression{};
    ASSERT_FALSE(tokens::Operator::parseFrom(expression));
}

}  // namespace calc::tests
