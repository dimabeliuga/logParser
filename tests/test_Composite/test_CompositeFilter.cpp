#include <gtest/gtest.h>
#include "CompositeFilter.h"

class CompositeFilterTest : public ::testing::Test {
protected:
    CompositeFilter filter;
    CliConfig config;
};

TEST_F(CompositeFilterTest, EmptyFilterReturnsTrue) {
    EXPECT_TRUE(filter.matches("any message"));
}

TEST_F(CompositeFilterTest, CombinedFiltersWork) {
    config.regexMatch = "^\\[ERROR\\].*$";
    config.levels = {"ERROR"};
    
    filter.buildCompositeFilters(config);
    
    EXPECT_TRUE(filter.matches("[ERROR] System failure"));
    EXPECT_FALSE(filter.matches("[WARN] System failure"));
    EXPECT_FALSE(filter.matches("ERROR: System failure"));
}

TEST_F(CompositeFilterTest, AllFiltersApplied) {
    config.regexMatch = "^\\[ERROR\\].*$";
    config.exclude = {"test"};
    config.levels = {"ERROR"};
    
    filter.buildCompositeFilters(config);
    
    EXPECT_TRUE(filter.matches("[ERROR] System failure"));
    EXPECT_FALSE(filter.matches("[ERROR] test message"));
    EXPECT_FALSE(filter.matches("[INFO] System failure"));
}