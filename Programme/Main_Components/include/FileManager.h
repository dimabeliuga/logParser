#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

/**
 * @brief Class for managing files.
 */
class FileManager {
public:
    /**
     * @brief Check if the file exists.
     * @param path Path to the file.
     * @return true if the file exists, false otherwise.
     */
    static bool fileExists(const std::string& path);

    /**
     * @brief Validate the output path.
     * If the parent directory does not exist, suggest storing in the current directory.
     * @param outputPath The output path to validate.
     * @return New path if the parent directory does not exist, otherwise returns the original path.
     */
    static std::string validateOutputPath(std::string& outputPath);

    /**
     * @brief Check if a file with the given name already exists.
     * @param path Path to the file.
     * @return true if the file already exists, false otherwise.
     */
    static bool fileAlreadyExists(const std::string& path);

    /**
     * @brief Ask the user if they want to overwrite an existing file or append to it.
     * @param filePath Path to the file.
     * @return true if overwrite mode is selected, false for appending.
     */
    static bool promptOverwriteOrAppend(const std::string& filePath);

    /**
     * @brief Ask the user if they want to merge all logs into one file or keep them separate.
     * @param inputFilesNumber The number of input files.
     * @return true if merging files is selected, false for keeping them separate.
     */
    static bool promptMergeFilesorSeperate(const size_t inputFilesNumber);

    /**
     * @brief Extract all log files from the directory provided by the user.
     * @param directoryPath Path to the directory.
     * @param logFiles Vector to store paths to log files.
     */
    static void getLogFilesFromDirectory(std::string& directoryPath, std::vector<std::string>& logFiles);

private:
    /**
     * @brief Helper function for prompt functions.
     * @return true for positive response, false otherwise.
     */
    static bool userChoice();

    /**
     * @brief Handles the case when the file name is provided without an extension.
     * @param outPath Path to the file.
     */
    static void handleMissingExtension(std::filesystem::path& outPath);

    /**
     * @brief Helper function to find the file extensions the user wants to extract from the folder.
     * @return Vector of strings containing desired file extensions.
     */
    static std::vector<std::string> askDesiredExtensions();

    /**
     * @brief Prompts the user when the parent directory does not exist and returns a new path in the current directory.
     * @param parentPath The parent directory path.
     * @param fileName The file name.
     * @return New path in the current directory.
     */
    static std::filesystem::path promptForNonExistentDirectory(const std::filesystem::path& parentPath, const std::filesystem::path& fileName);
};

#endif // FILE_MANAGER_H
