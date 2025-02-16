// FileManager.h
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

class FileManager {
public:
    //Check if the file exist
    static bool fileExists(const std::string& path);

    //Output path validation
    //If parent directory does not exist, suggest to store in the current directory
    static std::string validateOutputPath(std::string& outputPath);

    //Check if a file with the given name exists 
    static bool fileAlreadyExists(const std::string& path);

    //Ask the user if they want to overwrite an existing file or append to the end
    //Returns true of overwrite mode is selected, false for appending
    static bool promptOverwriteOrAppend(const std::string& filePath);

    //ask the user if he want to merge all logs in one file or seperate them
    static bool promptMergeFilesorSeperate(const size_t inputFilesNumber);

    //extract all log files from the directory that the user input
    static void getLogFilesFromDirectory(std::string& directoryPath, std::vector<std::string>& logFiles);

private:
    //helper function for promt functions
    static bool userChoice();
    // Handles the case when the file name is provided without an extension.
    static void handleMissingExtension(std::filesystem::path& outPath);

    //helper function to find out files' extensions the user wants to extract from the folder
    static std::vector<std::string> askDesiredExtensions();

    // Prompts the user when the parent directory does not exist and returns a new path in the current directory.
    static std::filesystem::path promptForNonExistentDirectory(const std::filesystem::path& parentPath, const std::filesystem::path& fileName);

};

#endif // FILE_MANAGER_H
