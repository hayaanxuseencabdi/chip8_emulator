#ifndef CPU_H
#define CPU_H

#include <cstdint>

#include <SDL2/SDL.h>

#include "chip8.h"

class CPU {
public:
  // 0NNN     Execute machine language subroutine at address NNN
  static void op_0NNN(CHIP8* chip8, const std::uint16_t& opcode);

  // 00E0     Clear the screen
  static void op_00E0(CHIP8* chip);

  // 00EE     Return from a subroutine
  static void op_00EE(CHIP8* chip);

  // 1NNN     Jump to address NNN
  static void op_1NNN(CHIP8* chip8, const std::uint16_t& opcode);

  // 2NNN     Execute subroutine starting at address NNN
  static void op_2NNN(CHIP8* chip8, const std::uint16_t& opcode);

  // 3XNN     Skip the following instruction if the value of register VX equals NN
  static void op_3XNN(CHIP8* chip8, const std::uint16_t& opcode);

  // 4XNN     Skip the following instruction if the value of register VX is not
  //          equal to NN
  static void op_4XNN(CHIP8* chip8, const std::uint16_t& opcode);

  // 5XY0     Skip the following instruction if the value of register VX is equal
  //          to the value of register VY
  static void op_5XY0(CHIP8* chip8, const std::uint16_t& opcode);

  // 6XNN     Store number NN in register VX
  static void op_6XNN(CHIP8* chip8, const std::uint16_t& opcode);

  // 7XNN     Add the value NN to register VX
  static void op_7XNN(CHIP8* chip8, const std::uint16_t& opcode);

  // 8XY0     Store the value of register VY in register VX
  static void op_8XY0(CHIP8* chip8, const std::uint16_t& opcode);

  // 8XY1     Set VX to VX OR VY
  static void op_8XY1(CHIP8* chip8, const std::uint16_t& opcode);

  // 8XY2     Set VX to VX AND VY
  static void op_8XY2(CHIP8* chip8, const std::uint16_t& opcode);

  // 8XY3     Set VX to VX XOR VY
  static void op_8XY3(CHIP8* chip8, const std::uint16_t& opcode);

  // 8XY4     Add the value of register VY to register VX
  //          Set VF to 01 if a carry occurs
  //          Set VF to 00 if a carry does not occur
  static void op_8XY4(CHIP8* chip8, const std::uint16_t& opcode);

  // 8XY5     Subtract the value of register VY from register VX
  //          Set VF to 00 if a borrow occurs
  //          Set VF to 01 if a borrow does not occur
  static void op_8XY5(CHIP8* chip8, const std::uint16_t& opcode);

  // 8XY6     Store the value of register VY shifted right one bit in register VX
  //          Set register VF to the least significant bit prior to the shift
  static void op_8XY6(CHIP8* chip8, const std::uint16_t& opcode);

  // 8XY7     Set register VX to the value of VY minus VX
  //          Set VF to 00 if a borrow occurs
  //          Set VF to 01 if a borrow does not occur
  static void op_8XY7(CHIP8* chip8, const std::uint16_t& opcode);

  // 8XYE     Store the value of register VY shifted left one bit in register VX
  //          Set register VF to the most significant bit prior to the shift
  static void op_8XYE(CHIP8* chip8, const std::uint16_t& opcode);

  // 9XY0     Skip the following instruction if the value of register VX is not
  //          equal to the value of register VY
  static void op_9XY0(CHIP8* chip8, const std::uint16_t& opcode);

  // ANNN     Store memory address NNN in register I
  static void op_ANNN(CHIP8* chip8, const std::uint16_t& opcode);

  // BNNN     Jump to address NNN + V0
  static void op_BNNN(CHIP8* chip8, const std::uint16_t& opcode);

  // CXNN     Set VX to a random number with a mask of NN
  static void op_CXNN(CHIP8* chip8, const std::uint16_t& opcode);

  // DXYN     Draw a sprite at position VX, VY with N bytes of sprite data
  //          starting at the address stored in I
  //          Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
  static void op_DXYN(CHIP8* chip8, const std::uint16_t& opcode);

  // EX9E     Skip the following instruction if the key corresponding to the
  //          hex value currently stored in register VX is pressed
  static void op_EX9E(CHIP8* chip8, const std::uint16_t& opcode, SDL_Event event);

  // EXA1     Skip the following instruction if the key corresponding to the
  //          hex value currently stored in register VX is not pressed
  static void op_EXA1(CHIP8* chip8, const std::uint16_t& opcode, SDL_Event event);

  // FX07     Store the current value of the delay timer in register VX
  static void op_FX07(CHIP8* chip8, const std::uint16_t& opcode);

  // FX0A     Wait for a keypress and store the result in register VX
  static void op_FX0A(CHIP8* chip8, const std::uint16_t& opcode, SDL_Event event);

  // FX15     Set the delay timer to the value of register VX
  static void op_FX15(CHIP8* chip8, const std::uint16_t& opcode);

  // FX18     Set the sound timer to the value of register VX
  static void op_FX18(CHIP8* chip8, const std::uint16_t& opcode);

  // FX1E     Add the value stored in register VX to register I
  static void op_FX1E(CHIP8* chip8, const std::uint16_t& opcode);

  // FX29     Set I to the memory address of the sprite data corresponding to the
  //          hexadecimal digit stored in register VX
  static void op_FX29(CHIP8* chip8, const std::uint16_t& opcode);

  // FX33     Store the binary-coded decimal equivalent of the value stored in
  //          register VX at addresses I, I+1, and I+2
  static void op_FX33(CHIP8* chip8, const std::uint16_t& opcode);

  // FX55     Store the values of registers V0 to VX inclusive in memory starting
  //          at address I
  //          I is set to I + X + 1 after operation
  static void op_FX55(CHIP8* chip8, const std::uint16_t& opcode);

  // FX65     Fill registers V0 to VX inclusive with the values stored in memory
  //          starting at address I
  //          I is set to I + X + 1 after operation
  static void op_FX65(CHIP8* chip8, const std::uint16_t& opcode);
};

#endif // CPU_H
