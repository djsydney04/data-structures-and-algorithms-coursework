#include <iostream>
#include <sstream>
#include <string>

#include "../block/block.h"

namespace {
std::string expectedHashFor(const Block& block) {
    const std::string combined =
        std::to_string(block.getBlockIndex()) +
        block.getTimeStamp() +
        block.getBlockData() +
        block.getPreviousHash();

    int asciiSum = 0;
    for (unsigned char ch : combined) {
        asciiSum += static_cast<int>(ch);
    }

    std::stringstream ss;
    ss << std::hex << asciiSum;
    return ss.str();
}

bool expect(bool condition, const std::string& passMessage, const std::string& failMessage) {
    if (condition) {
        std::cout << "[PASS] " << passMessage << '\n';
        return true;
    }

    std::cerr << "[FAIL] " << failMessage << '\n';
    return false;
}

void printExampleBlock(const Block& block) {
    std::cout << "\nExample Block\n";
    std::cout << "index: " << block.getBlockIndex() << '\n';
    std::cout << "timestamp: " << block.getTimeStamp();
    if (!block.getTimeStamp().empty() && block.getTimeStamp().back() != '\n') {
        std::cout << '\n';
    }
    std::cout << "data: " << block.getBlockData() << '\n';
    std::cout << "previous hash: " << block.getPreviousHash() << '\n';
    std::cout << "current hash: " << block.getCurrentHash() << '\n';
}
}

int main() {
    Block block(1, "hello world", "0000");
    bool allPassed = true;

    allPassed = expect(
        block.getBlockIndex() == 1,
        "Constructor stored the block index.",
        "Expected block index 1."
    ) && allPassed;

    allPassed = expect(
        block.getBlockData() == "hello world",
        "Constructor stored the block data.",
        "Expected block data \"hello world\"."
    ) && allPassed;

    allPassed = expect(
        block.getPreviousHash() == "0000",
        "Constructor stored the previous hash.",
        "Expected previous hash \"0000\"."
    ) && allPassed;

    allPassed = expect(
        !block.getTimeStamp().empty(),
        "Timestamp was generated.",
        "Expected a non-empty timestamp."
    ) && allPassed;

    const std::string expectedHash = expectedHashFor(block);
    allPassed = expect(
        block.getCurrentHash() == expectedHash,
        "Current hash matches the expected hash.",
        "Current hash did not match the expected hash."
    ) && allPassed;

    allPassed = expect(
        block.calculateHash() == expectedHash,
        "calculateHash() matches the expected hash.",
        "calculateHash() did not match the expected hash."
    ) && allPassed;

    if (!allPassed) {
        return 1;
    }

    printExampleBlock(block);
    std::cout << "\nAll Block tests passed.\n";

    return 0;
}
