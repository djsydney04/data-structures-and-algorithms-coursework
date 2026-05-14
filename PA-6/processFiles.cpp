#include "WGraph.h"
#include <iostream>
#include <fstream>
#include <string>



void processInput(WGraph<std::string> &graph, std::string inputFile) {
    //Number of vertices in the graph
    int numVertices;
    //weight of the edge 
    double weight; 
    // end of the file 
    std::string endOfFile;
    // open the input file
    std::ifstream file(inputFile);
    // error if the file can not be opened
    if (!file.is_open()) {
        throw std::invalid_argument("Could not open input file");
    }
    // reads the number of vertices from the first line of the file
    file >> numVertices;
    // create a graph with the number of vertices 
    graph = WGraph<std::string>(numVertices);
    // for each vertex, read the edges from the file
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            // read the weight of the edge from the file
            file >> weight;
            // if the weight is not 0 and the edge is not already in the graph, add the edge to the graph
            if (weight != 0 && i < j) {
                // add the edge between i and j vertices with the weight
                graph.addEdge(i, j, weight);
            }
        }
    }
    // read the end of the file
    file >> endOfFile;
    // if the end of the file is not "END", throw an error
    if (endOfFile != "END") {
        throw std::invalid_argument("Invalid input file");
    }
    // close the file
    file.close();
}