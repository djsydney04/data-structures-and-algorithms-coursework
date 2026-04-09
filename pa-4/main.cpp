/*
 * Full Name: Dylan Mitic
 * Chapman Email: mitic@chapman.edu
 * Course Number and Section: CPSC 350-02
 * Assignment Number: pa-4
 */

#include <iostream>
#include <string>

#include "blockchain/blockchain.h"

//Read an integer from the CLI
//This is used to read the user's choice from the CLI
int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            return -1;
        }
        try {
            return std::stoi(line);
        } catch (...) {
            std::cout << "Please enter a valid number.\n";
        }
    }
}
//Read the string input from the CLI
//This is used to read the user's input from the CLI 
//after choosing an option from the menu
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

//Print the CLI menu 
void printMenu() {
    std::cout << "\n=== Blockchain Ledger ===\n"
              << "1) Add a new block\n"
              << "2) Display the blockchain\n"
              << "3) Validate the blockchain\n"
              << "4) Save blockchain to file\n"
              << "5) Load blockchain from file\n"
              << "6) Exit\n";
}

int main() {
    //create a new blockchain
    Blockchain chain;

    while (true) {
        //print the menu
        printMenu();
        //read the user's choice from the CLI
        const int choice = readInt("Choose an option: ");
        
        if (choice == 1) { //add a new block
            const std::string data = readLine("Enter block data: ");
            chain.addBlock(data);
            std::cout << "Block added.\n";
        } else if (choice == 2) { //display the blockchain
            chain.displayChain();
        } else if (choice == 3) { //validate the blockchain
            const bool ok = chain.validateChain();
            std::cout << (ok ? "Blockchain is VALID.\n" : "Blockchain is INVALID.\n");
        } else if (choice == 4) { //save the blockchain to a file
            const std::string filename = readLine("Enter output filename: ");
            chain.saveToFile(filename);
            std::cout << "Saved.\n";
        } else if (choice == 5) {
            const std::string filename = readLine("Enter input filename: ");
            chain.loadFromFile(filename);
            std::cout << "Loaded.\n";
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "Unknown option.\n";
        }
    }

    return 0;
}
