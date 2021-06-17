#include <gtest/gtest.h>

#include "Number.h"

namespace calc::tests {

class NumberTest
    : public ::testing::TestWithParam<std::pair<std::string, double>> {};

TEST_P(NumberTest, canParseNumbers) {
    std::stringstream number{GetParam().first};
    const auto parsed = tokens::Number::parseFrom(number);
    ASSERT_TRUE(parsed);
    ASSERT_TRUE(parsed->value == GetParam().second);
}

INSTANTIATE_TEST_SUITE_P(ValidNumbers, NumberTest,
                         ::testing::Values(std::pair{"100", 100.},
                                           std::pair{"0", 0.},
                                           std::pair{"0.55", 0.55}));

TEST_F(NumberTest, cannotParseNonNumbers) {
    std::stringstream number{"sf1"};
    ASSERT_FALSE(tokens::Number::parseFrom(number));    
}

TEST_F(NumberTest, cannotParseIfStreamIsInvalid) {
    std::stringstream number{"12456"};
    // parse the number and exhaust the stream
    tokens::Number::parseFrom(number);
    ASSERT_FALSE(tokens::Number::parseFrom(number));    
}

TEST_F(NumberTest, canBePrinted) {
    std::stringstream printed;
    tokens::Number{5554.0}.printTo(printed);
    ASSERT_EQ(printed.str(), "5554.0");    
}

}  // namespace calc::tests
