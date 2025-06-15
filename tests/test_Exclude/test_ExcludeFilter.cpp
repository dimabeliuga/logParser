#include <gtest/gtest.h>
#include "ExcludeFilter.h"

class ExcludeFilterTest : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(ExcludeFilterTest, ExcludesSingleWord) {
    std::vector<std::string> banned = {"DEBUG"};
    ExcludeFilter filter(banned);
    
    EXPECT_FALSE(filter.matches("[DEBUG] Test message"));
    EXPECT_TRUE(filter.matches("[INFO] Test message"));
}

TEST_F(ExcludeFilterTest, ExcludesMultipleWords) {
    std::vector<std::string> banned = {"DEBUG", "TRACE"};
    ExcludeFilter filter(banned);
    
    EXPECT_FALSE(filter.matches("[DEBUG] Test message"));
    EXPECT_FALSE(filter.matches("[TRACE] Another message"));
    EXPECT_TRUE(filter.matches("[INFO] Normal message"));
}

TEST_F(ExcludeFilterTest, CaseSensitive) {
    std::vector<std::string> banned = {"debug"};
    ExcludeFilter filter(banned);
    
    EXPECT_FALSE(filter.matches("debug message"));
    EXPECT_TRUE(filter.matches("DEBUG message"));
}

TEST_F(ExcludeFilterTest, PartialWordMatch) {
    std::vector<std::string> banned = {"error"};
    ExcludeFilter filter(banned);
    
    EXPECT_FALSE(filter.matches("This is an error in the system"));
    EXPECT_FALSE(filter.matches("error: system failure"));
    EXPECT_TRUE(filter.matches("This is an ERROR in the system"));
}