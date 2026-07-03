#include <iostream>
#include "config.hpp"
#include "sort.hpp"

int main() {
  int response = createConfig();
  if (response == 1) return 1;

  if (!checkConfigValidity(getConfig())) return 1;
  
  response = moveFiles();
  if (response == 1) return 1;

  return 0;
}