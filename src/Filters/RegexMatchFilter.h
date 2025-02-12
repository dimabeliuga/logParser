// RegexMatchFilter.h
#ifndef REGEX_MATCH_FILTER_H
#define REGEX_MATCH_FILTER_H

#include "ILogFilter.h"
#include <regex>
#include <string>

class RegexMatchFilter : public ILogFilter {
public:
    // Конструктор принимает регулярное выражение в виде строки
    explicit RegexMatchFilter(const std::string& pattern);

    // Метод, проверяющий, что вся строка полностью соответствует регулярному выражению
    bool matches(const std::string& logLine) const override;

private:
    std::regex regexPattern;
};

#endif // REGEX_MATCH_FILTER_H
