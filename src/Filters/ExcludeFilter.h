#ifndef EXCLUDE_FILTER_H
#define EXCLUDE_FILTER_H

#include "ILogFilter.h"
#include <algorithm>
#include <vector>
#include <string>

class ExcludeFilter : public ILogFilter{
public:
    //The constructor that takes a vector of words that can't appear in logs
    explicit ExcludeFilter(const std::vector<std::string>& text);

    //The function checks so that a log string doesn't contain not one of the words listed 
    bool matches(const std::string& logLine) const override;

private:
     std::vector<std::string> excludeWords;
};
#endif