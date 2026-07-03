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

    { "sort-paths": toml::table{
      { "images": tombl::table{
        {"extensions": toml::array{ ".png", ".jpeg", ".jpg", ".webp"}},
        {"sort-path": "" }
      }},
      { "videos": tombl::table{
        {"extensions": toml::array{ ".mp4", ".gif", ".mov"}},
        {"sort-path": "" }
      }},
      { "music": tombl::table{
        {"extensions": toml::array{ ".mp3", ".wav", ".m3a"}},
        {"sort-path": "" }
      }},
      { "documents": tombl::table{
        {"extensions": toml::array{ ".txt", ".pdf", ".docx"}},
        {"sort-path": "" }
      }}
    }}
  }

  std::ofstream file(getConfigPath / "config.toml");
  if (!file.is_open()) {
    std::cerr << "Failed to open config for writing." << std::endl;
    return 1;
  }

  return 0;
}