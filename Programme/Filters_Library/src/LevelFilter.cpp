// LevelFilter.cpp
#include "LevelFilter.h"

LevelFilter::LevelFilter(const std::vector<std::string>& levels)
    : levels(levels)
{
}

bool LevelFilter::matches(const std::string &logLine) const {
    // We go through all the specified levels and look for their presence in the line
    for (const auto &level : levels) {
        if (logLine.find(level) != std::string::npos) {
            return true;
        }
    }
    return false;
}
