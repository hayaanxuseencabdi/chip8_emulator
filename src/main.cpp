#include <iostream>
#include <cstdint>
#include <string>

#include <SDL2/SDL.h>
#include "chip8.h"
#include "cpu.h"

namespace {
void update_screen(CHIP8* chip8, SDL_Renderer* renderer) {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderPresent(renderer);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (int row_idx {0}; row_idx < 32; row_idx += 2) {
    for (int col_idx {0}; col_idx < 32; col_idx += 2) {
      if (chip8->display[row_idx][col_idx]) {
        for (std::uint8_t p_row {0}; p_row < 25; ++p_row) {
          for (std::uint8_t p_col {0}; p_col < 25; ++p_col) {
            SDL_RenderDrawPoint(renderer, col_idx * 25 + p_col,
                                row_idx * 25 + p_row);
          } 
        }
      }
    }
  }
  SDL_RenderPresent(renderer);
}
} // namespace

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Missing filename. (e.g. \"./chip8 <$ROM_PATH>\")\n";
    return 1;
  }
  const std::string file_location {argv[1]};
  CHIP8* chip8 {new CHIP8{file_location}};
  // Window resolution = 1600x800 thus each CHIP8 pixel = a 25x25 quadrant.
  SDL_Window* window {SDL_CreateWindow("CHIP-8 Emulator",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1600, 800, 0)};
  SDL_Renderer* renderer {SDL_CreateRenderer(window, -1, 0)};
  ::update_screen(chip8, renderer);
  /**
   *  TODO: for the main loop, make sure to calculate the number of CPU cycles
   * it should take before you decrement the sound and delay timers again.
   * e.g. if our CPU clock speed is 120 Hz, we should decrement the registers
   * every 2 cycles rather than every cycle @ 60 Hz
   */
  // Handles user input.
  SDL_Event event;
  while (true) {
    if (chip8->needs_redrawing()) {
      ::update_screen(chip8, renderer);
    }
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        delete chip8;
        return 0;
      }
      chip8->clock_cycle();
    }
  }
}
