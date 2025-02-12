// CompositeFilter.cpp
#include "CompositeFilter.h"

void CompositeFilter::addFilter(std::unique_ptr<ILogFilter> filter) {
    filters.push_back(std::move(filter));
}

bool CompositeFilter::matches(const std::string &logLine) const {
    // Если фильтров не задано, считаем, что строка удовлетворяет условиям
    if (filters.empty()) {
        return true;
    }
    // Применяем все фильтры: если хотя бы один фильтр возвращает false, строка не проходит проверку
    for (const auto &filter : filters) {
        if (!filter->matches(logLine)) {
            return false;
        }
    }
    return true;
}
