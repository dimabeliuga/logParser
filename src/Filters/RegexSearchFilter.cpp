// RegexSearchFilter.cpp
#include "RegexSearchFilter.h"

//the constructor takes a vector of regular expressions
RegexSearchFilter::RegexSearchFilter(const std::string &pattern)
    : regexPattern(pattern)
{
}

bool RegexSearchFilter::matches(const std::string &logLine) const {
    // Используем std::regex_search для поиска совпадения в строке
    return std::regex_search(logLine, regexPattern);
}
