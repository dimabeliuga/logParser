#ifndef COMPOSITE_FILTER_H
#define COMPOSITE_FILTER_H

#include "ILogFilter.h"
#include "CliParser.h"

#include <vector>
#include <memory>
#include <string>

// Filters
#include "Filters.h"

/**
 * @brief CompositeFilter aggregates multiple log filters.
 *
 * This class implements the ILogFilter interface by combining several filters.
 * A log line passes the composite filter if and only if it satisfies all added filters.
 */
class CompositeFilter : public ILogFilter {
public:
    /**
     * @brief Default constructor.
     */
    CompositeFilter() = default;

    /**
     * @brief Checks if the log line satisfies all added filters.
     * 
     * @param logLine The log line to test.
     * @return true if the log line passes all filters, false otherwise.
     */
    bool matches(const std::string &logLine) const override;
    
    /**
     * @brief Initializes the composite filter with all user-specified conditions.
     * 
     * This function builds the internal collection of filters based on the configuration.
     * 
     * @param config The configuration containing user conditions.
     */
    void buildCompositeFilters(const CliConfig& config);
    
private:
    std::vector<std::unique_ptr<ILogFilter>> filters;  ///< Container of added filters.

    /**
     * @brief Adds a new filter to the composite filter.
     * 
     * @param filter The filter to add.
     */
    void addFilter(std::unique_ptr<ILogFilter> filter);
};

#endif // COMPOSITE_FILTER_H
