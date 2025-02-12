// LevelFilter.cpp
#include "LevelFilter.h"

LevelFilter::LevelFilter(const std::vector<std::string>& levels)
    : levels(levels)
{
}

bool LevelFilter::matches(const std::string &logLine) const {
    // Проходим по всем указанным уровням и ищем их наличие в строке
    for (const auto &level : levels) {
        if (logLine.find(level) != std::string::npos) {
            return true;
        }
    }
    return false;
}
