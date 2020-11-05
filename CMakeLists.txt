cmake_minimum_required(VERSION 3.17)
project(sea_chip)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(sea_chip chip8/main.cpp chip8/chip8.cpp chip8/chip8.h)
target_link_libraries(sea_chip ${SDL2_LIBRARIES})

add_executable(test_sea_chip test/chip8Test.cpp chip8/chip8.cpp chip8/chip8.h)