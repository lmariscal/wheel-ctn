#include "types.h"
#include "utils.h"
#include "ctn.h"

#include <iostream>
#include <string>
#include <filesystem>

using namespace act;

void PrintHelp() {
  std::cout << "\n\
CTN Programming Test\n\
\
Usage:\n\
\n\
  wheel-ctn <path_to_wheels> <path_to_dictionary>\n\
    Loads `wheels.txt` and `dictionary.txt` from the provided path.\n\
\n\
  wheel-ctn default\n\
    Loads `wheels.txt` and `dictionary.txt` from the `res` directory, these are the\n\
    values provided with the instructions.\n";
}

i32 main(i32 argSize, char **args) {
  if (argSize <= 1) {
    PrintHelp();
    return 0;
  }

  std::string firstArg = std::string(args[1]);
  if (argSize == 2 && firstArg != "default") {
    PrintHelp();
    return -1;
  }

  std::filesystem::path wheelsPath(DataDir() + "res/wheels.txt");
  std::filesystem::path dictionaryPath(DataDir() + "res/dictionary.txt");
  if (argSize > 2) {
    wheelsPath = std::filesystem::path(firstArg);
    dictionaryPath = std::filesystem::path(args[2]);
  }

  if (!std::filesystem::exists(wheelsPath)) {
    std::cerr << "Required file '" << wheelsPath.string() << "' does not exists...\n";
    return -1;
  }
  if (!std::filesystem::exists(dictionaryPath)) {
    std::cerr << "Required file '" << dictionaryPath.string() << "' does not exists...\n";
    return -1;
  }

  CTN ctn(dictionaryPath.string(), wheelsPath.string());
  ctn.CalculatePossibleWords();
}
