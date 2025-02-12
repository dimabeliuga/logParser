// LogProcessor.cpp
#include "LogProcessor.h"
#include <fstream>
#include <iostream>
#include <string>

LogProcessor::LogProcessor(const std::string &inputPath, const std::string &outputPath, bool overwrite)
    : inputFile(inputPath), outputFile(outputPath), overwriteMode(overwrite)
{
}

void LogProcessor::process(const ILogFilter &filter) const {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть входной файл: " << inputFile << std::endl;
        return;
    }
    
    std::ios_base::openmode mode = std::ios::out;
    if (overwriteMode) {
        mode |= std::ios::trunc;  // Перезапись файла
    } else {
        mode |= std::ios::app;    // Добавление в конец файла
    }
    
    std::ofstream outFile(outputFile, mode);
    if (!outFile.is_open()) {
        std::cerr << "Не удалось открыть выходной файл: " << outputFile << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(inFile, line)) {
        if (filter.matches(line)) {
            outFile << line << std::endl;
        }
    }
    
    inFile.close();
    outFile.close();
    
    std::cout << "Обработка логов завершена. Результат сохранен в: " << outputFile << std::endl;
}
