// LevelFilter.h
#ifndef LEVEL_FILTER_H
#define LEVEL_FILTER_H

#include "ILogFilter.h"
#include <vector>
#include <string>

class LevelFilter : public ILogFilter {
public:
    // Конструктор принимает вектор уровней логов
    explicit LevelFilter(const std::vector<std::string>& levels);

    // Метод проверяет, что строка лога содержит хотя бы один из указанных уровней
    bool matches(const std::string &logLine) const override;

private:
    std::vector<std::string> levels;
};

#endif // LEVEL_FILTER_H
