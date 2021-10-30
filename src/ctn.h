#pragma once

#include "types.h"

#include <set>
#include <vector>
#include <string>

namespace act {

  class CTN {
   public:
    CTN(const std::string &dictionaryPath, const std::string &wheelsPath);

    void CalculatePossibleWords();

   protected:
    void LoadDictionary(const std::string &path);
    void LoadWheels(const std::string &path);
    void GetWordsThreaded(std::vector<std::string> &words);

    void GetWords(const std::string &along, std::vector<std::string> &words, const i32 index);

    i32 lettersPerWheel = 0;
    i32 numberOfWheels  = 0;
    std::vector<std::string> wheels;
    std::set<std::string> dictionary;
    std::set<std::string> branches;
  };

}
