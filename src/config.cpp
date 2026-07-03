#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include "config.hpp"
#include <toml.hpp>

namespace fs = std::filesystem;

fs::path getConfigPath() {
  #if defined(_WIN32)
    const char* appdata = std::getenv("APPDATA");
    if (appdata) {
      return fs::path(appdata) / "Downloads-Sort";
    }
  #elif defined(__APPLE__)
    const char* home = std::getenv("HOME");
    if (home) {
      return fs::path(home) / "Library" / "Application Support" / "Downloads-Sort";
    }
  #elif defined(__linux__)
    const char* home = std::getenv("HOME");
    if (home) {
      return fs::path(home) / ".config" / "Downloads-Sort";
    }
  #endif
    std::cout << "Unable to find config folder. Making config file in current directory";
    return fs::current_path() / "Downloads-Sort-Config";
}

int fillConfig() {
  toml::table config{
    { "title", "Downloads-Sort Config" },
    { "downloads-path", "" }, 

    { "sort-paths", toml::array{
      toml::table{
        {"extensions", toml::array{ ".png", ".jpeg", ".jpg", ".webp" }},
        {"sort-path", "" }
      },
      toml::table{
        {"extensions", toml::array{ ".mp4", ".gif", ".mov" }},
        {"sort-path", "" }
      },
      toml::table{
        {"extensions", toml::array{ ".mp3", ".wav", ".m3a" }},
        {"sort-path", "" }
      },
      toml::table{
        {"extensions", toml::array{ ".txt", ".pdf", ".docx" }},
        {"sort-path", "" }
      }
    }}
  };

  std::ofstream file(getConfigPath() / "config.toml");
  if (!file.is_open()) {
    std::cerr << "Failed to open config for writing." << std::endl;
    return 1;
  }

  file << config;

  return 0;
}

int createConfig() {
  if (!fs::exists(getConfigPath())) {
    if (!fs::create_directories(getConfigPath())) {
      std::cerr << "Failed to create config directory: " << getConfigPath() << std::endl;
      return 1;
    }
  }

  if (!fs::exists(getConfigPath() / "config.toml")) {
      return fillConfig();
  }

  return 0;
}

sortPathData sortPathTable(toml::table* table) {
  sortPathData sortPathInfo;
  sortPathInfo.sortPath = (*table)["sort-path"].value_or("");

  if (toml::array* extensionArray = (*table)["extensions"].as_array()) {
    for (auto&& node : *extensionArray) {
      std::string extension = node.value_or("");
      sortPathInfo.extensions.push_back(extension);
    }
  }

  return sortPathInfo;
}

configData getConfig() {
  toml::table config = toml::parse_file((getConfigPath() / "config.toml").string());

  configData configInfo;

  configInfo.downloadsPath = config["downloads-path"].value_or("");
  if (toml::array* sortPathArray = config["sort-paths"].as_array()) {
    for (toml::node& node : *sortPathArray) {
      if (toml::table* table = node.as_table()) {
        configInfo.sortPaths.push_back(sortPathTable(table));
      }
    }
  }

  return configInfo;
}

bool checkConfigValidity(configData config) {
  bool configValid = true;

  if (config.downloadsPath == "") {
    std::cerr << "Missing downloads path in config." << std::endl;
    configValid = false;
  }

  std::vector<sortPathData> sortPathsInfo = config.sortPaths;
  int missingExtensionCount = 0;
  int missingPathCount = 0;

  for (sortPathData sortPathInfo : sortPathsInfo) {
    if (sortPathInfo.extensions.size() == 0) missingExtensionCount += 1;
    if (sortPathInfo.sortPath == "") missingPathCount += 1;
  }

  if (missingExtensionCount > 0) std::cerr << missingExtensionCount << " blank lists for extensions." << std::endl;
  if (missingPathCount > 0) std::cerr << missingPathCount << " empty sort paths." << std::endl;

  return configValid;
}