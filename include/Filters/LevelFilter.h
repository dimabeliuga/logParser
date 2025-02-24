// LevelFilter.h
#ifndef LEVEL_FILTER_H
#define LEVEL_FILTER_H

#include "ILogFilter.h"
#include <vector>
#include <string>

class LevelFilter : public ILogFilter {
public:
    // The constructor takes a vector with log levels
    explicit LevelFilter(const std::vector<std::string>& levels);

    // The method checks that at least the log line contains one of the specified levels
    bool matches(const std::string &logLine) const override;

private:
    std::vector<std::string> levels;
};

#endif // LEVEL_FILTER_H
