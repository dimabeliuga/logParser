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
    std::vector<std::string> exclude;
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
};

#endif // CLI_PARSER_H
