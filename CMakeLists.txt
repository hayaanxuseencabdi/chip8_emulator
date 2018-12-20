cmake_minimum_required(VERSION 3.11.2)

project(chip8)

set(SDL2_DIR lib/SDL2/lib/cmake/SDL2)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS}/..)

add_subdirectory(src)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(
  -Wall -Wextra -Wpedantic -Weffc++ -Wshadow
)

add_executable(chip8 ${SOURCE_FILES})
target_link_libraries(chip8 ${SDL2_LIBRARIES})
