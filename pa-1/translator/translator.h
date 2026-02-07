#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "model.h"
#include <string>

class Translator {
public:
    Translator();
    ~Translator();

    std::string translateEnglishWord(const std::string& word) const;
    std::string translateEnglishSentence(const std::string& sentence) const;

private:
    Model model;
};

#endif