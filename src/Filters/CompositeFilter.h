// CompositeFilter.h
#ifndef COMPOSITE_FILTER_H
#define COMPOSITE_FILTER_H

#include "ILogFilter.h"
#include "CliParser.h"

#include <vector>
#include <memory>
#include <string>

// Фильтры
#include "Filters/CompositeFilter.h"
#include "Filters/RegexMatchFilter.h"
#include "Filters/RegexSearchFilter.h"
#include "Filters/LevelFilter.h"
#include "Filters/ExcludeFilter.h"
#include "Filters/ExcludeRegexFilter.h"


class CompositeFilter : public ILogFilter {
public:
    CompositeFilter() = default;

    // The method checks that the line satisfies all added filters
    bool matches(const std::string &logLine) const override;
    
    //function for initialization the valuable filters with all user conditions
    void buildCompositeFilters(const CliConfig& config);
    
private:
    std::vector<std::unique_ptr<ILogFilter>> filters;

    // Adding a new filtr to the composite filter
    void addFilter(std::unique_ptr<ILogFilter> filter);
};

#endif // COMPOSITE_FILTER_H
