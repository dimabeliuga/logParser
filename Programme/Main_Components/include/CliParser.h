#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include "FileManager.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/**
 * @struct CliConfig
 * @brief Structure for storing command line arguments
 */
struct CliConfig {
    std::vector<std::string> inputFile;    ///< Input file paths
    std::string inputDir;                  ///< Path to a directory with log-files
    std::string outputFile;                ///< Output file path
    std::string regexMatch;                ///< Regular expression for exact match
    std::string regexSearch;               ///< Regular expression for searching
    std::string excludeRegex;              ///< Regular expression for excluding lines
    std::string configuration;             ///< Config file path 
    std::vector<std::string> exclude;      ///< List of excluded word(-s) that should be absent in the line
    std::vector<std::string> levels;       ///< List of log levels 
};

/**
 * @class CliParser
 * @brief Class for parsing command line arguments
 */
class CliParser {
public:
    /**
     * @brief Default constructor
     */
    CliParser();
    
    /**
     * @brief Parse command line arguments and save result to config
     * @param argc Number of command line arguments
     * @param argv Array of command line arguments
     * @param config Configuration structure to store parsed arguments
     * @return true if parsing was successful, false otherwise
     */
    bool parse(int argc, char** argv, CliConfig &config);
    
    /**
     * @brief Get the error message if parsing failed
     * @return String containing the error message
     */
    std::string getError() const;
    
    /**
     * @brief Print usage instructions for the program
     */
    void printUsage() const;
    
private:
    std::string errorMessage;  ///< Stores error messages during parsing
    
    /**
     * @brief Helper function to get arguments following a flag
     * @param currentIndex Current position in argument array
     * @param argc Total number of arguments
     * @param argv Array of arguments
     * @return Vector of extracted parameters
     */
    std::vector<std::string> extractParameters(int &currentIndex, int argc, char** argv);

    /**
     * @brief Extract configuration from user's file
     * @param config Configuration structure to update
     */
    void loadConfig(CliConfig& config);

    /**
     * @brief Validate config file, input files and output file
     * @param config Configuration to validate
     * @return true if validation successful, false otherwise
     */
    bool inputDataValidation(CliConfig& config);
};

#endif // CLI_PARSER_H
