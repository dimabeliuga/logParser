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

void CompositeFilter::buildCompositeFilters(const CliConfig& config){
    // Если указан флаг --regex_match, добавляем фильтр полного соответствия
    if (!config.regexMatch.empty()) {
        addFilter(std::make_unique<RegexMatchFilter>(config.regexMatch));
    }
    
    // Если указан флаг --regex_search, добавляем фильтр поиска совпадений
    if (!config.regexSearch.empty()) {
        addFilter(std::make_unique<RegexSearchFilter>(config.regexSearch));
    }
    
    // Если указан флаг --level, добавляем фильтр уровней логов
    if (!config.levels.empty()) {
        addFilter(std::make_unique<LevelFilter>(config.levels));
    }
    
    if(!config.exclude.empty()){
        addFilter(std::make_unique<ExcludeFilter>(config.exclude));
    }
    if(!config.excludeRegex.empty()){
        addFilter(std::make_unique<ExcludeRegexFilter>(config.excludeRegex));
    }
}
