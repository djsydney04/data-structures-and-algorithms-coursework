/*
 * Full Name: Dylan Mitic
 * Chapman Email: mitic@chapman.edu
 * Course Number and Section: CPSC 350-02
 * Assignment Number: pa-4
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <ctime>
#include <sstream>

class Block {
private:
    int blockIndex;
    std::string timeStamp;
    std::string blockData;
    std::string previousHash;
    std::string currentHash;
    Block* next;
    //timestamp computation
    std::string calculateTimestamp() const;

    //calculateHash helper functions
    //calculate the ASCII sum of the combined data
    int calculateASCIISum(const std::string& dataCombined) const;
    //convert the ASCII sum to a hexadecimal string
    std::string convertAsciiToHex(int num) const;

public:
    // constructor
    Block(int index, const std::string& data, const std::string& prevHash);
    Block(int index, const std::string& timestamp, const std::string& data,
          const std::string& prevHash, const std::string& currHash);
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
    Block* getNext() const;
    void setNext(Block* nextBlock);

};
#endif
