#include <iostream>
#include <filesystem>
#include <vector>
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

int moveFiles() {
  std::vector<fs::path> downloads = getDownloads();
  std::cout<< "Downloads: " << downloads.size() << std::endl;

  for (fs::path download : downloads) {
    std::cout << "Download path: " << download << std::endl;
    std::cout << "Found path: " << findSortPath(download) << std::endl;
  }

  return 0;
}