#include "translator.h"
#include <sstream>
#include <string>

Translator::Translator() {
    // constructor
}

Translator::~Translator() {
    // destructor
}

std::string Translator::translateEnglishWord(const std::string& word) const {
    std::string translatedWord;
    translatedWord.reserve(word.size() * 3); // worst-case consonant doubling

    for (char c : word) {
        if (model.isVowel(c)) {
            translatedWord += model.translateSingleVowel(c);
        } else {
            translatedWord += model.translateSingleConsonant(c);
        }
    }

    return translatedWord;
}

std::string Translator::translateEnglishSentence(const std::string& sentence) const {
    std::istringstream iss(sentence);
    std::string word;
    std::string translatedSentence;

    while (iss >> word) {
        if (!translatedSentence.empty()) {
            translatedSentence += ' ';
        }
        translatedSentence += translateEnglishWord(word);
    }

    return translatedSentence;
}