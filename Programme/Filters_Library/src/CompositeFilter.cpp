// CompositeFilter.cpp
#include "CompositeFilter.h"

void CompositeFilter::addFilter(std::unique_ptr<ILogFilter> filter) {
    filters.push_back(std::move(filter));
}

bool CompositeFilter::matches(const std::string &logLine) const {
    // If no filters are, we assume that the srting satisfies the conditions
    if (filters.empty()) {
        return true;
    }

    // Apply all filters: if at least one filter returns false, the row will not be written to the output file
    for (const auto &filter : filters) {
        if (!filter->matches(logLine)) {
            return false;
        }
    }
    return true;
}

void CompositeFilter::buildCompositeFilters(const CliConfig& config){
    // If the --regex_match flag specified, add an exact match filter
    if (!config.regexMatch.empty()) {
        addFilter(std::make_unique<RegexMatchFilter>(config.regexMatch));
    }
    
    // --regex_search
    if (!config.regexSearch.empty()) {
        addFilter(std::make_unique<RegexSearchFilter>(config.regexSearch));
    }
    
    // --exclude_regex
    if(!config.excludeRegex.empty()){
        addFilter(std::make_unique<ExcludeRegexFilter>(config.excludeRegex));
    }
    
    // --exclude
    if(!config.exclude.empty()){
        addFilter(std::make_unique<ExcludeFilter>(config.exclude));
    }
    
    // --level
    if (!config.levels.empty()) {
        addFilter(std::make_unique<LevelFilter>(config.levels));
    }    
}
