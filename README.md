# LogParser

LogParser is a modular C++ command-line application designed for parsing and filtering log files. It supports multiple input methods including individual log files and directories containing log files. The application offers advanced filtering capabilities using regular expressions, log level filtering, and exclusion criteria. It is built with extensibility in mind, allowing you to easily add new filters and configuration options.

## Features

- **Multiple Input Sources**:  
  Accepts single or multiple log files as well as entire directories of log files.
  
- **Advanced Filtering**:  
  - **Regex Matching**: Filter lines that completely match a specified regular expression (`--regex_match`).  
  - **Regex Search**: Filter lines that contain a substring matching a regular expression (`--regex_search`).  
  - **Log Level Filtering**: Include only lines containing specific log levels (`--level`).  
  - **Exclusion Filters**: Exclude lines containing specified keywords (`--exclude`) or matching a regex pattern (`--exclude_regex`).
  
- **Configuration File Support**:  
  Load default parameters from a configuration file.

- **Extensible Architecture**:  
  Easily add new filters and processing modules.

- **CMake Build System**:  
  Uses CMake for building the project.

- **Unit Testing**:  
  Includes unit tests using GoogleTest to ensure code quality and reliability.

## Requirements

- **C++17** or higher
- **CMake** 3.10 or above
- **GoogleTest** (for running tests)
- A compatible C++ compiler (GCC, Clang, or MSVC)

## Installation and Build

### Building the Project

1. **Clone the Repository**

   ```bash
   git clone https://github.com/your_username/LogParser.git
   cd LogParser
2. **Configure and Build**
Create a build directory and run CMake:
   ```bash
   mkdir build && cd build
   cmake .. 
   cmake --build .
This will build the main executable LogParser and the library.

3. **Running the Application**
Run the executable from the build directory. For example:
   ```bash
   ./LogParser --input log1.txt log2.txt --output output.log --regex_match "^[ERROR].*" --level ERROR WARN --exclude Pixel

This command reads the specified log files, filters lines that fully match the regex (e.g., lines starting with [ERROR]), filters by log levels (ERROR or WARN), excludes lines containing the word Pixel, and writes the results to output.log.

4. Running Tests
To build and run tests (ensure GoogleTest is installed):
   ```bash
   ctest --verbose
Alternatively, you can run each test executable individually from the build directory.

## Documentation ##
Documentation is generated using Doxygen.

Generate a Doxyfile:
   ```bash
   doxygen -g

Contributing
Contributions are welcome! Please fork the repository, make your changes, and open a pull request. Ensure your code adheres to the project standards and includes appropriate tests.
