// ILogFilter.h
#ifndef ILOGFILTER_H
#define ILOGFILTER_H

#include <string>

class ILogFilter {
public:
    virtual ~ILogFilter() = default;
    
    //A method for checking each string of a log file. It returns true, if a log string satisfies the filter condition
    virtual bool matches(const std::string& logLine) const = 0;
};

#endif // ILOGFILTER_H
