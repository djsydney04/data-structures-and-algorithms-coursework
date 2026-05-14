#include "WGraph.h"
#include <string>
int main() {
    // Create the graph with sufficient size
    WGraph<std::string> graph();  

    // Add vertices (nodes)
    graph.addVertex("Whoville");
    graph.addVertex("Grinch's Cave");
    graph.addVertex("Mount Crumpit");
    graph.addVertex("Who Roast Beast Feast");
    graph.addVertex("Cindy Lou's House");
    graph.addVertex("Christmas Tree Plaza");
    graph.addVertex("Toy Workshop");

    // Add edges (connections with weights)
    graph.addEdge("Whoville", "Grinch's Cave", 10);
    graph.addEdge("Whoville", "Mount Crumpit", 5);
    graph.addEdge("Grinch's Cave", "Mount Crumpit", 3);
    graph.addEdge("Mount Crumpit", "Who Roast Beast Feast", 8);
    graph.addEdge("Who Roast Beast Feast", "Cindy Lou's House", 4);
    graph.addEdge("Cindy Lou's House", "Whoville", 6);
    graph.addEdge("Grinch's Cave", "Who Roast Beast Feast", 7);
    graph.addEdge("Whoville", "Christmas Tree Plaza", 2);
    graph.addEdge("Cindy Lou's House", "Christmas Tree Plaza", 3);
    graph.addEdge("Grinch's Cave", "Christmas Tree Plaza", 12);
    graph.addEdge("Mount Crumpit", "Toy Workshop", 6);
    graph.addEdge("Toy Workshop", "Christmas Tree Plaza", 4);
    graph.addEdge("Toy Workshop", "Who Roast Beast Feast", 9);
    graph.addEdge("Grinch's Cave", "Toy Workshop", 11);
    graph.addEdge("Cindy Lou's House", "Mount Crumpit", 7);

    // Display DFS traversal
    std::cout << "DFS Traversal from 'Whoville': ";
    for (const auto& node : graph.dfs("Whoville")) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    // Display BFS traversal
    std::cout << "BFS Traversal from 'Whoville': ";
    for (std::string node : graph.bfs("Whoville")) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    // Check for adjacency
    std::cout << "Are 'Whoville' and 'Grinch's Cave' adjacent? "
              << (graph.areAdjacent("Whoville", "Grinch's Cave") ? "Yes" : "No") << std::endl;

    // Get weight of an edge
    std::cout << "Weight of edge between 'Grinch's Cave' and 'Mount Crumpit': "
              << graph.getWeight("Grinch's Cave", "Mount Crumpit") << std::endl;

    // Count the number of islands
    std::cout << "Number of disconnected components (islands): " << graph.findIslands() << std::endl;

    std::cout << "Floyd Warshall: " << std::endl;
    std::cout << "Cheapest cost from Grinch's Cave to Mount Crumpit: " << graph.cheapestCost("Grinch's Cave", "Mount Crumpit") << std::endl;  
    std::cout << "Cheapest cost from Whoville to Christmas Tree Plaza: " << graph.cheapestCost("Whoville", "Christmas Tree Plaza") << std::endl;  

    return 0;
}