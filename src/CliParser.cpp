// CliParser.cpp
#include "CliParser.h"
#include <iostream>

CliParser::CliParser() : errorMessage("") {}

std::string CliParser::getError() const {
    return errorMessage;
}

void CliParser::printUsage() const {
    std::cout << "How to use: log_parser --input <log_file> [--output <output_file_path>] "
                "[--regex_match <regular_expression>] [--regex_search <regular_expression>] "
                "[--level <log_level1> [<log_level2> ...]] [--exclude <excluded_string1> [<excluded_string2 ...]] "
                "[--exclude_regex <regular_expression>]\n";
}

bool CliParser::parse(int argc, char** argv, CliConfig &config) {
    if (argc < 2) {
        errorMessage = "Not enough arguments!!!";
        return false;
    }
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--input") {
            if (i + 1 < argc) {
                config.inputFile = extractParametrs(i, argc, argv);
            } if(config.inputFile.empty()) {
                errorMessage = "Syntax error: The flag --input requires a file path";
                return false;
            }
        } else if(arg == "--input_dir"){
            if(i + 1 < argc){
                config.inputDir = argv[++i];
            } else{
                errorMessage = "Syntax error: The flag --input_dir requires a correct path to log files";
                return false;
            }
        } else if (arg == "--output") {
            if (i + 1 < argc) {
                config.outputFile = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag --output requires a correct output path";
                return false;
            }
        } else if (arg == "--regex_match") {
            if (i + 1 < argc) {
                config.regexMatch = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag -- regex_match requires a regular expression";
                return false;
            }
        } else if (arg == "--regex_search") {
            if (i + 1 < argc) {
                config.regexSearch = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag --regex_search requires a regular expression";
                return false;
            }
        } else if (arg == "--level") {
            // После флага --level могут идти один или несколько уровней,
            // пока следующий аргумент не начинается с "--" или не закончились аргументы.
            config.levels = extractParametrs(i, argc, argv);
            if (config.levels.empty()) {
                errorMessage = "Syntax error: The flag --level requires level(levels)";
                return false;
            }
        } else if(arg == "--exclude"){
            config.exclude = extractParametrs(i, argc, argv);
            if(config.exclude.empty()){
                errorMessage = "Syntax error: The flag --exclude requires at least one parametr";
                return false;
            }
        } else if(arg == "--exclude_regex"){
            if(i + 1 < argc){
                config.excludeRegex = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag --exclude-regex must contain one argument at least";
                return false;
            }
        } else if(arg == "--help"){
            errorMessage = "Action: The user requested instuction";
            return false;
        } else {
            errorMessage = "Error: Unknown argument: " + arg;
            return false;
        }
    }

    // Проверка существования входного файла
    for(size_t i = 0; i < config.inputFile.size(); ++i){
        if(!FileManager::fileExists(config.inputFile[i])){
            errorMessage += "Input file does not exist: " + config.inputFile[i] + "\n";
            config.inputFile.erase(config.inputFile.begin() + i);
        }
    }

    //if none valid input files left, the function will return false
    if(config.inputFile.empty()){
        errorMessage += "Error: None of the files was valid. Try again...";
        return false;
    }

    // Если выходной файл не задан, можно установить значение по умолчанию
    if (config.outputFile.empty()) {
        config.outputFile = "output.log";
    }

    return true;
}

std::vector<std::string> CliParser::extractParametrs(int& currentIndex, int argc, char** argv){
    std::vector<std::string> parametrs;
    while(currentIndex+1 < argc){
        std::string nextArg = argv[currentIndex+1];
        if(nextArg.rfind("--", 0) == 0){
            break;
        }
        parametrs.push_back(nextArg);
        ++currentIndex;
    }
    return parametrs;
}
