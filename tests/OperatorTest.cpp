#include <gtest/gtest.h>

#include "Operator.h"

namespace calc::tests {

class OperatorTest : public ::testing::TestWithParam<char> {};

INSTANTIATE_TEST_SUITE_P(AllOperators, OperatorTest,
                         ::testing::Values('+', '-', '*', '/', '^', '(', ')'));

TEST_P(OperatorTest, canPrintOperator) {
    std::stringstream printed{};
    tokens::Operator{GetParam(), {}, {}, tokens::Arity::Binary}.printTo(
        printed);
    ASSERT_EQ(printed.str(), std::string(1, GetParam()));
}

TEST_P(OperatorTest, canParseBinaryOperatorByOperationSymbol) {
    std::stringstream expression{};
    expression << GetParam();
    expression << 'x';
    ASSERT_TRUE(tokens::Operator::parseFrom(expression, tokens::Arity::Binary));
    ASSERT_FALSE(
        tokens::Operator::parseFrom(expression, tokens::Arity::Binary));
}

TEST_P(OperatorTest, failOperatorParseIfStreamIsBad) {
    std::stringstream expression{};
    ASSERT_FALSE(
        tokens::Operator::parseFrom(expression, tokens::Arity::Binary));
}

TEST_F(OperatorTest, canParseUnaryMinus) {
    std::stringstream expression{"-"};
    ASSERT_TRUE(tokens::Operator::parseFrom(expression, tokens::Arity::Unary));
}

TEST_F(OperatorTest, canParseUnaryLeftBracket) {
    std::stringstream expression{"("};
    ASSERT_TRUE(tokens::Operator::parseFrom(expression, tokens::Arity::Unary));
}

TEST_F(OperatorTest, canParseUnaryRightBracket) {
    std::stringstream expression{")"};
    ASSERT_TRUE(tokens::Operator::parseFrom(expression, tokens::Arity::Unary));
}

}  // namespace calc::tests
