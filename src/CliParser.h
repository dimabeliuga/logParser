// CliParser.h
#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <string>
#include <vector>

// Структура для хранения параметров командной строки
struct CliConfig {
    std::string inputFile;      // Обязательный параметр: путь к файлу с логами
    std::string outputFile;     // Путь для сохранения файла с результатом (если не указан, можно задать значение по умолчанию)
    std::string regexMatch;     // Регулярное выражение для проверки полного соответствия строки
    std::string regexSearch;    // Регулярное выражение для поиска в строке
    std::string excludeRegex;   //regex expression for deleting log lines that match user expression
    std::vector<std::string> exclude; //list of words that the log string should not contain
    std::vector<std::string> levels; // Список уровней логов
    bool helpCommandRequested = false;  // Show the programm instruction 
};

class CliParser {
public:
    CliParser();
    
    // Метод для разбора аргументов командной строки, результат сохраняется в config
    bool parse(int argc, char** argv, CliConfig &config);
    
    // Возвращает сообщение об ошибке, если парсинг завершился неудачно
    std::string getError() const;
    
    // Вывод справки по использованию программы
    void printUsage() const;
    
private:
    std::string errorMessage;

    //helper function for parse function which is needed to extract parametrs from input line
    std::vector<std::string> extractParametrs(int& currentIndex, int argc, char** argv);

};

#endif // CLI_PARSER_H
