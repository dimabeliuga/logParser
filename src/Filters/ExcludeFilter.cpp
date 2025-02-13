#include "ExcludeFilter.h"

ExcludeFilter::ExcludeFilter(const std::vector<std::string>& bannedWords)
    : excludeWords(bannedWords)
{
}

bool ExcludeFilter::matches(const std::string& logLine) const{
    for(const auto &excludeWord : excludeWords){
        if(logLine.find(excludeWord) != std::string::npos){
            return false;
        }
    }
    return true;
}

