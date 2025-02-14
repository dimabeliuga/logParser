// LogProcessor.h
#ifndef LOG_PROCESSOR_H
#define LOG_PROCESSOR_H

#include <string>
#include <vector>
#include "ILogFilter.h"

class LogProcessor {
public:
    // Конструктор принимает путь к входному файлу, путь к выходному файлу и флаг режима записи.
    // Если overwrite равен true, то файл будет перезаписан, иначе данные будут добавлены в конец.
    LogProcessor(const std::vector<std::string> &inputPath, const std::string &outputPath, bool overwrite);

    // Метод для обработки логов:
    // Читает входной файл построчно, применяет фильтрацию и записывает отфильтрованные строки в выходной файл.
    void process(const ILogFilter &filter) const;

private:
    std::vector<std::string> inputFiles;
    std::string outputFile;
    bool overwriteMode;

    void processWithEachFile(const std::string& inputFilePath, std::ofstream& outFile, const ILogFilter& filter) const;
};

#endif // LOG_PROCESSOR_H
