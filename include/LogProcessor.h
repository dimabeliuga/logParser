#ifndef LOG_PROCESSOR_H
#define LOG_PROCESSOR_H

#include "ILogFilter.h"
#include "FileManager.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

/**
 * @class LogProcessor
 * @brief Handles the processing and filtering of log files
 */
class LogProcessor {
public:
    /**
     * @brief Constructs a LogProcessor with input and output paths
     * @param inputPaths Vector of paths to input log files
     * @param outputPath Path where processed logs will be written
     */
    LogProcessor(const std::vector<std::string>& inputPaths, const std::string& outputPath);

    /**
     * @brief Main method to process logs with the specified filter
     * @param filter Filter to be applied on log entries
     */
    void process(const ILogFilter& filter) const;

private:
    std::vector<std::string> inputFiles; ///< List of input file paths
    std::string outputFile;              ///< Output file path

    /**
     * @brief Processes all input files into a single output file
     * @param filter Filter to be applied on log entries
     */
    void processMergedOutput(const ILogFilter& filter) const;
    
    /**
     * @brief Processes each input file into separate output files
     * @param filter Filter to be applied on log entries
     */
    void processSeparateOutputs(const ILogFilter& filter) const;
    
    /**
     * @brief Process a single input file with the given filter
     * @param inputFilePath Path to the input file
     * @param outFile Output file stream
     * @param filter Filter to be applied on log entries
     */
    void processFile(const std::string& inputFilePath, std::ofstream& outFile, const ILogFilter& filter) const;
    
    /**
     * @brief Determines the file open mode for output files
     * @param filePath Path to the file
     * @return ios_base::openmode The mode to open the file (append or truncate)
     */
    std::ios_base::openmode getOutputFileMode(const std::string& filePath) const;
};

#endif // LOG_PROCESSOR_H
