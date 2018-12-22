#include "chip8.h"

#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>

#include "disassembler.h"

/*
 * Contains the sprites (in ascending order) CHIP-8 programs could refer to.
 * Each sprite is 5 bytes long. They'll be stored from 0x000 onwards up to 0x50
 * in the memory reserved for the CHIP-8 interpreter (0x000 to 0x1FF). 
 * The sprites represent the possible values of a hexadecimal digit, i.e.
 * {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F}.
 */
constexpr std::array<std::uint8_t, 16 * 5> SPRITES {
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

CHIP8::CHIP8(const std::string& file_loc) 
  : opcode {0}, V {std::array<std::uint8_t, 16>{}}, pc {std::uint8_t(0x200)},
    I {0}, mem {std::array<std::uint8_t, 4096>{}}, stack_pointer  {0}, 
    stack {std::array<std::uint16_t, 16>{}}, delay_timer {0}, sound_timer {0} {      
  for (std::size_t idx {0}; idx < 0x50; ++idx) {
    mem[idx] = SPRITES[idx];
  }
  std::vector<std::uint8_t>* rom {Disassembler::disassemble_code(file_loc)};
  if (0x200 + rom->size() > 0xFFF) {
    throw std::invalid_argument(
      "The ROM is too large to be processed by the CHIP-8 interpreter.");
  }
  for (std::size_t op_idx {0}; op_idx < rom->size(); ++op_idx) {
    mem[0x200 + op_idx] = (*rom)[op_idx];
  }
  delete rom;
}
