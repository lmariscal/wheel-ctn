#include "utils.h"

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include <algorithm>

namespace act {

std::string DataDir() {
  char resultChar[512];
  for (i32 i = 0; i < 512; ++i)
    resultChar[i] = '\0';

#if defined(WIN32) || defined(_WIN32)
  GetModuleFileName(nullptr, resultChar, MAX_PATH);
#elif defined(__linux__)
  ssize_t count = readlink("/proc/self/exe", resultChar, 512);
#else
  std::cerr << "Unsupported OS for DistPath\n";
#endif

  std::string result = std::string(resultChar);
  std::replace(result.begin(), result.end(), '\\', '/');
  std::string::size_type pos = std::string(result).rfind("dist/");
  result                     = result.substr(0, pos + 5);

  return result;
}

}
