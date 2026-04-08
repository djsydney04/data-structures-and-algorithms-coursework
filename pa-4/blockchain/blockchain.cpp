#include "blockchain.h"
#include "block.h"

#include <fstream>
#include <string>

Blockchain::Blockchain() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

Blockchain::~Blockchain() {
    Block* current = head;
    while (current != nullptr) {
        Block* next = current->next;
        delete current;
        current = next;
    }
}

void Blockchain::addBlock(const std::string& data) {
    Block* newBlock = new Block(size, data, tail->getCurrentHash());
    if (head == nullptr) {
        head = newBlock;
    } else {
        tail->setNext(newBlock);
    }
    tail = newBlock;
    size++;
}

Block* Blockchain::getBlock(int index) const {
    Block* current = head;
    for (int i = 0; i < index; i++) {
        current = current->getNext();
    }
    return current;
}

void Blockchain::displayChain() const {
    Block* current = head;
    while (current != nullptr) {
    }
}

bool Blockchain::validateChain() const {
    Block* current = head;
    while (current != nullptr) {
        if (current->getCurrentHash() != current->calculateHash()) {
            return false;
        }
        current = current->getNext();
    }
    return true;
}

void Blockchain::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    Block* current = head;
    while (current != nullptr) {
        file << current->getCurrentHash() << std::endl;
        current = current->getNext();
    }
    file.close();
}

void Blockchain::loadFromFile(const std::string& filename) {