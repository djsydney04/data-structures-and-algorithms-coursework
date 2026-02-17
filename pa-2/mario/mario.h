#ifndef MARIO_H
#define MARIO_H

class mario
{
public:
    mario();
    ~mario();
    //constructor
    Mario(int initialLives, int startRow, int startCol);

    //getters
    int getNumberOfLives() const;
    int getCoins() const;
    int getPowerLevel() const;
    int getRow() const;
    int getColumn() const;
    int getEnemiesKilled() const;

    //game mechanics 
    void collectCoin();
    void eatMushroom();
    void takeDamage();
    void gainLife();
    void killEnemy();

    //movement 
    void setPosition(int newRow, int newCol);

    //status checks/checkers
    bool isAlive() const;

private:
    int numberOfLives;
    int coins;
    int powerLevel;
    int row;
    int column;
    int enemiesKilled;

};

#endif