#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <string>

class Blockchain {
private:
    Block* head;
    Block* tail;
    int size;

public:
    Blockchain();
    ~Blockchain();

    void addBlock(const std::string& data);
    Block* getBlock(int index) const;
    void displayChain() const;
    bool validateChain() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif