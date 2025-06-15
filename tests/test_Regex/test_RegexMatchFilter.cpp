#include <gtest/gtest.h>
#include "RegexMatchFilter.h"

class RegexMatchFilterTest : public ::testing::Test{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RegexMatchFilterTest, ExactMatch) {
    // This test checks that the filter returns true for an exact match.
    RegexMatchFilter filter("^Hello World$");
    EXPECT_TRUE(filter.matches("Hello World"));
    EXPECT_FALSE(filter.matches("Hello World!"));
}

TEST_F(RegexMatchFilterTest, NumericPattern) {
    // This test verifies matching a numeric pattern in the format "123-45-6789".
    RegexMatchFilter filter("^\\d{3}-\\d{2}-\\d{4}$");
    EXPECT_TRUE(filter.matches("123-45-6789"));
    EXPECT_FALSE(filter.matches("123-456-789"));
    EXPECT_FALSE(filter.matches("abc-de-ghij"));
}

TEST_F(RegexMatchFilterTest, EmptyStringPattern) {
    // This test checks the behavior when matching an empty string.
    RegexMatchFilter filter("^$");  // Pattern that matches only an empty string.
    EXPECT_TRUE(filter.matches(""));
    EXPECT_FALSE(filter.matches(" "));
}

TEST_F(RegexMatchFilterTest, SpecialCharacters) {
    // This test verifies that special characters are matched exactly.
    RegexMatchFilter filter("^\\[INFO\\]: .*");
    EXPECT_TRUE(filter.matches("[INFO]: System started successfully"));
    EXPECT_FALSE(filter.matches("INFO: System started successfully"));
}
