/*
 * Full Name: Dylan Mitic
 * Student ID: 2441836
 * Chapman Email: mitic@chapman.edu
 * Course Number and Section: CPSC 350-02
 * Assignment Number: pa-4
 */

#include "block.h"

#include <sstream>
#include <string>

using namespace std;

Block::Block(int index, const std::string& data, const std::string& prevHash) {
    blockIndex = index;
    blockData = data;
    previousHash = prevHash;
    timeStamp = calculateTimestamp();
    currentHash = calculateHash();
    next = nullptr;
}

Block::Block(int index, const std::string& timestamp, const std::string& data,
             const std::string& prevHash, const std::string& currHash) {
    blockIndex = index;
    timeStamp = timestamp;
    blockData = data;
    previousHash = prevHash;
    currentHash = currHash;
    next = nullptr;
}

Block::~Block() {}

int Block::getBlockIndex() const { return blockIndex; }

std::string Block::getTimeStamp() const { return timeStamp; }

std::string Block::getBlockData() const { return blockData; }

std::string Block::getPreviousHash() const { return previousHash; }

std::string Block::getCurrentHash() const { return currentHash; }

Block* Block::getNext() const { return next; }

void Block::setNext(Block* nextBlock) { next = nextBlock; }

// timestamp computation using <ctime> library. For more information, see:
// https://www.w3schools.com/cpp/cpp_date.asp
std::string Block::calculateTimestamp() const {
    time_t now = time(nullptr);
    std::string timestamp = std::string(ctime(&now));
    if (!timestamp.empty() && timestamp.back() == '\n') {
        timestamp.pop_back();
    }
    return timestamp;
}

std::string Block::calculateHash() const {
    std::string dataCombined =
        std::to_string(blockIndex) + timeStamp + blockData + previousHash;
    int asciiSum = calculateASCIISum(dataCombined);
    std::string hexSum = convertAsciiToHex(asciiSum);
    return hexSum;
}

int Block::calculateASCIISum(const std::string& dataCombined) const {
    int totalSum = 0;
    for (unsigned char ch : dataCombined) {
        totalSum += static_cast<int>(ch);
    }
    return totalSum;
}

std::string Block::convertAsciiToHex(int num) const {
    std::stringstream ss;
    ss << std::hex << num;
    return ss.str();
}
