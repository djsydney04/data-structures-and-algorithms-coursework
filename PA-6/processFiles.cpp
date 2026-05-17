#include "WGraph.h"
#include <iostream>
#include <fstream>
#include <string>

static int g_numVertices = 0;

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
    g_numVertices = numVertices;
    // create a graph with the number of vertices 
    graph = WGraph<std::string>(numVertices);
    // add each vertex to the graph
    for (int i = 0; i < numVertices; i++) {
        graph.addVertex(std::to_string(i));
    }
    // for each vertex, read the edges from the file
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            // read the weight of the edge from the file
            file >> weight;
            // if the weight is not 0 and the edge is not already in the graph, add the edge to the graph
            if (weight != 0 && i < j) {
                // add the edge between i and j vertices with the weight
                graph.addEdge(std::to_string(i), std::to_string(j), weight);
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

void processOutput(WGraph<std::string> &graph, std::string outputFile) {
    // print the graph to the terminal using getWeight from WGraph
    for (int i = 0; i < g_numVertices; i++) {
        for (int j = 0; j < g_numVertices; j++) {
            // if the edge is not adjacent, print 0
            if (!graph.areAdjacent(std::to_string(i), std::to_string(j))) {
                std::cout << .0;
            } else {
                // else print the weight of the edge
                std::cout << graph.getWeight(std::to_string(i), std::to_string(j));
            }
            if (j + 1 < g_numVertices) {
                std::cout << ' ';
            }
        }
        // end of the line
        std::cout << std::endl;
    }
}
