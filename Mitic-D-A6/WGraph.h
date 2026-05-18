/*
Full name: Dylan Mitic
Student ID: 2441836
Chapman email: mitic@chapman.edu
Course number and section: CPSC 350-02
Assignment or exercise number: A6
*/

#ifndef WGRAPH_H
#define WGRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits> 
#include <set>
#include <queue>

// CLASS TO REPRESENT EACH VERTEX
template <typename T>
class Vertex {
public:
    T name; // Each vertex has a 'name' of type T
    Vertex(T n); // Constructor
    ~Vertex(); // Destructor
};

// Constructor for the Vertex class
template <typename T>
Vertex<T>::Vertex(T n) { name = n; } // Assign 'name' during construction

// Destructor for the Vertex class
template <typename T>
Vertex<T>::~Vertex() {}

// CLASS TO REPRESENT A WEIGHTED GRAPH
template <typename T>
class WGraph {
public:
    WGraph(int sz); // Constructor to initialize graph of a given size
    ~WGraph(); // Destructor to clean up dynamic allocations

    void addVertex(T name);
    void addEdge(T name1, T name2, double weight);
    void computeMST(); // Compute MST using Kruskal's algorithm
    double getMSTCost() const; // Return the total cost of the MST
    double getMSTWeight(int i, int j) const; // Return weight of edge (i,j) in the MST
    int getSize() const { return m_size; }

private:
    int m_size; // Maximum number of vertices in the graph
    double** m_adj; // 2D array representing adjacency matrix for edge weights
    double** m_mst; // 2D array representing MST adjacency matrix (0 = no edge in MST)
    double m_mstCost; // Sum of all edge weights in the MST
    std::vector<Vertex<T>> m_vertices; // List of vertices
    std::unordered_map<T, int> m_nameToIndex; // Map to track each vertex's index by name

    // Edge struct to represent an edge in the graph
    struct Edge {
        int u;
        int v;
        double weight;
    };

    // Compares edges so std::set keeps them sorted
    struct EdgeCompare {
        bool operator()(const Edge& a, const Edge& b) const {
            if (a.weight != b.weight) {
                return a.weight < b.weight;
            }
            if (a.u != b.u) {
                return a.u < b.u;
            }
            return a.v < b.v;
        }
    };
    // Build edge list from adjacency matrix for Kruskal
    std::vector<Edge> makeEdgeList();
    // BFS on m_mst; uses std::set to track visited vertices
    bool connectedInMST(int u, int v) const; 
};

// CONSTRUCTOR
template <typename T>
WGraph<T>::WGraph(int sz) {
    m_size = sz;
    m_vertices.clear();
    m_nameToIndex.clear();
    m_mstCost = 0.0;
    m_adj = nullptr;
    m_mst = nullptr;
    if (sz > 0) {
        m_adj = new double*[sz];
        m_mst = new double*[sz];
        for (int i = 0; i < sz; ++i) {
            m_adj[i] = new double[sz];
            m_mst[i] = new double[sz];
            for (int j = 0; j < sz; ++j) {
                m_adj[i][j] = std::numeric_limits<double>::max(); // infinity = no edge
                m_mst[i][j] = 0.0; // 0 = no edge in MST
            }
        }
    }
}

// DESTRUCTOR
template <typename T>
WGraph<T>::~WGraph() {
    // if the matrices are not null, return
    if (m_adj == nullptr) {
        return;
    }
    // goes through the matrices and deletes the memory
    for (int i = 0; i < m_size; ++i) {
        delete[] m_adj[i];
        delete[] m_mst[i];
    }
    // deletes the memory of the matrices
    delete[] m_adj;
    delete[] m_mst;
}

// Add a new vertex to the graph
template <typename T>
void WGraph<T>::addVertex(T name) {
    if (m_vertices.size() < static_cast<size_t>(m_size)) {
        m_vertices.push_back(Vertex<T>(name));
        m_nameToIndex[name] = static_cast<int>(m_vertices.size()) - 1;
    } else {
        std::cerr << "Graph capacity reached. Cannot add more vertices." << std::endl;
    }
}

