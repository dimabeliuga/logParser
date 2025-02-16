// RegexSearchFilter.h
#ifndef REGEX_SEARCH_FILTER_H
#define REGEX_SEARCH_FILTER_H

#include "ILogFilter.h"
#include <regex>
#include <string>

class RegexSearchFilter : public ILogFilter {
public:

    // The constructor takes a regular expression as a string
    explicit RegexSearchFilter(const std::string &pattern);

    // The method checks that at least one match with the regular expression was found in the log line
    bool matches(const std::string &logLine) const override;

private:
    std::regex regexPattern;
};

#endif // REGEX_SEARCH_FILTER_H
