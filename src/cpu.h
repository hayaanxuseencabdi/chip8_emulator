#ifndef CPU_H
#define CPU_H

#include <array>
#include <cstdint>

class CPU {
public:
  std::uint16_t opcode;
  std::array<std::uint8_t, 16> V; // 16 8-bit data registers
  std::uint8_t pc; // program counter
  std::uint16_t I; // 16-bit index register
  std::array<std::uint8_t, 4096> mem; // 4096 bytes of addressable memory
  std::uint8_t stack_pointer; // 8-bit stack pointer
  std::array<std::uint16_t, 16> stack;
  std::uint8_t delay_timer;
  std::uint8_t sound_timer;

public:
  CPU();
  ~CPU();
  void clock_cycle();
};

#endif // CPU_H
