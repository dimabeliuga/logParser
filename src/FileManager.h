// FileManager.h
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include <filesystem>

class FileManager {
public:
    // Проверка существования файла по указанному пути
    static bool fileExists(const std::string& path);

    // Валидация выходного пути.
    // Если родительский каталог не существует, предложить сохранить в текущей директории.
    static std::string validateOutputPath(const std::string& outputPath);

    // Проверка, существует ли файл с данным именем
    static bool fileAlreadyExists(const std::string& path);

    // Запрос у пользователя, хочет ли он перезаписать существующий файл или дописать в конец.
    // Возвращает true, если выбран режим перезаписи, false – для дозаписи.
    static bool promptOverwriteOrAppend(const std::string& filePath);

    //ask the user if he want to merge all logs in one file or seperate them
    static bool promptMergeFilesorSeperate(const size_t inputFilesNumber);

    //extract all log files from the directory that the user input
    static void getLogFilesFromDirectory(std::string& directoryPath, std::vector<std::string>& logFiles);

private:
    //helper function for promt functions
    static bool userChoice();
};

#endif // FILE_MANAGER_H
