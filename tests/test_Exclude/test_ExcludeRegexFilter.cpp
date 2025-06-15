#include <gtest/gtest.h>
#include "ExcludeRegexFilter.h"

class ExcludeRegexFilterTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(ExcludeRegexFilterTest, ExcludesMatchingLines) {
    ExcludeRegexFilter filter("DEBUG|TRACE");
    
    EXPECT_FALSE(filter.matches("[DEBUG] Test message"));
    EXPECT_FALSE(filter.matches("[TRACE] Another message"));
    EXPECT_TRUE(filter.matches("[INFO] Normal message"));
}

TEST_F(ExcludeRegexFilterTest, ComplexPatternWorks) {
    ExcludeRegexFilter filter("\\[TEST-\\d+\\]");
    
    EXPECT_FALSE(filter.matches("[TEST-123] Message"));
    EXPECT_FALSE(filter.matches("Prefix [TEST-456] Suffix"));
    EXPECT_TRUE(filter.matches("[TEST] Without number"));
}

TEST_F(ExcludeRegexFilterTest, CaseSensitiveByDefault) {
    ExcludeRegexFilter filter("error");
    
    EXPECT_FALSE(filter.matches("This is an error message"));
    EXPECT_TRUE(filter.matches("This is an ERROR message"));
}