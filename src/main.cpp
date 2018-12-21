#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

int main(int argc, char* argv[]) {
  const std::string file_location {"/home/hxyxxn/projects/chip8/roms/pong.ch8"};
  std::ifstream rom_file {file_location, std::ios::binary};
  if (!rom_file) {
    std::cout << "File wasn't found.\n";
    return -1;
  }
  std::cout << "Printing CHIP-8 file:\n";
  std::vector<std::uint8_t> rom {std::istreambuf_iterator<char>{rom_file}, {}};
  std::cout << std::uppercase << std::hex;
  for (std::size_t idx {0}; idx < rom.size(); idx += 2) {
    std::cout << (rom[idx] << 8 | rom[idx + 1]);
    std::cout << (idx != rom.size() - 1 ? ' ' : '\n');
  }
  std::cout << '\n';
  return 0;
}
