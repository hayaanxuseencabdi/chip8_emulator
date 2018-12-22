#include "cpu.h"

#include <cstddef>
#include <cstdint>

#include "chip8.h"

/**
 *  0NNN      Execute machine language subroutine at address NNN
 */
void CPU::op_0NNN(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: forgo implementation for now
}

/**
 *  00E0      Clear the screen
 */
void CPU::op_00E0(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: forgo implementation for now
}

/**
 *   00EE     Return from a subroutine
 */
void CPU::op_00EE(CHIP8& chip8, const std::uint16_t& opcode) {
  chip8.pc = chip8.stack[chip8.stack_pointer];
  --chip8.stack_pointer;
}

/**
 *   1NNN     Jump to address NNN
 */
void CPU::op_1NNN(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint16_t NNN {opcode & 0x0FFF};
  chip8.pc = NNN;
}

/**
 *   2NNN     Execute subroutine starting at address NNN
 */
void CPU::op_2NNN(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint16_t NNN {opcode & 0x0FFF};
  chip8.stack[chip8.stack_pointer] = chip8.pc;
  ++chip8.stack_pointer;
  chip8.pc = NNN;
}

/**
 *   3XNN     Skip the following instruction if the value of register VX
 *            equals NN
 */
void CPU::op_3XNN(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  const std::uint8_t NN {opcode & 0x00FF};
  chip8.pc = chip8.V[X] == NN ? chip8.pc + 2 : chip8.pc;
}

/**
 *  4XNN      Skip the following instruction if the value of register VX is not
 *            equal to NN
 */
void CPU::op_4XNN(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  const std::uint8_t NN {opcode & 0x00FF};
  chip8.pc = chip8.V[X] != NN ? chip8.pc + 2 : chip8.pc;
}

/**
 *  5XY0      Skip the following instruction if the value of register VX is equal
 *            to the value of register VY
 */
void CPU::op_5XY0(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  const std::uint8_t Y {opcode & 0x00F0};
  chip8.pc = (chip8.V[X] == chip8.V[Y]) ? chip8.pc + 2 : chip8.pc;
}

/**
 *   6XNN     Store number NN in register VX
 */
void CPU::op_6XNN(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  const std::uint8_t NN {opcode & 0x00FF};
  chip8.V[X] = NN;
}

/**
 *   7XNN     Add the value NN to register VX
 */
void CPU::op_7XNN(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  const std::uint8_t NN {opcode & 0x00FF};
  chip8.V[X] += NN;
}

/**
 *   8XY0     Store the value of register VY in register VX
 */
void CPU::op_8XY0(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  const std::uint8_t Y {opcode & 0x00F0};
  chip8.V[X] = chip8.V[Y];
}

/**
 *   8XY1     Set VX to VX OR VY
 */
void CPU::op_8XY1(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  const std::uint8_t Y {opcode & 0x00F0};
  chip8.V[X] |= chip8.V[Y];
}

/**
 *   8XY2     Set VX to VX AND VY
 */
void CPU::op_8XY2(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  const std::uint8_t Y {opcode & 0x00F0};
  chip8.V[X] &= chip8.V[Y];
}

/**
 *   8XY3     Set VX to VX XOR VY
 */
void CPU::op_8XY3(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  const std::uint8_t Y {opcode & 0x00F0};
  chip8.V[X] ^= chip8.V[Y];
}

/**
 *  8XY4      Add the value of register VY to register VX
 *            Set VF to 01 if a carry occurs
 *            Set VF to 00 if a carry does not occur
 */
void CPU::op_8XY4(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: implement. figure out whether they mean carry/borrow from overflow/underflow
}

/**
 *  8XY5      Subtract the value of register VY from register VX
 *            Set VF to 00 if a borrow occurs
 *            Set VF to 01 if a borrow does not occur
 */
void CPU::op_8XY5(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: implement. figure out whether they mean carry/borrow from overflow/underflow
}

/**
 *  8XY6      Store the value of register VY shifted right one bit in register VX
 *            Set register VF to the least significant bit prior to the shift
 */
