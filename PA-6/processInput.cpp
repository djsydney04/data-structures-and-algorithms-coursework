#include "WGraph.h"
#include <iostream>
#include <fstream>
#include <string>

void processInput(WGraph<std::string> &graph, std::string inputFile) {
    std::ifstream file(inputFile);
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "ADD") {
            std::string vertex;
            ss >> vertex;
            graph.addVertex(vertex);
        }
    }
}