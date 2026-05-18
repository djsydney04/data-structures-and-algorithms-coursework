/*
Full name: Dylan Mitic
Student ID: 2441836
Chapman email: mitic@chapman.edu
Course number and section: CPSC 350-01
Assignment or exercise number: A6
*/

#include "processFiles.h"
#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>

// Print whole numbers like x.0 instead of x
std::string formatDouble(double value) {
    //create a stringstream to output the double
    std::ostringstream output;  
    //output the double to the stringstream
    output << value;
    //convert the stringstream to a string
    std::string text = output.str();
    //if the string does not contain a decimal point, add a '.0' to the end of the string
    if (text.find('.') == std::string::npos) {
        text += ".0";
    }
    //return the string
    return text;
}
//process the input file
void processInput(std::istream& input, WGraph<std::string>& graph) {
    // set the number of vertices to 0
    int numVertices = 0;
    // set the weight to 0.0
    double weight = 0.0;
    // set the end of file to an empty string
    std::string endOfFile;
    numVertices = graph.getSize();
    // loop through the number of vertices and add the vertices to the graph
    for (int i = 0; i < numVertices; ++i) {
        graph.addVertex(std::to_string(i));
    }
    // loop through the number of vertices and add the edges to the graph
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            // read the weight from the file
            input >> weight;
            // if the weight is not 0.0 and the vertex is less than the current vertex, add the edge to the graph
            if (weight != 0.0 && i < j) {
                graph.addEdge(std::to_string(i), std::to_string(j), weight);
            }
        }
    }
    // read the end of file from the file
    input >> endOfFile;
    // if the end of file is not "END", throw an error
    if (endOfFile != "END") {
        throw std::invalid_argument("Invalid input file");
    }
}

void processOutput(WGraph<std::string>& graph) {
    // Compute the MST`
    graph.computeMST();
    // Print the MST Cost
    std::cout << "The MST Cost is: " << formatDouble(graph.getMSTCost()) << std::endl;
    // Print the MST Matrix
    for (int i = 0; i < graph.getSize(); ++i) {
        for (int j = 0; j < graph.getSize(); ++j) {
            // Print the MST Weight
            // formats a double to a string so it is clear that it is a double and not an integer
            std::cout << formatDouble(graph.getMSTWeight(i, j));
            // Print a space if not the last column
            if (j + 1 < graph.getSize()) {
                std::cout << ' ';
            }
        }
        // Print a new line
        std::cout << std::endl;
    }
}
