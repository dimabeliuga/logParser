// RegexMatchFilter.h
#ifndef REGEX_MATCH_FILTER_H
#define REGEX_MATCH_FILTER_H

#include "ILogFilter.h"
#include <regex>
#include <string>

class RegexMatchFilter : public ILogFilter {
public:
    // The constructor takes a regular expression as a string
    explicit RegexMatchFilter(const std::string& pattern);

    // Method checks that the whole string completely matches a regular expression 
    bool matches(const std::string& logLine) const override;

private:
    std::regex regexPattern;
};

#endif // REGEX_MATCH_FILTER_H
