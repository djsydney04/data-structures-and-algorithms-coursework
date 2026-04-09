#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../blockchain/blockchain.h"

namespace {
bool expect(bool condition, const std::string& passMessage,
            const std::string& failMessage) {
    if (condition) {
        std::cout << "[PASS] " << passMessage << '\n';
        return true;
    }

    std::cerr << "[FAIL] " << failMessage << '\n';
    return false;
}

int countPipes(const std::string& line) {
    int pipeCount = 0;
    for (char ch : line) {
        if (ch == '|') {
            pipeCount++;
        }
    }
    return pipeCount;
}

bool containsInOrder(const std::string& text, const std::string& first,
                     const std::string& second) {
    std::size_t firstPos = text.find(first);
    std::size_t secondPos = text.find(second);

    return firstPos != std::string::npos &&
           secondPos != std::string::npos &&
           firstPos < secondPos;
}

std::string replaceCurrentHash(const std::string& line,
                               const std::string& newHash) {
    std::size_t lastPipe = line.rfind('|');
    if (lastPipe == std::string::npos) {
        return line;
    }

    return line.substr(0, lastPipe + 1) + newHash;
}

std::string replacePreviousHash(const std::string& line,
                                const std::string& newPreviousHash) {
    std::stringstream lineStream(line);
    std::string indexField;
    std::string timestampField;
    std::string dataField;
    std::string previousHashField;
    std::string currentHashField;

    if (!std::getline(lineStream, indexField, '|') ||
        !std::getline(lineStream, timestampField, '|') ||
        !std::getline(lineStream, dataField, '|') ||
        !std::getline(lineStream, previousHashField, '|') ||
        !std::getline(lineStream, currentHashField)) {
        return line;
    }

    return indexField + "|" + timestampField + "|" + dataField + "|" +
           newPreviousHash + "|" + currentHashField;
}
}

