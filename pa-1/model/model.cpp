#include "model.h"
#include <cctype>   // std::isalpha, std::tolower, std::toupper

Model::Model() {
    // constructor
}

Model::~Model() {
    // destructor
}

bool Model::isVowel(char c) const {
    char lower = static_cast<char>(std::tolower(c)); // convert char c to lowercase
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
}

bool Model::isConsonant(char c) const {
    char lower = static_cast<char>(std::tolower(c)); // convert char c to lowercase
    return std::isalpha(c) && !isVowel(c); // consonant if alphabetic and not a vowel
}

std::string Model::translateSingleConsonant(char c) const {
    if (!isConsonant(c)) {
        return std::string(1, c); // return unchanged if not consonant
    }
    return std::string(1, c) + "o" + std::string(1, c);
}

std::string Model::translateSingleVowel(char c) const {
    return std::string(1, c);
}