// Add an edge with a weight between two vertices
template <typename T>
void WGraph<T>::addEdge(T name1, T name2, double weight) {
    if (m_nameToIndex.count(name1) > 0 && m_nameToIndex.count(name2) > 0) {
        int i = m_nameToIndex[name1];
        int j = m_nameToIndex[name2];
        m_adj[i][j] = weight;
        m_adj[j][i] = weight; // Symmetric for undirected graph
    } else {
        std::cerr << "One or both vertices not found in the graph." << std::endl;
    }
}

// MST STORAGE AND COMPUTATION

// Helper that builds a list of edges from the adjacency matrix that is passed in inside of the input file in order to use Kruskal's algorithm to compute the MST
template <typename T>
std::vector<typename WGraph<T>::Edge> WGraph<T>::makeEdgeList() {
    //create a vector to store the edges 
    std::vector<Edge> edges;
    // Loop through the adjacency matrix and add the edges to the vector
    for (int i = 0; i < m_size; ++i) {
        for (int j = i + 1; j < m_size; ++j) {
            // If the edge exists, add it to the vector
            if (m_adj[i][j] != std::numeric_limits<double>::max()) {
                // Add the edge to the vector
                edges.push_back({i, j, m_adj[i][j]});
            }
        }
    }
    // Return the vector of edges
    return edges;
}

// Returns true if v is reachable from u using only edges currently in m_mst
// This function uses BFS to check if the vertices are connected in the MST by interating through the vertices and checking if the edge weight is not 0 and the vertex is not already visited
template <typename T>
// int u and int v are the variables for the vertices to check if they are connected in the MST
bool WGraph<T>::connectedInMST(int u, int v) const {
    // If the vertices are the same, they are connected
    if (u == v) {
        return true;
    }
    // Create a set to track visited vertices
    std::set<int> visited;
    // Create a queue to track the vertices to visit
    std::queue<int> q;
    // Add the starting vertex to the queue and set
    q.push(u);
    // Add the starting vertex to the visited set
    visited.insert(u);
    // While the queue is not empty, dequeue the front vertex and check if it is the target vertex
    while (!q.empty()) {
        // Dequeue the front vertex
        int current = q.front();
        // Remove the front vertex from the queue
        q.pop();
        // If the current vertex is the target vertex, return true
        if (current == v) {
            return true;
        }
        // Loop through the vertices and add the vertices to the queue and set if they are not already visited and the edge weight is not 0
        for (int k = 0; k < m_size; ++k) {
            if (m_mst[current][k] != 0.0 && visited.count(k) == 0) {
                visited.insert(k);
                q.push(k);
            }
        }
    }

    return false;
}

// Implementation of Kruskal's algorithm to compute the MST
template <typename T>
void WGraph<T>::computeMST() {
    // Reset the MST Matrix
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < m_size; ++j) {
            m_mst[i][j] = 0.0;
        }
    }
    //Reset the MST Cost 
    m_mstCost = 0.0;

    // If the graph has only one vertex, return. Edge case but worth accounting for! 
    if (m_size <= 1) {
        return;
    }

    // build edge list then stick it in a set so we go lowest weight to highest
    std::vector<Edge> edgeList = makeEdgeList();
    std::set<Edge, EdgeCompare> sortedEdges(edgeList.begin(), edgeList.end());

    // go through edges and add them if u and v arent already connected (BFS + set for visited)
    int edgesAdded = 0;
    for (const Edge& edge : sortedEdges) {
        if (connectedInMST(edge.u, edge.v)) {
            continue; // would form a cycle, skip this edge 
        }
        // add edge to m_mst and add weight to total cost
        m_mst[edge.u][edge.v] = edge.weight;
        m_mst[edge.v][edge.u] = edge.weight;
        // Add the edge weight to the MST cost
        m_mstCost += edge.weight;
        // Increment edges added
        ++edgesAdded;
        // If the number of edges added is equal to the number of vertices minus 1, the MST is complete
        if (edgesAdded == m_size - 1) {
            break;
        }
    }
}

//getter functions

//return MST Cost
template <typename T>
double WGraph<T>::getMSTCost() const {
    return m_mstCost;
}

//return MST Weight
template <typename T>
double WGraph<T>::getMSTWeight(int i, int j) const {
    return m_mst[i][j];
}

#endif
