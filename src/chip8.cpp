#include "chip8.h"

#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <ios>

#include <SDL2/SDL.h>
#include "cpu.h"

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

std::unordered_map<std::int32_t, std::uint8_t> CHIP8::KEYPAD {
  {SDLK_1, 0x0}, {SDLK_2, 0x1}, {SDLK_3, 0x2}, {SDLK_4, 0x3},
  {SDLK_q, 0x4}, {SDLK_w, 0x5}, {SDLK_e, 0x6}, {SDLK_r, 0x7},
  {SDLK_a, 0x8}, {SDLK_s, 0x9}, {SDLK_d, 0xA}, {SDLK_f, 0xB},
  {SDLK_z, 0xC}, {SDLK_x, 0xD}, {SDLK_c, 0xE}, {SDLK_v, 0xF}
};

std::vector<std::uint8_t>* CHIP8::read_program(const std::string& file_loc) {
  std::ifstream rom {file_loc, std::ios::binary};
  if (!rom) {
    throw std::runtime_error("File could not be found.");
  }
  return new std::vector<std::uint8_t>{std::istreambuf_iterator<char>{rom}, {}};
}

CHIP8::CHIP8(const std::string& file_loc) 
  : V {std::array<std::uint8_t, 16>{}}, pc {0x200}, I {0},
    mem {std::array<std::uint8_t, 4096>{}}, stack_pointer {0},
    stack {std::array<std::uint16_t, 16>{}},
    display {std::array<std::array<std::uint8_t, 64>, 32>{}},
    // FIXME: set timers to 60 or 0 at start?
    delay_timer {60}, sound_timer {60}, redraw {false} {
  // Load the fontset into the reserved memory.
  for (std::size_t idx {0}; idx < 0x50; ++idx) {
    mem[idx] = SPRITES[idx];
  }
  // Fetch the instructions from the ROM.
  std::vector<std::uint8_t>* rom {CHIP8::read_program(file_loc)};
  if (0x200 + rom->size() > 0xFFF) {
    throw std::invalid_argument(
      "The ROM is too large for the CHIP-8 interpreter.");
  }
  // Load the program into memory.
  for (std::size_t op_idx {0}; op_idx < rom->size(); ++op_idx) {
    mem[0x200 + op_idx] = (*rom)[op_idx];
  }
  delete rom;
  // Seed the random number generator.
  std::srand(std::time(nullptr));
}

CHIP8::~CHIP8() = default;

void CHIP8::clock_cycle() {
  const std::uint16_t& opcode {(V[pc] << 8) | V[pc + 1]};
  pc += 2;
  switch (opcode & 0xF000) {
    // TODO: implement switch statement for the current operation
    default:
      std::cerr << "Unknown operation: " << std::hex << std::uppercase
                << opcode << '\n';
      break;
  }
}

bool CHIP8::needs_redrawing() {
  if (redraw) {
    redraw = false;
    return true;
  }
  return false;
}
