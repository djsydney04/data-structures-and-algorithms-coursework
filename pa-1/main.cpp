#include "fileprocessor.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // validate arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }
    
    try {
        // create a file processor
        FileProcessor fileProcessor;
        // process the file (reads, translates, and writes HTML)
        fileProcessor.processFile(argv[1], argv[2]);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    
    return 0;
}