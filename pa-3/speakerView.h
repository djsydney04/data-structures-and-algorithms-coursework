/*
Dylan Mitic
2441836
Mitic@chapman.edu
CPSC 350-01
PA-3
*/

#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include <string>

class SpeakerView {
public:
    // Constructor
    SpeakerView(const std::string& fileName);
    // Destructor
    ~SpeakerView();
    // Compute views
    void computeViews() const;

private:
    // Grid of double values
    double** grid;
    // Number of rows
    int rows;
    // Number of columns
    int cols;
    
    // Read file function
    void readFile(const std::string& fileName);
    // Clear memory function
    void clearMemory();
    // Count columns function
    int countColumns(const std::string& line) const;
};

#endif