// ILogFilter.h
#ifndef ILOGFILTER_H
#define ILOGFILTER_H

#include <string>

class ILogFilter {
public:
    virtual ~ILogFilter() = default;
    // Метод проверки строки лога. Возвращает true, если строка удовлетворяет условию фильтра.
    virtual bool matches(const std::string& logLine) const = 0;
};

#endif // ILOGFILTER_H