int main() {
    bool allPassed = true;

    {
        Blockchain chain;
        Block* genesis = chain.getBlock(0);
        Block* missing = chain.getBlock(1);

        allPassed = expect(
            genesis != nullptr,
            "Constructor creates a genesis block.",
            "Expected the blockchain constructor to create a genesis block."
        ) && allPassed;

        allPassed = expect(
            genesis != nullptr && genesis->getBlockIndex() == 0,
            "Genesis block index is 0.",
            "Expected the genesis block to have index 0."
        ) && allPassed;

        allPassed = expect(
            genesis != nullptr && genesis->getBlockData() == "Genesis Block",
            "Genesis block uses the required default data.",
            "Expected genesis block data to be \"Genesis Block\"."
        ) && allPassed;

        allPassed = expect(
            genesis != nullptr && genesis->getPreviousHash() == "0",
            "Genesis block previous hash is 0.",
            "Expected genesis block previous hash to be \"0\"."
        ) && allPassed;

        allPassed = expect(
            genesis != nullptr && !genesis->getCurrentHash().empty(),
            "Genesis block hash is computed.",
            "Expected the genesis block to have a computed hash."
        ) && allPassed;

        allPassed = expect(
            missing == nullptr,
            "getBlock() returns nullptr for an out-of-range index.",
            "Expected getBlock() to return nullptr for an invalid index."
        ) && allPassed;
    }

    {
        Blockchain chain;
        chain.addBlock("Elia sent Erik 1000 Panther Coins");
        chain.addBlock("Erik sent Elizabeth 88 Panther Coins");

        Block* genesis = chain.getBlock(0);
        Block* firstTransaction = chain.getBlock(1);
        Block* secondTransaction = chain.getBlock(2);

        allPassed = expect(
            firstTransaction != nullptr &&
                firstTransaction->getBlockIndex() == 1,
            "addBlock() assigns the next sequential index.",
            "Expected the first added block to have index 1."
        ) && allPassed;

        allPassed = expect(
            firstTransaction != nullptr &&
                firstTransaction->getBlockData() ==
                    "Elia sent Erik 1000 Panther Coins",
            "addBlock() stores transaction data.",
            "Expected the added block to store the provided transaction data."
        ) && allPassed;

        allPassed = expect(
            genesis != nullptr && firstTransaction != nullptr &&
                firstTransaction->getPreviousHash() ==
                    genesis->getCurrentHash(),
            "Added blocks link to the previous block hash.",
            "Expected the first added block to reference the genesis hash."
        ) && allPassed;

        allPassed = expect(
            firstTransaction != nullptr && secondTransaction != nullptr &&
                secondTransaction->getPreviousHash() ==
                    firstTransaction->getCurrentHash(),
            "Later blocks link to the immediately preceding block hash.",
            "Expected the second added block to reference block 1's hash."
        ) && allPassed;

        allPassed = expect(
            chain.validateChain(),
            "validateChain() accepts a valid chain.",
            "Expected validateChain() to return true for a valid chain."
        ) && allPassed;
    }

    {
        Blockchain chain;
        chain.addBlock("Alice paid Bob 5 Panther Coins");
        chain.addBlock("Bob paid Carol 2 Panther Coins");

        std::ostringstream displayBuffer;
        std::streambuf* originalBuffer = std::cout.rdbuf(displayBuffer.rdbuf());
        chain.displayChain();
        std::cout.rdbuf(originalBuffer);

        const std::string displayedChain = displayBuffer.str();
        allPassed = expect(
            containsInOrder(displayedChain, "Genesis Block",
                            "Alice paid Bob 5 Panther Coins"),
            "displayChain() prints blocks in order.",
            "Expected displayChain() to print the genesis block before later transactions."
        ) && allPassed;

        allPassed = expect(
            displayedChain.find("Bob paid Carol 2 Panther Coins") !=
                std::string::npos,
            "displayChain() includes later transaction data.",
            "Expected displayChain() to print all block data."
        ) && allPassed;
    }

    const std::string savedChainPath = "/tmp/pa4_blockchain_saved.txt";
    {
        Blockchain chain;
        chain.addBlock("Elia sent Erik 1000 Panther Coins");
        chain.addBlock("Erik sent Elizabeth 88 Panther Coins");
        chain.saveToFile(savedChainPath);

        std::ifstream savedChain(savedChainPath);
        std::string firstLine;
        std::string secondLine;
        std::string thirdLine;

        std::getline(savedChain, firstLine);
        std::getline(savedChain, secondLine);
        std::getline(savedChain, thirdLine);
        savedChain.close();

        allPassed = expect(
            !firstLine.empty() && !secondLine.empty() && !thirdLine.empty(),
            "saveToFile() writes one line per block.",
            "Expected saveToFile() to write each block on its own line."
        ) && allPassed;

        allPassed = expect(
            countPipes(firstLine) == 4 && countPipes(secondLine) == 4 &&
                countPipes(thirdLine) == 4,
            "saveToFile() uses the required pipe-separated format.",
            "Expected each saved line to contain 5 pipe-separated fields."
        ) && allPassed;

        Blockchain loadedChain;
        loadedChain.loadFromFile(savedChainPath);

        Block* loadedGenesis = loadedChain.getBlock(0);
        Block* loadedFirstTransaction = loadedChain.getBlock(1);
        Block* loadedSecondTransaction = loadedChain.getBlock(2);

        allPassed = expect(
            loadedGenesis != nullptr &&
                loadedGenesis->getBlockData() == "Genesis Block" &&
                loadedFirstTransaction != nullptr &&
                loadedFirstTransaction->getBlockData() ==
                    "Elia sent Erik 1000 Panther Coins" &&
                loadedSecondTransaction != nullptr &&
                loadedSecondTransaction->getBlockData() ==
                    "Erik sent Elizabeth 88 Panther Coins",
            "loadFromFile() rebuilds the blockchain contents.",
            "Expected loadFromFile() to reconstruct all saved blocks."
        ) && allPassed;

        allPassed = expect(
            loadedChain.validateChain(),
            "A chain loaded from disk still validates successfully.",
            "Expected a loaded blockchain to remain valid."
        ) && allPassed;
    }

    const std::string tamperedCurrentHashPath =
        "/tmp/pa4_blockchain_bad_hash.txt";
    {
        Blockchain chain;
        chain.addBlock("Alice paid Bob 7 Panther Coins");
        chain.saveToFile(tamperedCurrentHashPath);

        std::ifstream originalFile(tamperedCurrentHashPath);
        std::string firstLine;
        std::string secondLine;
        std::getline(originalFile, firstLine);
        std::getline(originalFile, secondLine);
        originalFile.close();

        std::ofstream tamperedFile(tamperedCurrentHashPath);
        tamperedFile << firstLine << '\n'
                     << replaceCurrentHash(secondLine, "deadbeef") << '\n';
        tamperedFile.close();

        Blockchain tamperedChain;
        tamperedChain.loadFromFile(tamperedCurrentHashPath);

        allPassed = expect(
            !tamperedChain.validateChain(),
            "validateChain() rejects a block with a tampered current hash.",
            "Expected validateChain() to fail when a block hash is changed in the saved file."
        ) && allPassed;
    }

    const std::string tamperedPreviousHashPath =
        "/tmp/pa4_blockchain_bad_previous_hash.txt";
    {
        Blockchain chain;
        chain.addBlock("Alice paid Bob 7 Panther Coins");
        chain.addBlock("Bob paid Carol 3 Panther Coins");
        chain.saveToFile(tamperedPreviousHashPath);

        std::ifstream originalFile(tamperedPreviousHashPath);
        std::string firstLine;
        std::string secondLine;
        std::string thirdLine;
        std::getline(originalFile, firstLine);
        std::getline(originalFile, secondLine);
        std::getline(originalFile, thirdLine);
        originalFile.close();

        std::ofstream tamperedFile(tamperedPreviousHashPath);
        tamperedFile << firstLine << '\n'
                     << secondLine << '\n'
                     << replacePreviousHash(thirdLine,
                                            "incorrect_previous_hash")
                     << '\n';
        tamperedFile.close();

        Blockchain tamperedChain;
        tamperedChain.loadFromFile(tamperedPreviousHashPath);

        allPassed = expect(
            !tamperedChain.validateChain(),
            "validateChain() rejects a block whose previous hash does not match the earlier block.",
            "Expected validateChain() to fail when a block links to the wrong previous hash."
        ) && allPassed;
    }

    std::remove(savedChainPath.c_str());
    std::remove(tamperedCurrentHashPath.c_str());
    std::remove(tamperedPreviousHashPath.c_str());

    if (!allPassed) {
        return 1;
    }

    std::cout << "\nAll Blockchain tests passed.\n";
    return 0;
}
