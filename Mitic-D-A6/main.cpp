/*
Full name: Dylan Mitic
Student ID: 2441836
Chapman email: mitic@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: A6
*/

#include "processFiles.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    // If the user does not provide an input file, return an error
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }
    // Open the input file
    std::ifstream file(argv[1]);
    // If the file is not open, throw an error
    if (!file.is_open()) {
        throw std::invalid_argument("Could not open input file");
    }
    // Read the number of vertices from the input file
    int numVertices = 0;
    // Read the number of vertices from the input file
    file >> numVertices;
    // Initialize the graph with the number of vertices
    WGraph<std::string> graph(numVertices);
    // Process the input
    processInput(file, graph);
    // Process the output
    processOutput(graph);
    // Return 0 if the program completes sucesfully 
    return 0;
}
