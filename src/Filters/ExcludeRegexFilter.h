#ifndef EXCLUDE_REGEX_FILTER_H
#define EXCLUDE_REGEX_FILTER_H

#include "ILogFilter.h"
#include <regex>
#include <vector>
#include <string>

class ExcludeRegexFilter : public ILogFilter{
public:
    //The constructor that takes a vector of regular expressions that a log string must not match
    explicit ExcludeRegexFilter(const std::vector<std::string>& patterns);

    //The function checks so that a log string doesn't contain not one of the words listed 
    bool matches(const std::string& logLine) const override;

private:
     std::vector<std::string> excludePatterns;
};
#endif