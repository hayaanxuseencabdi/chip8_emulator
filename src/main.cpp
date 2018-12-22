#include <iostream>
#include <string>

#include "chip8.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Missing filename. (e.g. \"./chip8 <$ROM_PATH>\")\n";
    return -1;
  }
  const std::string file_location {argv[1]};
  CHIP8 chip8 {file_location};
  return 0;
}
