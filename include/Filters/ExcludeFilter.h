#ifndef EXCLUDE_FILTER_H
#define EXCLUDE_FILTER_H

#include "ILogFilter.h"
#include <algorithm>
#include <vector>
#include <string>

/**
 * @brief ExcludeFilter filters out log lines containing any of the specified words.
 *
 * This filter returns true if the log line does NOT contain any of the excluded words.
 */
class ExcludeFilter : public ILogFilter {
public:
    /**
     * @brief Constructs an ExcludeFilter with a list of words to exclude.
     * 
     * @param text A vector of words that must not appear in the log line.
     */
    explicit ExcludeFilter(const std::vector<std::string>& text);

    /**
     * @brief Checks that the log line does not contain any excluded word.
     * 
     * @param logLine The log line to check.
     * @return true if none of the excluded words are found, false otherwise.
     */
    bool matches(const std::string& logLine) const override;

private:
    std::vector<std::string> excludeWords;  ///< List of words that must not be present in the log line.
};

#endif // EXCLUDE_FILTER_H
