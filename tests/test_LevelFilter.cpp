#include <gtest/gtest.h>
#include "Filters/LevelFilter.h"

class LevelFilterTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(LevelFilterTest, MatchesSpecifiedLevels) {
    std::vector<std::string> levels {"ERROR", "WARN", "INFO"};
    LevelFilter filter(levels);
    
    EXPECT_TRUE(filter.matches("[ERROR] System failure"));
    EXPECT_TRUE(filter.matches("[WARN] Disk space low"));
    EXPECT_TRUE(filter.matches("[INFO] Operation completed"));
    EXPECT_FALSE(filter.matches("[DEBUG] Variable value"));
}

TEST_F(LevelFilterTest, CaseSensitiveMatch) {
    std::vector<std::string> levels {"ERROR"};
    LevelFilter filter(levels);
    
    EXPECT_TRUE(filter.matches("[ERROR] message"));
    EXPECT_FALSE(filter.matches("[error] message"));
}