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

    //Main method to process logs with filtering
    void process(const ILogFilter& filter) const;

private:
    std::vector<std::string> inputFiles;
    std::string outputFile;

    //Log processing with merged output
    void processMergedOutput(const ILogFilter& filter) const;
    
    //Log processing with seperate output files for each input file
    void processSeparateOutputs(const ILogFilter& filter) const;
    
    //General process logic for one output file 
    void processFile(const std::string& inputFilePath, std::ofstream& outFile, const ILogFilter& filter) const;
    
    //Helper method to get the file open mode(trunc or append)
    std::ios_base::openmode getOutputFileMode(const std::string& filePath) const;
};

#endif // LOG_PROCESSOR_H
