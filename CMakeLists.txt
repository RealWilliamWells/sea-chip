cmake_minimum_required(VERSION 3.17)
project(sea_chip)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(sea_chip src/main.cpp src/chip8.cpp src/chip8.h)
target_link_libraries(sea_chip ${SDL2_LIBRARIES})

add_executable(test_sea_chip test/chip8Test.cpp test/chip8Test.h src/chip8.cpp src/chip8.h)