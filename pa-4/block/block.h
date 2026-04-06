#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>

class Block {
private:
    int blockIndex;
    std::string timeStamp;
    std::string blockData;
    std::string previousHash;
    std::string currentHash;

public:
    // constructor
    Block(int index, const std::string& data, const std::string& prevHash);
    // destructor
    ~Block();
    // getters
    int getBlockIndex() const;
    std::string getTimeStamp() const;
    std::string getBlockData() const;
    std::string getPreviousHash() const;
    std::string getCurrentHash() const;

    // hash computation
    std::string calculateHash() const;
    //timestamp computation
    std::string calculateTimestamp() const;
};

#endif