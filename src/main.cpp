#include <iostream>
#include <thread>
#include "config.hpp"
#include "sort.hpp"
#include "efsw/efsw.hpp"

class UpdateListener : public efsw::FileWatchListener {
  public:
    void handleFileAction( efsw::WatchID watchid, const std::string& dir,
                       const std::string& filename, efsw::Action action,
                       const std::string& oldFilename ) override {
      switch ( action ) {
        case efsw::Actions::Add:
          moveFiles();
          break;
        default:
          break;
}
    }
};

int main() {
  int response = createConfig();
  if (response == 1) return 1;

  if (!checkConfigValidity(getConfig())) return 1;

  configData config = getConfig();

  efsw::FileWatcher* fileWatcher = new efsw::FileWatcher();
  UpdateListener* listener = new UpdateListener();
  efsw::WatchID watchID = fileWatcher->addWatch( config.downloadsPath.string(), listener, true );

  fileWatcher->watch();

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  delete fileWatcher;
  delete listener;
  return 0;
}