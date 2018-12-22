#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <cstddef>
#include <array>
#include <string>

#include "disassembler.h"

class CHIP8 {
public:
  std::uint16_t opcode;
  std::array<std::uint8_t, 16> V; // 16 8-bit data registers
  std::uint16_t pc; // program counter
  std::uint16_t I; // 16-bit index register
  std::array<std::uint8_t, 4096> mem; // 4096 bytes of addressable memory
  std::uint8_t stack_pointer; // 8-bit stack pointer
  std::array<std::uint16_t, 16> stack;
  std::uint8_t delay_timer;
  std::uint8_t sound_timer;

public:
  CHIP8(const std::string& file_loc);
  ~CHIP8();
  void clock_cycle();
};

#endif // CHIP8_H
