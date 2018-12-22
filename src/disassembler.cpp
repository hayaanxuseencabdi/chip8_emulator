#include "disassembler.h"

#include <string>
#include <vector>
#include <cstdint>
#include <fstream>
#include <stdexcept>

std::vector<std::uint8_t>* Disassembler::disassemble_code(const std::string& file_loc) {
  std::ifstream rom {file_loc};
  if (!rom) {
    throw std::runtime_error("File could not be found.");
  }
  return new std::vector<std::uint8_t>{std::istreambuf_iterator<char>{rom}, {}};
}
