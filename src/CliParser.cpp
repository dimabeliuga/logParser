#include "CliParser.h"
#include "FileManager.h"  // Для проверки существования файлов
#include <sstream>

CliParser::CliParser() : errorMessage("") {}

std::string CliParser::getError() const {
    return errorMessage;
}

void CliParser::printUsage() const {
    std::cout << "Usage: log_parser --input <log_file1> [<log_file2> ...] [--input_dir <directory>] "
              << "[--output <output_file_path>] [--regex_match <regex>] [--regex_search <regex>] "
              << "[--level <log_level1> [<log_level2> ...]] [--exclude <word1> [<word2> ...]] "
              << "[--exclude_regex <regex>] [--config <config_file>]\n";
}

bool CliParser::parse(int argc, char** argv, CliConfig &config) {
    if (argc < 2) {
        errorMessage = "Not enough arguments!";
        return false;
    }
    
    // Перебор аргументов командной строки
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            errorMessage = "User requested help\n";
            return false;
        } 
        else if (arg == "--input") {
            // Извлекаем один или несколько параметров после флага --input
            config.inputFile = extractParameters(i, argc, argv);
            if (config.inputFile.empty()) {
                errorMessage = "Syntax error: The flag --input requires at least one file path.";
                return false;
            }
        } 
        else if (arg == "--input_dir") {
            if (i + 1 < argc) {
                config.inputDir = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag --input_dir requires a valid directory path.";
                return false;
            }
        } 
        else if (arg == "--config") {
            if (i + 1 < argc) {
                config.configuration = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag --config requires a valid configuration file path.";
                return false;
            }
        } 
        else if (arg == "--output") {
            if (i + 1 < argc) {
                config.outputFile = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag --output requires a valid output file path.";
                return false;
            }
        } 
        else if (arg == "--regex_match") {
            if (i + 1 < argc) {
                config.regexMatch = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag --regex_match requires a regular expression.";
                return false;
            }
        } 
        else if (arg == "--regex_search") {
            if (i + 1 < argc) {
                config.regexSearch = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag --regex_search requires a regular expression.";
                return false;
            }
        } 
        else if (arg == "--level") {
            config.levels = extractParameters(i, argc, argv);
            if (config.levels.empty()) {
                errorMessage = "Syntax error: The flag --level requires at least one log level.";
                return false;
            }
        } 
        else if (arg == "--exclude") {
            config.exclude = extractParameters(i, argc, argv);
            if (config.exclude.empty()) {
                errorMessage = "Syntax error: The flag --exclude requires at least one parameter.";
                return false;
            }
        } 
        else if (arg == "--exclude_regex") {
            if (i + 1 < argc) {
                config.excludeRegex = argv[++i];
            } else {
                errorMessage = "Syntax error: The flag --exclude_regex requires a regular expression.";
                return false;
            }
        } 
        else {
            errorMessage = "Error: Unknown argument: " + arg;
            return false;
        }
    }
    
    return inputDataValidation(config);
}

std::vector<std::string> CliParser::extractParameters(int &currentIndex, int argc, char** argv) {
    std::vector<std::string> parameters;
    // Извлекаем все параметры, пока следующий аргумент не начинается с "--" или не достигнут конец аргументов
    while (currentIndex + 1 < argc) {
        std::string nextArg = argv[currentIndex + 1];
        if (nextArg.rfind("--", 0) == 0) {
            break;
        }
        parameters.push_back(nextArg);
        ++currentIndex;
    }
    return parameters;
}


void CliParser::loadConfig(CliConfig& config){
    std::ifstream inFile(config.configuration);
    if(!inFile.is_open()){
        std::cerr << "Error: impossible to open the configuration file";
        return ;
    }

    std::string line;
    while(std::getline(inFile, line)){
        //if line is comment or empty, we skip this line
        if(line.empty() || line[0] == '#'){
            continue;
        }

        std::istringstream iss(line);
        std::string key, value;

        if(std::getline(iss, key, '=') && std::getline(iss, value)){
            if(key == "--input"){
                config.inputFile.push_back(value);
            } else if(key == "--input_dir"     && !config.inputDir.empty()){
                config.inputDir = value;
            } else if(key == "--output"        && !config.outputFile.empty()){
                config.outputFile = value;
            } else if(key == "--regex_match"   && !config.regexMatch.empty()){
                config.regexMatch = value;
            } else if(key == "--regex_search"  && !config.regexSearch.empty()){
                config.regexSearch = value;
            } else if(key == "--exclude_regex" && !config.excludeRegex.empty()){
                config.excludeRegex = value;
            } else if(key == "--exclude"){
                std::istringstream excludeWords(value);
                std::string word;
                while(excludeWords >> word){
                    config.exclude.push_back(word);
                }
            } else if(key == "--level"){
                std::istringstream listLevels(value);
                std::string level;
                while (listLevels >> level){
                    config.levels.push_back(level);
                }
            }
        }
    }
    inFile.close();
}


bool CliParser::inputDataValidation(CliConfig& config){
    if(!config.configuration.empty()){
        loadConfig(config);
    }

    if(!config.inputDir.empty()){
        FileManager::getLogFilesFromDirectory(config.inputDir, config.inputFile);
    }
    // Валидация входных файлов: удаляем несуществующие файлы
    for (size_t i = 0; i < config.inputFile.size(); ) {
        if (!FileManager::fileExists(config.inputFile[i])) {
            errorMessage += "Input file does not exist: " + config.inputFile[i] + "\n";
            config.inputFile.erase(config.inputFile.begin() + i);
        } else {
            ++i;
        }
    }

    if (config.inputFile.empty()) {
        errorMessage += "Error: None of the input files are valid. Please check file paths.";
        return false;
    }

    config.outputFile = FileManager::validateOutputPath(config.outputFile);
    
    return true;
}