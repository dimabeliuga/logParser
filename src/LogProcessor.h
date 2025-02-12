// LogProcessor.h
#ifndef LOG_PROCESSOR_H
#define LOG_PROCESSOR_H

#include <string>
#include "ILogFilter.h"

class LogProcessor {
public:
    // Конструктор принимает путь к входному файлу, путь к выходному файлу и флаг режима записи.
    // Если overwrite равен true, то файл будет перезаписан, иначе данные будут добавлены в конец.
    LogProcessor(const std::string &inputPath, const std::string &outputPath, bool overwrite);

    // Метод для обработки логов:
    // Читает входной файл построчно, применяет фильтрацию и записывает отфильтрованные строки в выходной файл.
    void process(const ILogFilter &filter) const;

private:
    std::string inputFile;
    std::string outputFile;
    bool overwriteMode;
};

#endif // LOG_PROCESSOR_H
