// ILogFilter.h
#ifndef ILOGFILTER_H
#define ILOGFILTER_H

#include <string>

/**
 * @class ILogFilter
 * @brief Interface for log filtering functionality
 */
class ILogFilter {
public:
    /**
     * @brief Virtual destructor for interface class
     */
    virtual ~ILogFilter() = default;
    
    /**
     * @brief Check if a log string satisfies the filter condition
     * @param logLine String to be checked against the filter
     * @return true if the log string matches the filter criteria, false otherwise
     */
    virtual bool matches(const std::string& logLine) const = 0;
};

#endif // ILOGFILTER_H
