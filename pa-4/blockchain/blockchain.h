/*
 * Full Name: Dylan Mitic
 * Student ID: 2441836
 * Chapman Email: mitic@chapman.edu
 * Course Number and Section: CPSC 350-02
 * Assignment Number: pa-4
 */

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "../block/block.h"
#include <string>

class Blockchain {
private:
    //head of the blockchain
    Block* head;
    //tail of the blockchain
    Block* tail;
    //size of the blockchain
    int size;
    //clear the blockchain
    void clearChain();

public:
    //constructor for the Blockchain class
    Blockchain();
    //destructor for the Blockchain class
    ~Blockchain();

    //add a block to the blockchain
    void addBlock(const std::string& data);
    //get a block from the blockchain
    Block* getBlock(int index) const;
    //display the blockchain
    void displayChain() const;
    //validate the blockchain
    bool validateChain() const;
    //save the blockchain to a file
    void saveToFile(const std::string& filename) const;
    //load the blockchain from a file
    void loadFromFile(const std::string& filename);
};

#endif
