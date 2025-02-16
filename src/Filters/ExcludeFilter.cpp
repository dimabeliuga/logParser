#include "ExcludeFilter.h"

ExcludeFilter::ExcludeFilter(const std::vector<std::string>& bannedWords)
    : excludeWords(bannedWords)
{
}

bool ExcludeFilter::matches(const std::string& logLine) const{
    // check if the line contains banned words
    for(const auto &excludeWord : excludeWords){
        if(logLine.find(excludeWord) != std::string::npos){
            return false;
        }
    }
    return true;
}

