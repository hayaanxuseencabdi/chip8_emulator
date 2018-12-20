#ifndef CPU_H
#define CPU_H

#include <array>
#include <cstdint>

class CPU {
public:
  /**
   * 16 8-bit data registers:
   * {V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB, VC, VD, VE, VF}
   * VF is generally reserved since it acts as a flag for certain operations.
   */
  std::array<std::uint8_t, 16> V {};
  std::uint16_t opcode;
  std::array<std::uint8_t, 4096> mem {}; // 4096 bytes of addressable memory
  std::uint8_t pc {0}; // program counter
  std::uint8_t stack_pointer {0}; // 8-bit stack pointer
  std::array<std::uint16_t, 16> stack {};
  std::uint8_t delay_timer;
  std::uint8_t sound_timer;

public:
  CPU() = default;
  ~CPU() = default;
};

#endif // CPU_H
