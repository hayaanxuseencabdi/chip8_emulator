#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "chip8.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Missing filename. (e.g. \"./chip8 <$ROM_PATH>\")\n";
    return 1;
  }
  const std::string file_location {argv[1]};
  CHIP8 chip8 {file_location};
  // Window resolution = 1600x800 thus each CHIP8 pixel = a 25x25 quadrant.
  SDL_Window* window {SDL_CreateWindow("CHIP-8 Emulator",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1600, 800, 0)};
  if (!window) {
    std::cout << "Could not create window: " << SDL_GetError() << '\n';
    return 2;
  }
  SDL_Surface* screen_surface {SDL_GetWindowSurface(window)};
  SDL_Surface* corner {SDL_CreateRGBSurfaceFrom(0, 25, 25, 32, 0, 0, 0, 0, 0)};
  SDL_FillRect(screen_surface, nullptr,
               SDL_MapRGB(screen_surface->format, 255, 255, 255));
  SDL_UpdateWindowSurface(window);
  SDL_Delay(5000);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
