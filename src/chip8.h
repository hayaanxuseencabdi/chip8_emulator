#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <cstddef>
#include <array>
#include <vector>
#include <string>

class CHIP8 {
public:
  std::array<std::uint8_t, 16> V; // 16 8-bit data registers
  std::uint16_t pc; // program counter
  std::uint16_t I; // 16-bit index register
  std::array<std::uint8_t, 4096> mem; // 4096 bytes of addressable memory
  std::uint8_t stack_pointer; // 8-bit stack pointer
  std::array<std::uint16_t, 16> stack;
  std::array<std::array<std::uint8_t, 64>, 32> display; // 64x32 pixel display
  std::uint8_t delay_timer;
  std::uint8_t sound_timer;
  bool redraw;

public:
  CHIP8(const std::string& file_loc);
  ~CHIP8();
  static std::vector<std::uint8_t>* read_program(const std::string& file_loc);
  void clock_cycle();
};

#endif // CHIP8_H
