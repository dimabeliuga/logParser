// RegexMatchFilter.cpp
#include "RegexMatchFilter.h"

RegexMatchFilter::RegexMatchFilter(const std::string& pattern)
    : regexPattern(pattern) // Инициализация std::regex с переданным паттерном
{
}

bool RegexMatchFilter::matches(const std::string& logLine) const {
    // Используем std::regex_match для проверки, что вся строка соответствует регулярному выражению
    return std::regex_match(logLine, regexPattern);
}
