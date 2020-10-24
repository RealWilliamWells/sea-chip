cmake_minimum_required(VERSION 3.17)
project(sea_chip)

set(CMAKE_CXX_STANDARD 14)

add_executable(sea_chip src/main.cpp src/chip8.cpp src/chip8.h)

add_executable(test_sea_chip test/chip8Test.cpp test/chip8Test.h src/chip8.cpp src/chip8.h)