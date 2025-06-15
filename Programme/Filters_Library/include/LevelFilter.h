#ifndef LEVEL_FILTER_H
#define LEVEL_FILTER_H

#include "ILogFilter.h"
#include <vector>
#include <string>

/**
 * @brief Filters log lines based on specified log levels.
 *
 * The LevelFilter checks if a log line contains at least one of the specified log levels.
 */
class LevelFilter : public ILogFilter {
public:
    /**
     * @brief Constructs a LevelFilter with the given log levels.
     *
     * @param levels A vector of log levels to check for in the log line.
     */
    explicit LevelFilter(const std::vector<std::string>& levels);

    /**
     * @brief Checks if the log line contains at least one of the specified levels.
     *
     * @param logLine The log line to be evaluated.
     * @return true if the log line contains any of the specified levels, false otherwise.
     */
    bool matches(const std::string &logLine) const override;

private:
    std::vector<std::string> levels; ///< Vector of log levels.
};

#endif // LEVEL_FILTER_H
