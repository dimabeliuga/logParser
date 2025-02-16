// RegexMatchFilter.cpp
#include "RegexMatchFilter.h"

RegexMatchFilter::RegexMatchFilter(const std::string& pattern)
    : regexPattern(pattern)
{
}

bool RegexMatchFilter::matches(const std::string& logLine) const {
    return std::regex_match(logLine, regexPattern);
}
