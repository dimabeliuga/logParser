// FileManager.cpp
#include "FileManager.h"
#include <iostream>
#include <filesystem>
#include <cstdlib>    // для exit()
#include <fstream>

namespace fs = std::filesystem;

bool FileManager::fileExists(const std::string& path) {
    return fs::exists(path) && fs::is_regular_file(path);
}

std::string FileManager::validateOutputPath(const std::string& outputPath) {
    fs::path outPath(outputPath);
    fs::path parentPath = outPath.parent_path();

    // Если родительский путь пустой, значит файл будет создан в текущей директории
    if (parentPath.empty()) {
        return outputPath;
    }
    
    // Если каталог не существует, предлагаем использовать текущую директорию
    if (!fs::exists(parentPath)) {
        std::cout << "Каталог \"" << parentPath.string() 
                  << "\" не существует. Сохранить файл в текущей директории? (y/n): ";
        char response;
        std::cin >> response;
        if (response == 'y' || response == 'Y') {
            fs::path newPath = fs::current_path() / outPath.filename();
            std::cout << "Выбран новый путь: " << newPath.string() << std::endl;
            return newPath.string();
        } else {
            std::cerr << "Невозможно использовать указанный путь. Завершение программы.\n";
            exit(EXIT_FAILURE);
        }
    }
    return outputPath;
}

bool FileManager::fileAlreadyExists(const std::string& path) {
    return fs::exists(path) && fs::is_regular_file(path);
}

bool FileManager::promptOverwriteOrAppend(const std::string& filePath) {
    std::cout << "Файл \"" << filePath << "\" уже существует.\n";
    std::cout << "Выберите действие:\n";
    std::cout << "  1. Перезаписать файл\n";
    std::cout << "  2. Добавить данные в конец файла\n";
    std::cout << "Ваш выбор (1/2): ";
    
    return userChoice();
}

bool FileManager::promptMergeFilesorSeperate(const size_t inputFilesNumber){
    if(inputFilesNumber == 1){
        return true;
    }

    std::cout << "\nNumber of input files: " << inputFilesNumber;
    std::cout << "\nChoose an action:";
    std::cout << "\n1) write all logs to one file";
    std::cout << "\n2) Write each log separately";
    std::cout << "\nYour choise(1\2): ";
    
    return userChoice();
}

void FileManager::getLogFilesFromDirectory(std::string& directoryPath, std::vector<std::string>& logFiles){
    if(directoryPath.empty()){
        return;
    }
    
    if(!std::filesystem::exists(directoryPath) || !std::filesystem::is_directory(directoryPath)){
        std::cerr << "Error: Incorect directory path!!!" << std::endl;
        return;
    }
    
    for(const auto& entry : std::filesystem::directory_iterator(directoryPath)){
        if (entry.is_regular_file() && entry.path().extension() == ".log") {
            logFiles.push_back(entry.path().string());
        }
    }
}

bool FileManager::userChoice(){
    int choise;
    std::cin >> choise;
    if(choise == 1){
        return true;
    } else if(choise == 2){
        return false;
    } else {
        std::cerr << "\nWrong choise. Exit programm";
        exit(EXIT_FAILURE);
    }
}