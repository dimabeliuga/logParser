#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include "FileManager.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// Структура для хранения параметров командной строки
struct CliConfig {
    std::vector<std::string> inputFile;    // Пути к входным файлам
    std::string inputDir;                  // Путь к директории с лог-файлами
    std::string outputFile;                // Выходной файл или базовый путь для результатов
    std::string regexMatch;                // Регулярное выражение для полного совпадения
    std::string regexSearch;               // Регулярное выражение для поиска
    std::string excludeRegex;              // Регулярное выражение для исключения строк
    std::string configuration;             // Путь к конфигурационному файлу (txt)
    std::vector<std::string> exclude;      // Список слов, которые должны отсутствовать в строке
    std::vector<std::string> levels;       // Список уровней логов
};

class CliParser {
public:
    CliParser();
    
    // Разбор аргументов командной строки; результат сохраняется в config
    bool parse(int argc, char** argv, CliConfig &config);
    
    // Возвращает сообщение об ошибке (если парсинг завершился неудачно)
    std::string getError() const;
    
    // Вывод справки по использованию программы
    void printUsage() const;
    
private:
    std::string errorMessage;
    
    // Вспомогательная функция для извлечения параметров, следующих за флагом.
    std::vector<std::string> extractParameters(int &currentIndex, int argc, char** argv);

    //function to extract configs from the user's file
    void loadConfig(CliConfig& config);

    //helper function to check config file, input files and output file
    bool inputDataValidation(CliConfig& config);
};

#endif // CLI_PARSER_H
