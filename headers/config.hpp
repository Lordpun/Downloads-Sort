#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

struct sortPathData {
  std::vector<std::string> extensions;
  fs::path sortPath;
};

struct configData {
  fs::path downloadsPath;
  std::vector<sortPathData> sortPaths;
};

int createConfig();

configData getConfig();

bool checkConfigValidity(configData config);

#endif