#include <gtest/gtest.h>
#include "Filters/RegexSearchFilter.h"

class RegexSearchFilterTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RegexSearchFilterTest, MatchesPatternInMiddle) {
    RegexSearchFilter filter("error");
    EXPECT_TRUE(filter.matches("This is an error message"));
}

TEST_F(RegexSearchFilterTest, NoMatchWhenPatternAbsent) {
    RegexSearchFilter filter("error");
    EXPECT_FALSE(filter.matches("This is a normal message"));
}

TEST_F(RegexSearchFilterTest, MatchesComplexPattern) {
    RegexSearchFilter filter("\\d{4}-\\d{2}-\\d{2}");
    EXPECT_TRUE(filter.matches("Log entry from 2024-02-24: message"));
    EXPECT_FALSE(filter.matches("Log entry from 24-02-2024: message"));
}