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
}

Block::~Block() {}

int Block::getBlockIndex() const { return blockIndex; }

std::string Block::getTimeStamp() const { return timeStamp; }

std::string Block::getBlockData() const { return blockData; }

std::string Block::getPreviousHash() const { return previousHash; }

std::string Block::getCurrentHash() const { return currentHash; }

// timestamp computation using <ctime> library. For more information, see:
// https://www.w3schools.com/cpp/cpp_date.asp
std::string Block::calculateTimestamp() const {
    time_t now = time(nullptr);
    return std::string(ctime(&now));
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
