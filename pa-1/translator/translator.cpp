#include "translator.h"
#include <sstream>
#include <string>

Translator::Translator() {
    // constructor
}

Translator::~Translator() {
    // destructor
}
//const reference to avoid copying the string and modifying it unnecessarily
std::string Translator::translateEnglishWord(const std::string& word) const {
    // translate a single English word
    std::string translatedWord;

    for (char c : word) {
        // check if the character is a vowel
        if (model.isVowel(c)) {
            // translate the vowel
            translatedWord += model.translateSingleVowel(c);
        } else {
            // translate the consonant
            translatedWord += model.translateSingleConsonant(c);
        }
    }

    return translatedWord;
}
//const reference to avoid copying the string and modifying it unnecessarily
std::string Translator::translateEnglishSentence(const std::string& sentence) const {
    ///stream the sentece into words (from standard library)
    std::istringstream iss(sentence);
    // string to store the current word
    std::string word;
    // string to store the translated sentence
    std::string translatedSentence;
    // iterate through each word in the sentence
    while (iss >> word) {
        // add a space between words
        if (!translatedSentence.empty()) {
            translatedSentence += ' ';
        }
        // translate the current word and add it to the translated sentence
        translatedSentence += translateEnglishWord(word);
    }
    // return the translated sentence
    return translatedSentence;
}