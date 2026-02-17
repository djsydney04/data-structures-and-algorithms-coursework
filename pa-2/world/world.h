#ifndef WORLD_H
#define WORLD_H

class World {
    private:
        char*** levels;
        int numLevels;
        int gridSize;
        
    public:
        // Construction & setup
        World(int L, int N);
        void populateLevel(int levelNum, int coinPercent, int goombaPercent, /*etc*/);
        
        // Basic access
        char getCell(int level, int row, int col);
        void setCell(int level, int row, int col, char value);
        
        // Game-specific operations
        void printLevel(int levelNum);
        bool isValidPosition(int level, int row, int col);
        
        // Maybe helper methods
        void clearCell(int level, int row, int col);  // Set to 'x' (nothing)
        int wrapCoordinate(int coord, int maxSize);   // Handle torus wrapping
};

#endif