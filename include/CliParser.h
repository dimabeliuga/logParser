#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include "FileManager.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// Structure for storing command line arguments

struct CliConfig {
    std::vector<std::string> inputFile;    // Input file paths
    std::string inputDir;                  // Path to a directory with log-files
    std::string outputFile;                // Output file path
    std::string regexMatch;                // Regular expression for exact match
    std::string regexSearch;               // Regular expression for searching
    std::string excludeRegex;              // Regular expression for excluding lines
    std::string configuration;             // Config file path 
    std::vector<std::string> exclude;      // List of excluded word(-s) that should be absent in the line
    std::vector<std::string> levels;       // List of log levels 
};

class CliParser {
public:
    CliParser();
    
    // Parse command line arguments; save result to config
    bool parse(int argc, char** argv, CliConfig &config);
    
    // Return error message (in case parsing went wrong)
    std::string getError() const;
    
    // Output instruction how to use programme
    void printUsage() const;
    
private:
    std::string errorMessage;
    
    // helper function to get arguments following the flag
    std::vector<std::string> extractParameters(int &currentIndex, int argc, char** argv);

    //function to extract configs from the user's file
    void loadConfig(CliConfig& config);

    //helper function to check config file, input files and output file
    bool inputDataValidation(CliConfig& config);
};

#endif // CLI_PARSER_H
