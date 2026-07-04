#include <iostream>
#include <filesystem>
#include <vector>
#include <thread>
#include <chrono>
#include "sort.hpp"
#include "config.hpp"

namespace fs = std::filesystem;

std::vector<fs::path> getDownloads() {
  configData config = getConfig();
  fs::path downloadsPath = config.downloadsPath;

  std::vector<fs::path> files;

  if (fs::exists(downloadsPath) && fs::is_directory(downloadsPath)) {
    for (const auto& file : fs::directory_iterator(downloadsPath)) {
      if (fs::is_regular_file(file.status())) {
        files.push_back(file.path());
      }
    }
    return files;
  }

  std::cerr << '\"' << downloadsPath << "\" either does not exist or is not a folder";
  return files;
}

fs::path findSortPath(fs::path filePath) {
  configData config = getConfig();
  std::vector<sortPathData> sortPathInfo = config.sortPaths;

  std::string fileExtension = filePath.extension().string();

  for (sortPathData sortPathItem : sortPathInfo) {
    for (std::string extension : sortPathItem.extensions) {
      if (extension == fileExtension) return sortPathItem.sortPath;
    }
  }

  return config.downloadsPath;
}

bool isFileReady(const fs::path& path) {
  try {
    if (!fs::exists(path)) return false;

    uintmax_t size1 = fs::file_size(path);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    uintmax_t size2 = fs::file_size(path);

    if (size1 != size2) return false;

    return true;
  } catch (...) {
    return false;
  }
}

int moveFiles() {
  configData config = getConfig();

  std::vector<fs::path> downloads = getDownloads();

  for (fs::path download : downloads) {
    fs::path sortPath = findSortPath(download);
    if (sortPath == config.downloadsPath) continue;

    int attempts = 0;
    while (!isFileReady(download) && attempts < 20) { 
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      attempts += 1;
    }

    try {
      fs::rename((config.downloadsPath / download.filename()), (sortPath / download.filename()));
    } catch (const fs::filesystem_error& e) {
      std::cerr << "Error moving file: " << e.what() << "\n";
    }
  }

  return 0;
}