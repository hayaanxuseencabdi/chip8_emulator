#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <vector>
#include <cstdint>
#include <string>

class Disassembler {
public:
  static std::vector<std::uint8_t> disassemble_code(const std::string& file_loc);
};

#endif // DISASSEMBLER_H
