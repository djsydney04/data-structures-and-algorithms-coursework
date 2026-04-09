/*
Dylan Mitic
Mitic@chapman.edu
CPSC 350-01
PA-3
*/

#include "speakerView.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "No input file provided" << std::endl;
        return 1;
    }

    // Try to compute views
    try {
        SpeakerView sv(argv[1]);
        sv.computeViews();
    } catch (const std::exception& e) { // Catch any exceptions
        // Print the error message
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
