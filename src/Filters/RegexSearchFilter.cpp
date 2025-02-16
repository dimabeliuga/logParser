// RegexSearchFilter.cpp
#include "RegexSearchFilter.h"

RegexSearchFilter::RegexSearchFilter(const std::string &pattern)
    : regexPattern(pattern)
{
}

bool RegexSearchFilter::matches(const std::string &logLine) const {
    return std::regex_search(logLine, regexPattern);
}
