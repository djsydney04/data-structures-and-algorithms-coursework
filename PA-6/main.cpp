#include "WGraph.h"
#include <iostream>
#include <fstream>

int main() {
    // create a graph
    WGraph<std::string> graph;
    // process the input
    processInput(graph, "input.txt");
    // print the graph
    graph.print();
    return 0;
}