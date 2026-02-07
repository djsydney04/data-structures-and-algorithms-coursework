#ifndef MODEL_H
#define MODEL_H

#include <string>

class Model {
public:
  Model();               // default constructor
  ~Model();              // default destructor

  std::string translateSingleConsonant(char c) const;
  std::string translateSingleVowel(char c) const;

  bool isVowel(char c) const;
  bool isConsonant(char c) const;
};

#endif