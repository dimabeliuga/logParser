#ifndef EXCLUDE_REGEX_FILTER_H
#define EXCLUDE_REGEX_FILTER_H

#include "ILogFilter.h"
#include <regex>
#include <vector>
#include <string>

class ExcludeRegexFilter : public ILogFilter{
public:
    //The constructor takes a string(user regular expressions) that a log string must not match
    explicit ExcludeRegexFilter(const std::string& patterns);

    //The function checks so that a log string doesn't match a regular expression 
    bool matches(const std::string& logLine) const override;

private:
     std::regex excludePattern;
};
#endif