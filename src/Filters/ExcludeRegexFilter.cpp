#include "ExcludeRegexFilter.h"

ExcludeRegexFilter::ExcludeRegexFilter(const std::string& pattern)
    :excludePattern(pattern)
{
}

bool ExcludeRegexFilter::matches(const std::string& logLine) const{
    //check if a log line doesn't match a regular expression
    return !std::regex_search(logLine, excludePattern);
}
