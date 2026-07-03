#include <iostream>
#include <filesystem>
#include <fstream>
#include "config.hpp"
#include <toml.hpp>

namespace fs = std::filesystem;

fs::path getConfigPath() {
  fs::path get_config_directory() {
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
    const char* home = std::getenv("HOME") / "Downloads-Sort";
    if (home) {
      return fs::path(home) / ".config";
    }
  #endif
    return fs::current_path() / "Downloads-Sort-Config";
  }
}

int createConfig() {
  if (!fs::exists(getConfigPath() / "config.toml") && fs::is_regular_file(filePath)) {
    fs::create_directory(getConfigPath());
    std::ofstream file(getConfigPath() / "config.toml");

    if (!file.is_open()) {
      std::cerr << "Failed to make file for writing." << std::endl;
      return 1;
    }
  }

  return fillConfig;
}

int fillConfig() {
  toml::table config{
    { "title": "Downloads-Sort Config" },
    { "downloads-path": "" }, 

    { "sort-paths": toml::array{
      tombl::table{
        {"extensions": toml::array{ ".png", ".jpeg", ".jpg", ".webp"}},
        {"sort-path": "" }
      },
      tombl::table{
        {"extensions": toml::array{ ".mp4", ".gif", ".mov"}},
        {"sort-path": "" }
      },
      tombl::table{
        {"extensions": toml::array{ ".mp3", ".wav", ".m3a"}},
        {"sort-path": "" }
      },
      tombl::table{
        {"extensions": toml::array{ ".txt", ".pdf", ".docx"}},
        {"sort-path": "" }
      }
    }}
  };

  std::ofstream file(getConfigPath / "config.toml");
  if (!file.is_open()) {
    std::cerr << "Failed to open config for writing." << std::endl;
    return 1;
  }

  return 0;
}

configData getConfig() {
  toml::table config = toml::parse_file(getConfigPath() / "config.toml");

  configData configInfo;

  configInfo.downloadsPath = config["downloads-path"].value_or("");
  if (toml::array* sortPathArray = config["sort-paths"].as_array()) {
    for (toml::node& node : *sortPathArray) {
      if (toml::table* table = node.as_table()) {
        configInfo.sortPaths.push_back(sortPathTable());
      }
    }
  }

  return configInfo;
}

sortPathData sortPathTable(toml::table* table) {
  sortPathData = sortPathInfo;
  sortPathInfo.sortPath = (*table)["sort-path"].value_or("");

  if (toml::array* extensionArray = (*table)["extensions"].as_array()) {
    for (auto&& node : *extensionArray) {
      std::string extension = node.value_or("" std::string);
      sortPathInfo.extensions.push_back(extension);
    }
  }

  return sortPathInfo;
}