// FileManager.cpp
#include "FileManager.h"
#include <iostream>
#include <filesystem>
#include <cstdlib>    
#include <fstream>

namespace fs = std::filesystem;

bool FileManager::fileExists(const std::string& path) {
    return fs::exists(path) && fs::is_regular_file(path);
}

std::string FileManager::validateOutputPath(std::string& outputPath) {
    fs::path outPath(outputPath);
    fs::path parentPath = outPath.parent_path();
    fs::path fileName   = outPath.filename();

    // If no parent directory is specified, assume the file will be created in the current directory.
    if (parentPath.empty()) {
        // If file name is empty, assign a default file name.
        if (fileName.empty()) {
            outputPath = "output.log";
            outPath = outputPath;
        }
        // If file name is provided but has no extension, handle this case.
        else if (fileName.extension().empty()) {
            handleMissingExtension(outPath);
        }
        // Otherwise, a file name with an extension is provided; nothing needs to be done.
    } else {
        // If a parent directory is provided but the file name is missing,
        // append the default file name.
        if (fileName.empty()) {
            fileName = "output.log";
            outPath /= fileName;
        }
    }

    // Update parentPath and fileName after possible modifications.
    parentPath = outPath.parent_path();
    fileName = outPath.filename();

    // If the specified parent directory does not exist,
    // prompt the user to save the file in the current directory.
    if (!fs::exists(parentPath)) {
        outPath = promptForNonExistentDirectory(parentPath, fileName);
    }

    return outPath.string();
}

void FileManager::handleMissingExtension(fs::path& outPath) {
    // Prompt the user to clarify whether the provided input is a directory or a file,
    // since the file name does not have an extension.
    fs::path fileName = outPath.filename();
    std::cout << "The provided file name \"" << fileName.string() << "\" does not contain an extension.\n"
              << "Choise an actio:\n"
              << "1) it is a directory,\n"
              << "2) it is a file,\n"
              << "Your choice(1/2): ";
    if(userChoice()){
        outPath = fs::path(fileName.string()) / "output.log";
    } else {
        outPath += ".log";
    }
}

fs::path FileManager::promptForNonExistentDirectory(const fs::path& parentPath, const fs::path& fileName) {
    // Ask the user if they want to use the current directory if the specified one doesn't exist.
    std::cout << "Directory \"" << parentPath.string() 
              << "\" does not exist. Save file in the current directory? (y/n): ";
    char response;
    std::cin >> response;
    if (response == 'y' || response == 'Y') {
        fs::path newPath = fs::current_path() / fileName;
        std::cout << "New path selected: " << newPath.string() << std::endl;
        return newPath;
    } else {
        std::cerr << "Cannot use the specified path. Exiting program.\n";
        exit(EXIT_FAILURE);
    }
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