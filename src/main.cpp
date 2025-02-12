// main.cpp
#include <iostream>
#include "CliParser.h"
#include "FileManager.h"
#include "LogProcessor.h"

// Фильтры
#include "Filters/CompositeFilter.h"
#include "Filters/RegexMatchFilter.h"
#include "Filters/RegexSearchFilter.h"
#include "Filters/LevelFilter.h"

int main(int argc, char** argv) {
    // Разбор аргументов командной строки
    CliConfig config;
    CliParser parser;
    if (!parser.parse(argc, argv, config)) {
        std::cerr << "Ошибка при разборе аргументов: " << parser.getError() << std::endl;
        parser.printUsage();
        return EXIT_FAILURE;
    }
    
    // Проверка существования входного файла
    if (!FileManager::fileExists(config.inputFile)) {
        std::cerr << "Входной файл не существует: " << config.inputFile << std::endl;
        return EXIT_FAILURE;
    }
    
    // Валидация пути для выходного файла
    std::string validatedOutputPath = FileManager::validateOutputPath(config.outputFile);
    
    // Если файл уже существует, запрашиваем у пользователя режим записи (перезапись или дозапись)
    bool overwriteMode = true;
    if (FileManager::fileAlreadyExists(validatedOutputPath)) {
        overwriteMode = FileManager::promptOverwriteOrAppend(validatedOutputPath);
    }
    
    // Создание составного фильтра, который объединяет активные проверки
    CompositeFilter compositeFilter;
    
    // Если указан флаг --regex_match, добавляем фильтр полного соответствия
    if (!config.regexMatch.empty()) {
        compositeFilter.addFilter(std::make_unique<RegexMatchFilter>(config.regexMatch));
    }
    
    // Если указан флаг --regex_search, добавляем фильтр поиска совпадений
    if (!config.regexSearch.empty()) {
        compositeFilter.addFilter(std::make_unique<RegexSearchFilter>(config.regexSearch));
    }
    
    // Если указан флаг --level, добавляем фильтр уровней логов
    if (!config.levels.empty()) {
        compositeFilter.addFilter(std::make_unique<LevelFilter>(config.levels));
    }
    
    // Инициализация LogProcessor и запуск обработки логов
    LogProcessor logProcessor(config.inputFile, validatedOutputPath, overwriteMode);
    logProcessor.process(compositeFilter);
    
    system("pause");
    return EXIT_SUCCESS;
}
