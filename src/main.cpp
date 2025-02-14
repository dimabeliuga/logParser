// main.cpp
#include <iostream>
#include "Filters/CompositeFilter.h"
#include "LogProcessor.h"
#include "FileManager.h"

int main(int argc, char** argv) {
    // Разбор аргументов командной строки
    CliConfig config;
    CliParser parser;
    if (!parser.parse(argc, argv, config)) {
        std::cerr << parser.getError() << std::endl;
        parser.printUsage();
        return EXIT_FAILURE;
    }

    FileManager::getLogFilesFromDirectory(config.inputDir, config.inputFile);
    // Валидация пути для выходного файла
    std::string validatedOutputPath = FileManager::validateOutputPath(config.outputFile);

    // Создание составного фильтра, который объединяет активные проверки
    CompositeFilter compositeFilter;
    compositeFilter.buildCompositeFilters(config);
    
    // Инициализация LogProcessor и запуск обработки логов
    LogProcessor logProcessor(config.inputFile, validatedOutputPath);
    logProcessor.process(compositeFilter);
    
    return EXIT_SUCCESS;
}
