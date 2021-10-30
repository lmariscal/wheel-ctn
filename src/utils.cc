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
#if defined(WIN32) || defined(_WIN32)
  char result_char[512];
  GetModuleFileName(nullptr, result_char, MAX_PATH);
#elif defined(__linux__)
  char result_char[512];
  ssize_t count = readlink("/proc/self/exe", result_char, 512);
#else
  std::cerr << "Unsupported OS for DistPath\n";
#endif

  std::string result = std::string(result_char);
  std::replace(result.begin(), result.end(), '\\', '/');
  std::string::size_type pos = std::string(result).rfind("dist/");
  result                     = result.substr(0, pos + 5);

  return result;
}

}