void CPU::op_8XY6(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: implement
}

/**
 *  8XY7      Set register VX to the value of VY minus VX
 *            Set VF to 00 if a borrow occurs
 *            Set VF to 01 if a borrow does not occur
 */
void CPU::op_8XY7(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: implement
}

/**
 *  8XYE      Store the value of register VY shifted left one bit in register VX
 *            Set register VF to the most significant bit prior to the shift
 */
void CPU::op_8XYE(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: implement
}

/**
 *  9XY0      Skip the following instruction if the value of register VX is not
 *            equal to the value of register VY
 */
void CPU::op_9XY0(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: implement
}

/**
 *   ANNN     Store memory address NNN in register I
 */
void CPU::op_ANNN(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint16_t NNN {opcode & 0x0FFF};
  // FIXME: double check whether it's just the address or the value @ mem[NNN]
  chip8.I = NNN;
}

/**
 *   BNNN     Jump to address NNN + V0
 */
void CPU::op_BNNN(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint16_t NNN {opcode & 0x0FFF};
  chip8.pc = NNN + chip8.V[0];
}

/**
 *   CXNN     Set VX to a random number with a mask of NN
 */
void CPU::op_CXNN(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: seed a RNG
}

/**
 *  DXYN      Draw a sprite at position VX, VY with N bytes of sprite data
 *            starting at the address stored in I
 *            Set VF to 01 if any set pixels are changed to unset, and 00 otherwise
 */
void CPU::op_DXYN(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: look into this more
}

/**
 *  EX9E      Skip the following instruction if the key corresponding to the
 *            hex value currently stored in register VX is pressed
 */
void CPU::op_EX9E(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: set up key input
}

/**
 *  EXA1      Skip the following instruction if the key corresponding to the
 *            hex value currently stored in register VX is not pressed
 */
void CPU::op_EXA1(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: set up key input
}

/**
 *   FX07     Store the current value of the delay timer in register VX
 */
void CPU::op_FX07(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  chip8.V[X] = chip8.delay_timer;
}

/**
 *   FX0A     Wait for a keypress and store the result in register VX
 */
void CPU::op_FX0A(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: implement
}

/**
 *   FX15     Set the delay timer to the value of register VX
 */
void CPU::op_FX15(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  chip8.delay_timer = chip8.V[X];
}

/**
 *   FX18     Set the sound timer to the value of register VX
 */
void CPU::op_FX18(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  chip8.sound_timer = chip8.V[X];
}

/**
 *   FX1E     Add the value stored in register VX to register I
 */
void CPU::op_FX1E(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  chip8.I += chip8.V[X];
}

/**
 *  FX29      Set I to the memory address of the sprite data corresponding to
 *            the hexadecimal digit stored in register VX
 */
void CPU::op_FX29(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  chip8.I = 5 * chip8.V[X];
}

/**
 *  FX33      Store the binary-coded decimal equivalent of the value stored in
 *            register VX at addresses I, I+1, and I+2
 */
void CPU::op_FX33(CHIP8& chip8, const std::uint16_t& opcode) {
  // FIXME: ???
}

/**
 *  FX55      Store the values of registers V0 to VX inclusive in memory starting
 *            I is set to I + X + 1 after operation
 *            at address I
 */
void CPU::op_FX55(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  for (std::size_t idx {0x000}; idx <= X; ++idx) {
    chip8.mem[chip8.I + idx] = chip8.V[idx];
  }
  chip8.I += X + 1;
}

/**
 *  FX65      Fill registers V0 to VX inclusive with the values stored in memory
 *            starting at address I
 *            I is set to I + X + 1 after operation
 */
void CPU::op_FX65(CHIP8& chip8, const std::uint16_t& opcode) {
  const std::uint8_t X {opcode & 0x0F00};
  for (std::size_t idx {0x000}; idx <= X; ++idx) {
    chip8.V[idx] = chip8.mem[chip8.I + idx];
  }
  chip8.I += X + 1;
}
