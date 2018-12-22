#include "disassembler.h"

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>

std::vector<std::uint8_t> Disassembler::disassemble_code(const std::string& file_loc) {
  std::ifstream fin {file_loc};
  std::vector<std::uint8_t> instructions {std::istreambuf_iterator<char>{fin}, {}};
  return instructions;
}
