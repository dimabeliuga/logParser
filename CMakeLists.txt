cmake_minimum_required(VERSION 3.10)

project(LogParser LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем директорию с исходными файлами
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/Filters)

# Перечисляем исходные файлы проекта
set(SOURCES
    src/main.cpp
    src/CliParser.cpp
    src/FileManager.cpp
    src/LogProcessor.cpp
    src/Filters/RegexMatchFilter.cpp
    src/Filters/RegexSearchFilter.cpp
    src/Filters/LevelFilter.cpp
    src/Filters/CompositeFilter.cpp
    src/Filters/ExcludeFilter.cpp
    src/Filters/ExcludeRegexFilter.cpp
)

# Создаем исполняемый файл
add_executable(LogParser ${SOURCES})
