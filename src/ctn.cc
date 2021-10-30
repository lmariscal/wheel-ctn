#include "ctn.h"

#include <fstream>
#include <iostream>
#include <algorithm>

namespace act {

  CTN::CTN(const std::string &dictionaryPath, const std::string &wheelsPath) {
    LoadWheels(wheelsPath);
    LoadDictionary(dictionaryPath);
  }

  void CTN::LoadDictionary(const std::string &path) {
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
      std::cerr << "Required file '" << path << "' failed to open...\n";
      return;
    }

    std::string line;
    while (!file.eof()) {
      std::getline(file, line);

      if (line.empty())
        continue;
      if (line.length() > numberOfWheels)
        continue;

      // Let's assume that all dictionaries will be lowercased
      // std::transform(line.begin(), line.end(), line.begin(), [](uchar c){
      //   return std::tolower(c);
      // });

      dictionary.insert(dictionary.end(), line);
    }

    for (auto itr = dictionary.cbegin(); itr != dictionary.cend(); ++itr) {
      for (i32 i = 0; i < (*itr).size() - 1; ++i) {
        branches.insert(branches.end(), (*itr).substr(0, (*itr).size() - i - 1));
      }
    }

    file.close();
  }

  void CTN::LoadWheels(const std::string &path) {
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
      std::cerr << "Required file '" << path << "' failed to open...\n";
      return;
    }

    std::string line;

    std::getline(file, line);
    try {
      numberOfWheels = std::stoi(line);
    } catch (std::invalid_argument e) {
      std::cerr << "Ill formed number of wheels in `" << path << "` file...\n";
      file.close();
      return;
    }

    std::getline(file, line);
    try {
      lettersPerWheel = std::stoi(line);
    } catch (std::invalid_argument e) {
      std::cerr << "Ill formed letters per wheel in `" << path << "` file...\n";
      file.close();
      return;
    }

    while (!file.eof()) {
      std::getline(file, line);

      if (line.empty())
        continue;
      if (line.length() != lettersPerWheel) {
        std::cerr << "Ill formed letters per wheel value, please rectify `" << path << "` is valid...\n";
        continue;
      }

      std::transform(line.begin(), line.end(), line.begin(), [](uchar c){
        return std::tolower(c);
      });
      wheels.push_back(line);
    }

    if (wheels.size() != numberOfWheels)
      std::cerr << "Ill number of wheels, please rectify `" << path << "` is valid...\n";

    file.close();
  }

  void CTN::GetWords(const std::string &along, std::vector<std::string> &words, const i32 index) {
    for (i32 l = 0; l < lettersPerWheel; ++l) {
      std::string newAlong = along;

      newAlong.push_back((u32)wheels.at(index)[l]);

      if (dictionary.count(newAlong))
        words.push_back(newAlong);

      if (index + 1 < numberOfWheels && branches.count(newAlong))
        GetWords(newAlong, words, index + 1);
    }
  }

  void CTN::CalculatePossibleWords() {
    std::vector<std::string> words;
    for (i32 w = 0; w < numberOfWheels; ++w)
      GetWords({ }, words, w);

    for (std::string &w : words) {
      // toupper, so it matches with `output.txt`
      std::transform(w.begin(), w.end(), w.begin(), [](uchar c){
        return std::toupper(c);
      });
      std::cout << w << '\n';
    }

    std::cout << "Found " << words.size() << " words\n";
  }

}
