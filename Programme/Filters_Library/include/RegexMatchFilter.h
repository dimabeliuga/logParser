#ifndef REGEX_MATCH_FILTER_H
#define REGEX_MATCH_FILTER_H

#include "ILogFilter.h"
#include <regex>
#include <string>

/**
 * @brief Filters log lines by checking if the entire string matches a regular expression.
 *
 * The RegexMatchFilter uses a regular expression to determine whether the whole log line 
 * completely matches the given pattern.
 */
class RegexMatchFilter : public ILogFilter {
public:
    /**
     * @brief Constructs a RegexMatchFilter with the specified pattern.
     *
     * @param pattern The regular expression pattern as a string.
     */
    explicit RegexMatchFilter(const std::string& pattern);

    /**
     * @brief Checks whether the entire log line matches the regular expression.
     *
     * @param logLine The log line to be tested.
     * @return true if the whole log line matches the pattern, false otherwise.
     */
    bool matches(const std::string& logLine) const override;

private:
    std::regex regexPattern; ///< The compiled regular expression pattern.
};

#endif // REGEX_MATCH_FILTER_H
