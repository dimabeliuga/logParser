// main.cpp
#include <iostream>
#include "Filters/CompositeFilter.h"
#include "LogProcessor.h"

//1) пересмотреть cliparser.cpp
//2) пересмотреть отпут

int main(int argc, char** argv) {
    // Разбор аргументов командной строки
    CliConfig config;
    CliParser parser;
    if (!parser.parse(argc, argv, config)) {
        std::cerr << parser.getError() << std::endl;
        parser.printUsage();
        return EXIT_FAILURE;
    }

    // Создание составного фильтра, который объединяет активные проверки
    CompositeFilter compositeFilter;
    compositeFilter.buildCompositeFilters(config);
    
    // Инициализация LogProcessor и запуск обработки логов
    LogProcessor logProcessor(config.inputFile, config.outputFile);
    logProcessor.process(compositeFilter);
    
    return EXIT_SUCCESS;
}
