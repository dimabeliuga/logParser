// main.cpp
#include <iostream>
#include "Filters/CompositeFilter.h"
#include "LogProcessor.h"

int main(int argc, char** argv) {
    // Parse command line arguments
    CliConfig config;
    CliParser parser;
    if (!parser.parse(argc, argv, config)) {
        std::cerr << parser.getError() << std::endl;
        parser.printUsage();
        return EXIT_FAILURE;
    }

    // Create composite filter with all active checks
    CompositeFilter compositeFilter;
    compositeFilter.buildCompositeFilters(config);
    
    // Process logs with configured filters
    LogProcessor logProcessor(config.inputFile, config.outputFile);
    logProcessor.process(compositeFilter);
    
    return EXIT_SUCCESS;
}
