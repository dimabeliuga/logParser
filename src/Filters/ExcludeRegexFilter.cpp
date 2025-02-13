#include "ExcludeRegexFilter.h"

ExcludeRegexFilter::ExcludeRegexFilter(const std::vector<std::string>& patterns)
    :excludePatterns(patterns)
{
}

bool ExcludeRegexFilter::matches(const std::string& logLine) const{
    //check if a log line doesn't match any regular expression
    for(const auto& pattern : excludePatterns){
        if(std::regex_search(logLine, std::regex(pattern))){
            return false;
        }
    }
    return true;
}
