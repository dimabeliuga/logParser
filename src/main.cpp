// main.cpp
#include <iostream>
#include "CliParser.h"
#include "FileManager.h"
#include "LogProcessor.h"
#include "Filters/CompositeFilter.h"

int main(int argc, char** argv) {
    // Разбор аргументов командной строки
    CliConfig config;
    CliParser parser;
    if (!parser.parse(argc, argv, config)) {
        std::cerr << "Problem: " << parser.getError() << std::endl;
        parser.printUsage();
        return EXIT_FAILURE;
    }
    
    //Check if the user requested the programm instruction
    if(config.helpCommandRequested){
        parser.printUsage();
        return EXIT_SUCCESS;
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
    compositeFilter.buildCompositeFilters(config);
    
    // Инициализация LogProcessor и запуск обработки логов
    LogProcessor logProcessor(config.inputFile, validatedOutputPath, overwriteMode);
    logProcessor.process(compositeFilter);
    
    system("pause");
    return EXIT_SUCCESS;
}
