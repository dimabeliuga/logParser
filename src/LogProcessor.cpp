// LogProcessor.cpp
#include "LogProcessor.h"
#include <fstream>
#include <iostream>
#include <string>

LogProcessor::LogProcessor(const std::vector<std::string> &inputPath, const std::string &outputPath, bool overwrite)
    : inputFiles(inputPath), outputFile(outputPath), overwriteMode(overwrite)
{
}

void LogProcessor::process(const ILogFilter &filter) const {
    std::ios_base::openmode mode = std::ios::out;
    if (overwriteMode) {
        mode |= std::ios::trunc;  // Перезапись файла
    } else {
        mode |= std::ios::app;    // Добавление в конец файла
    }
    
    std::ofstream outFile(outputFile, mode);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open the output file: " << outputFile << std::endl;
        return;
    }
    for(std::string inputPath : inputFiles){
        processWithEachFile(inputPath, outFile, filter);
    }
    outFile.close();
    
    std::cout << "Log processing is over. Result has been saved to: " << outputFile << std::endl;
}


void LogProcessor::processWithEachFile(const std::string& inputFilePath, std::ofstream& outFile, const ILogFilter& filter) const{
    std::ifstream inFile(inputFilePath);
    if (!inFile.is_open()) {
        std::cerr << "Opening file failed: " << inputFilePath << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(inFile, line)) {
        if (filter.matches(line)) {
            outFile << line << std::endl;
        }
    }
    
    inFile.close();
}