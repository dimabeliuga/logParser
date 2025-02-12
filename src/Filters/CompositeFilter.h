// CompositeFilter.h
#ifndef COMPOSITE_FILTER_H
#define COMPOSITE_FILTER_H

#include "ILogFilter.h"
#include <vector>
#include <memory>
#include <string>

class CompositeFilter : public ILogFilter {
public:
    CompositeFilter() = default;

    // Добавление нового фильтра в составной фильтр
    void addFilter(std::unique_ptr<ILogFilter> filter);

    // Метод проверяет, что строка удовлетворяет всем добавленным фильтрам
    bool matches(const std::string &logLine) const override;

private:
    std::vector<std::unique_ptr<ILogFilter>> filters;
};

#endif // COMPOSITE_FILTER_H
