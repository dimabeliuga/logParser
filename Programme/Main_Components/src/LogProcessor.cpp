#include "LogProcessor.h"

namespace fs = std::filesystem;

LogProcessor::LogProcessor(const std::vector<std::string>& inputPaths, const std::string& outputPath)
    : inputFiles(inputPaths), outputFile(outputPath)
{
}

void LogProcessor::process(const ILogFilter& filter) const {
    //If the user choices merge output, we process all input files into one output file
    if (FileManager::promptMergeFilesorSeperate(inputFiles.size())) {
        processMergedOutput(filter);
    }
    //Otherwise, every input file will be processed seperately
    else {
        processSeparateOutputs(filter);
    }
}

void LogProcessor::processMergedOutput(const ILogFilter& filter) const {
    std::ios_base::openmode mode = getOutputFileMode(outputFile);
    std::ofstream outFile(outputFile, mode);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open the output file: " << outputFile << std::endl;
        return;
    }

    for (const auto& inputPath : inputFiles) {
        processFile(inputPath, outFile, filter);
    }
    std::cout << "Logs were written in " << outputFile << "\n";
    //outFile will be closed automaticly after exiting the scope
}

void LogProcessor::processSeparateOutputs(const ILogFilter& filter) const {
    for (const auto& inputFile : inputFiles) {
        fs::path inPath(inputFile);
        fs::path outPath(outputFile); 
        outPath = outPath.parent_path() / (inPath.stem().string() + "_parced" + inPath.extension().string());
        std::string outFilePath = outPath.string();
        std::cout << "\n" << outPath << "\n";
        std::ios_base::openmode mode = getOutputFileMode(outFilePath);
        std::ofstream outFile(outFilePath, mode);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open the output file: " << outFilePath << std::endl;
            continue; //move on to the next file
        }

        processFile(inputFile, outFile, filter);
        std::cout << "Logs were written in " << outPath << "\n";
    }
}

std::ios_base::openmode LogProcessor::getOutputFileMode(const std::string& filePath) const {
    bool overwriteMode = true;
    if (FileManager::fileAlreadyExists(filePath)) {
        overwriteMode = FileManager::promptOverwriteOrAppend(filePath);
    }
    // Режим всегда включает std::ios::out, а также trunc или app
    return std::ios::out | (overwriteMode ? std::ios::trunc : std::ios::app);
}

void LogProcessor::processFile(const std::string& inputFilePath, std::ofstream& outFile, const ILogFilter& filter) const {
    std::ifstream inFile(inputFilePath);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open the input file: " << inputFilePath << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(inFile, line)) {
        if (filter.matches(line)) {
            outFile << line << std::endl;
        }
    }
    // inFile will be closed automaticly after exiting the scope
}
