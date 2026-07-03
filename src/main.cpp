#include <iostream>
#include "config.hpp"

int main() {
  int response = createConfig();
  if (response == 1) return 1;

  if (!checkConfigValidity(getConfig())) return 1;
  
  return 0;
}