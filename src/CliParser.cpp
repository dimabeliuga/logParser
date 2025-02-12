// CliParser.cpp
#include "CliParser.h"
#include <iostream>

CliParser::CliParser() : errorMessage("") {}

std::string CliParser::getError() const {
    return errorMessage;
}

void CliParser::printUsage() const {
    std::cout << "Использование: log_parser --input <log_file> [--output <output_file_path>] "
                 "[--regex_match <regular_expression>] [--regex_search <regular_expression>] "
                 "[--level <log_level1> [<log_level2> ...]]\n";
}

bool CliParser::parse(int argc, char** argv, CliConfig &config) {
    if (argc < 2) {
        errorMessage = "Недостаточно аргументов.";
        return false;
    }
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "--input") {
            if (i + 1 < argc) {
                config.inputFile = argv[++i];
            } else {
                errorMessage = "Флаг --input требует указания пути к файлу.";
                return false;
            }
        } else if (arg == "--output") {
            if (i + 1 < argc) {
                config.outputFile = argv[++i];
            } else {
                errorMessage = "Флаг --output требует указания пути для сохранения файла.";
                return false;
            }
        } else if (arg == "--regex_match") {
            if (i + 1 < argc) {
                config.regexMatch = argv[++i];
            } else {
                errorMessage = "Флаг --regex_match требует указания регулярного выражения.";
                return false;
            }
        } else if (arg == "--regex_search") {
            if (i + 1 < argc) {
                config.regexSearch = argv[++i];
            } else {
                errorMessage = "Флаг --regex_search требует указания регулярного выражения.";
                return false;
            }
        } else if (arg == "--level") {
            // После флага --level могут идти один или несколько уровней,
            // пока следующий аргумент не начинается с "--" или не закончились аргументы.
            while (i + 1 < argc) {
                std::string nextArg = argv[i + 1];
                if (nextArg.rfind("--", 0) == 0) { // Если следующий аргумент начинается с "--", это новый флаг.
                    break;
                }
                config.levels.push_back(nextArg);
                ++i;
            }
            if (config.levels.empty()) {
                errorMessage = "Флаг --level требует указания хотя бы одного уровня логов.";
                return false;
            }
        } else {
            errorMessage = "Неизвестный аргумент: " + arg;
            return false;
        }
    }
    
    // Проверка обязательного параметра --input
    if (config.inputFile.empty()) {
        errorMessage = "Обязательный параметр --input не указан.";
        return false;
    }
    
    // Если выходной файл не задан, можно установить значение по умолчанию
    if (config.outputFile.empty()) {
        config.outputFile = "output.log";
    }
    
    return true;
}
