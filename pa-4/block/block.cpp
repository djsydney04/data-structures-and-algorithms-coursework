#include <block/block.h>
#include <ctime>
#include <string>

using namespace std;

Block::Block(int index, const std::string& data, const std::string& prevHash){
    blockIndex = index;
    blockData = data;
    previousHash = prevHash;
    timeStamp = calculateTimestamp();
    currentHash = calculateHash();
}

Block::~Block(){
    //destructor
}

int Block::getBlockIndex() const{
    return blockIndex;
}

//timestamp computation using <ctime> library. For more information, see: https://www.w3schools.com/cpp/cpp_date.asp
std::string Block::calculateTimestamp() const{
    //get current time and set it to the timeStamp
   time_t now = time(nullptr);
   //return the current time as a human-readable string
   return std::string(ctime(&now));
}