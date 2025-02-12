// RegexSearchFilter.h
#ifndef REGEX_SEARCH_FILTER_H
#define REGEX_SEARCH_FILTER_H

#include "ILogFilter.h"
#include <regex>
#include <string>

class RegexSearchFilter : public ILogFilter {
public:
    // Конструктор принимает регулярное выражение в виде строки
    explicit RegexSearchFilter(const std::string &pattern);

    // Метод проверяет, что в строке лога найдено хотя бы одно совпадение с регулярным выражением
    bool matches(const std::string &logLine) const override;

private:
    std::regex regexPattern;
};

#endif // REGEX_SEARCH_FILTER_H
