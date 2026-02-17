#include "mario.h"

mario::mario()
{

}

mario::~mario()
{

}

//Getters

int mario::getNumberOfLives() const
{
    return numberOfLives;
}

int mario::getCoins() const
{
    return coins;
}

int mario::getPowerLevel() const {
    return powerLevel;
}

int mario::getRow() const {
    return row;
}

int mario::getColumn() const {
    return column;
}

int mario::getEnemiesKilled() const {
    return enemiesKilled;
}

void mario::collectCoin() {
    coins++;
}

void mario::eatMushroom() {
    powerLevel++;
}

void mario::takeDamage() {
    numberOfLives--;
}

void mario::gainLife() {
    numberOfLives++;
}

void mario::killEnemy() {
    enemiesKilled++;
}

void mario::setPosition(int newRow, int newCol) {
    row = newRow;
    column = newCol;
}

bool mario::isAlive() const {
    return numberOfLives > 0;
}