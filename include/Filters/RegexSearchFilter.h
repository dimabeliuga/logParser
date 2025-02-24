#ifndef REGEX_SEARCH_FILTER_H
#define REGEX_SEARCH_FILTER_H

#include "ILogFilter.h"
#include <regex>
#include <string>

/**
 * @brief A class that filters log entries using regular expressions.
 */
class RegexSearchFilter : public ILogFilter {
public:
    /**
     * @brief Constructor that takes a regular expression as a string.
     * @param pattern The string containing the regular expression.
     */
    explicit RegexSearchFilter(const std::string &pattern);

    /**
     * @brief Checks that at least one match with the regular expression is found in the log line.
     * @param logLine The log string to check.
     * @return true if a match with the regular expression is found, false otherwise.
     */
    bool matches(const std::string &logLine) const override;

private:
    std::regex regexPattern; /**< The regular expression pattern used for filtering. */
};

#endif // REGEX_SEARCH_FILTER_H
