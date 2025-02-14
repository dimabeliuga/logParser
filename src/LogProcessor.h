#ifndef LOG_PROCESSOR_H
#define LOG_PROCESSOR_H

#include "ILogFilter.h"
#include "FileManager.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>


class LogProcessor {
public:
    LogProcessor(const std::vector<std::string>& inputPaths, const std::string& outputPath);

    // Основной метод обработки логов с фильтрацией
    void process(const ILogFilter& filter) const;

private:
    std::vector<std::string> inputFiles;
    std::string outputFile;

    // Обработка логов с объединённым выводом
    void processMergedOutput(const ILogFilter& filter) const;
    
    // Обработка логов с отдельными выходными файлами для каждого входного файла
    void processSeparateOutputs(const ILogFilter& filter) const;
    
    // Общая логика обработки одного входного файла
    void processFile(const std::string& inputFilePath, std::ofstream& outFile, const ILogFilter& filter) const;
    
    // Вспомогательный метод для получения режима открытия файла (trunc или append)
    std::ios_base::openmode getOutputFileMode(const std::string& filePath) const;
};

#endif // LOG_PROCESSOR_H
