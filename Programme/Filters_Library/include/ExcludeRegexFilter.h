#ifndef EXCLUDE_REGEX_FILTER_H
#define EXCLUDE_REGEX_FILTER_H

#include "ILogFilter.h"
#include <regex>
#include <vector>
#include <string>

/**
 * @brief A class that filters log entries using regular expressions.
 */
class ExcludeRegexFilter : public ILogFilter {
public:
    /**
     * @brief Constructor that takes a string of user-defined regular expressions that a log string must not match.
     * @param patterns The string containing regular expressions.
     */
    explicit ExcludeRegexFilter(const std::string& patterns);

    /**
     * @brief Checks whether a log string does not match the regular expression.
     * @param logLine The log string to check.
     * @return true if the log string does not match the regular expression, false otherwise.
     */
    bool matches(const std::string& logLine) const override;

private:
    std::regex excludePattern; /**< The regular expression pattern used for filtering. */
};

#endif // EXCLUDE_REGEX_FILTER_H
