/*
Dylan Mitic
Mitic@chapman.edu
CPSC 350-01
PA-3
*/

#include "speakerView.h"
#include "monoStack.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

// Constructor
SpeakerView::SpeakerView(const std::string& fileName) {
    // Initialize grid to nullptr, rows to 0, and cols to 0
    grid = nullptr;
    rows = 0;
    cols = 0;
    readFile(fileName);
}

// Destructor
SpeakerView::~SpeakerView() {  
    clearMemory();
}

// Clear memory function
void SpeakerView::clearMemory() {
    // If grid is not nullptr, delete the grid
    if (grid != nullptr) {
        // Delete each row of the grid
        for (int i = 0; i < rows; ++i) {
            delete[] grid[i];
        }
        // Delete the grid
        delete[] grid;
        grid = nullptr;
    }
}

// Count columns function
int SpeakerView::countColumns(const std::string& line) const {
    // Create a stringstream from the line
    std::stringstream ss(line);
    double value;
    // Initialize count to 0
    int count = 0;
    // Count the number of values in the stringstream
    while (ss >> value) {
        ++count;
    }

    return count;
}

// Read file function
void SpeakerView::readFile(const std::string& fileName) {
    // Open the file
    std::ifstream inFile(fileName);
    // If the file is not open, throw a runtime error
    if (!inFile.is_open()) {
        throw std::runtime_error("Could not open input file.");
    }
    // Initialize line to an empty string
    std::string line;

    // Check BEGIN
    if (!std::getline(inFile, line) || line != "BEGIN") {
        throw std::runtime_error("Input file must start with BEGIN.");
    }

    // First pass: count rows and cols
    // Get the position of the data start
    std::streampos dataStart = inFile.tellg();
    // Initialize foundEnd to false
    bool foundEnd = false;
    // While there is a line in the file
    while (std::getline(inFile, line)) {
        // If the line is END, set foundEnd to true and break
        if (line == "END") {
            foundEnd = true;
            break;
        }

        // If the number of rows is 0, set the number of columns to the number of columns in the line
        if (rows == 0) {
            cols = countColumns(line);
            // If the number of columns is 0, throw a runtime error
            if (cols == 0) {
                throw std::runtime_error("First data row is empty.");
            }
        } else {
            // Get the number of columns in the line
            int currentCols = countColumns(line);
            // If the number of columns is not the same as the number of columns in the line, throw a runtime error
            if (currentCols != cols) {
                throw std::runtime_error("All rows must have the same number of columns.");
            }
        }

        ++rows;
    }

    // If the file does not end with END, throw a runtime error
    if (!foundEnd) {
        throw std::runtime_error("Input file must end with END.");
    }
    if (rows == 0) {
        throw std::runtime_error("Input file contains no audience rows.");
    }

    // Allocate and fill grid
    try {
        grid = new double*[rows];
        // Set each row to nullptr
        for (int i = 0; i < rows; ++i) {
            grid[i] = nullptr;
        }
        // Set each row to a new double array with the number of columns
        for (int i = 0; i < rows; ++i) {
            grid[i] = new double[cols];
        }

        // Second pass: actually read data
        inFile.clear();
        inFile.seekg(dataStart);
    
        for (int r = 0; r < rows; ++r) {
            // If there is no line, throw a runtime error
            if (!std::getline(inFile, line)) {
                throw std::runtime_error("Unexpected end of file while reading audience rows.");
            }
            // Create a stringstream from the line
            std::stringstream ss(line);
            // For each column in the row
            for (int c = 0; c < cols; ++c) {
                // If the value is not a number, throw a runtime error
                if (!(ss >> grid[r][c])) {
                    throw std::runtime_error("Invalid numeric input.");
                }
            }
        }
    } catch (...) { // Catch any exceptions
        // Clear the memory
        clearMemory();
        // Throw the exception
        throw;
    }
}

void SpeakerView::computeViews() const {
    for (int c = 0; c < cols; ++c) {
            // Create a mono stack with the number of rows and the order 'd'
            MonoStack<double> visible(rows, 'd');
    
            // scan from back row to front row
            for (int r = rows - 1; r >= 0; --r) {
                visible.push(grid[r][c]);
            }
            // Get the size of the visible stack
            int visibleCount = visible.size();
    
            // Print the number of visible people and their heights
            std::cout << "In column " << c << " there are "
                      << visibleCount << " that can see. Their heights are: ";
    
            // While the visible stack is not empty
            while (!visible.isEmpty()) {
                // Pop the top element of the visible stack and print it
                std::cout << visible.pop();
                // If the visible stack is not empty, print a comma
                if (!visible.isEmpty()) {
                    std::cout << ", ";
                }
            }
            
            std::cout << " inches." << std::endl;
    }
}
