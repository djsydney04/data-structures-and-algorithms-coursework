/*
 * Full Name: Dylan Mitic
 * Student ID: 2441836
 * Chapman Email: mitic@chapman.edu
 * Course Number and Section: CPSC 350-02
 * Assignment Number: pa-4
 */

#include "blockchain.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//constructor for the Blockchain class
//initializes the head, tail, and size of the blockchain
Blockchain::Blockchain() {
    head = nullptr;
    tail = nullptr;
    size = 0;
    addBlock("Genesis Block");
}

Blockchain::~Blockchain() {
    clearChain();
}

//clear the blockchain
void Blockchain::clearChain() {
    //set the current block to the head of the blockchain
    Block* current = head;
    //iterate through the blockchain and delete each block
    while (current != nullptr) {
        Block* next = current->getNext();
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}
//add a block to the blockchain
void Blockchain::addBlock(const std::string& data) {
    //set the previous hash to the hash of the last block
    std::string previousHash = "0";
    //if the tail is not null, set the previous hash to the hash of the last block
    if (tail != nullptr) {
        previousHash = tail->getCurrentHash();
    }
    //create a new block with the data and previous hash
    Block* newBlock = new Block(size, data, previousHash);
    //if the head is null, set the head to the new block
    if (head == nullptr) {
        //set the head to the new block
        head = newBlock;
    } else {
        //set the next block to the new block
        tail->setNext(newBlock);
    }
    //set the tail to the new block
    tail = newBlock;
    //increment the size of the blockchain
    size++;
}
//get a block from the blockchain
Block* Blockchain::getBlock(int index) const {
    //if the index is out of range, return nullptr
    if (index < 0 || index >= size) {
        return nullptr;
    }
    //set the current block to the head of the blockchain
    Block* current = head;
    //iterate through the blockchain and return the block at the index
    for (int i = 0; i < index; i++) {
        current = current->getNext();
    }
    //return the block at the index
    return current;
}
//display the blockchain
void Blockchain::displayChain() const {
    //set the current block to the head of the blockchain
    Block* current = head;
    //iterate through the blockchain and display the block at the index
    while (current != nullptr) {
        std::cout << current->getBlockIndex() << '|'
                  << current->getTimeStamp() << '|'
                  << current->getBlockData() << '|'
                  << current->getPreviousHash() << '|'
                  << current->getCurrentHash() << '\n';
        current = current->getNext();
    }
}

bool Blockchain::validateChain() const {
    //set the current block to the head of the blockchain
    Block* current = head;
    //set the previous block to nullptr
    Block* previous = nullptr;
    //iterate through the blockchain and validate the block
    while (current != nullptr) {
        //if the current hash is not the same as the calculated hash, return false
        if (current->getCurrentHash() != current->calculateHash()) {
            return false;
        }
        //if the previous hash is not the same as the calculated hash, return false
        if (previous != nullptr &&
            current->getPreviousHash() != previous->calculateHash()) {
            return false;
        }
        //set the previous block to the current block
        previous = current;
        current = current->getNext();
    }
    //return true if the blockchain is valid
    return true;
}

//save the blockchain to a file
void Blockchain::saveToFile(const std::string& filename) const {
    //open the file
    std::ofstream file(filename);
    Block* current = head;
    //iterate through the blockchain and save the block at the index
    while (current != nullptr) {
        file << current->getBlockIndex() << '|'
             << current->getTimeStamp() << '|'
             << current->getBlockData() << '|'
             << current->getPreviousHash() << '|'
             << current->getCurrentHash() << '\n';
        current = current->getNext();
    }
}

//load the blockchain from a file
void Blockchain::loadFromFile(const std::string& filename) {
    //open the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    //clear the blockchain  
    clearChain();

    std::string line;
    //iterate through the file and load the block at the index
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream lineStream(line);
        std::string indexField;
        std::string timestampField;
        std::string dataField;
        std::string previousHashField;
        std::string currentHashField;
        //get the index, timestamp, data, previous hash, and current hash from the line
        if (!std::getline(lineStream, indexField, '|') ||
            !std::getline(lineStream, timestampField, '|') ||
            !std::getline(lineStream, dataField, '|') ||
            !std::getline(lineStream, previousHashField, '|') ||
            !std::getline(lineStream, currentHashField)) {
            continue;
        }
        //create a new block with the index, timestamp, data, previous hash, and current hash
        Block* loadedBlock = new Block(std::stoi(indexField), timestampField,
                                       dataField, previousHashField,
                                       currentHashField);
        //if the head is null, set the head to the loaded block
        if (head == nullptr) {
            head = loadedBlock;
        } else {
            //set the next block to the loaded block
            tail->setNext(loadedBlock);
        }
        //set the tail to the loaded block
        tail = loadedBlock;
        //increment the size of the blockchain
        size++;
    }
}
