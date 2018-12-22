#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>

int main(int argc, char* argv[]) {
  if (argc > 1) { std::cout << argv[1] << '\n'; }
  const std::string file_location {argv[1]};
  std::ifstream rom_file {file_location, std::ios::binary};
  if (!rom_file) {
    std::cout << "File wasn't found.\n";
    return -1;
  }
  std::cout << "Printing CHIP-8 file:\n";
  std::vector<std::uint8_t> rom {std::istreambuf_iterator<char>{rom_file}, {}};
  std::cout << std::uppercase << std::hex;
  std::cout.fill('0');
  for (std::size_t idx {0}; idx < rom.size(); idx += 2) {
    std::cout << "0x" << std::setw(4) << (rom[idx] << 8 | rom[idx + 1]);
    std::cout << (idx % 16 == 14? '\n' : '\t');
  }
  std::cout << '\n';
  return 0;
}
