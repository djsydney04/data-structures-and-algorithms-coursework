#include "world.h"

#include <random>

//construct the world with the given number of levels and grid size
World::World(int L, int N) : numLevels(L), gridSize(N) {
    levels = new char**[L];
    for (int i = 0; i < L; i++) {
        levels[i] = new char*[N];
        for (int j = 0; j < N; j++) {
            levels[i][j] = new char[N];
        }
    }
}

//set the cell at the given level, row, and column to the given value
void World::setCell(int level, int row, int col, char value) {
    levels[level][row][col] = value;
}

void World::randomizePositions(int* array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1); //random from 0 to i

        //swap the elements at indices i and j
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}


//populate the level with the given number of coins, goomba, and other game elements
void World::populateLevel(int levelNum, int coinPercent, int goombaPercent, int mushroomPercent, int nothingPercent, int koopaPercent) {
    //populate the level with coins, goomba, and other game elements
    int total cells = gridSize * gridSize;
    int coins = (coinP