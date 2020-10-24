//
// Created by william on 2020-10-24.
//

#include <iostream>
#include "chip8Test.h"
#include "../src/chip8.h"

chip8 chip8;

bool testChip8Opcodes() {
    chip8.programCounter = 0;
    chip8.memory[chip8.programCounter] = 0xA2;
    chip8.memory[chip8.programCounter + 1] = 0xF0;

    chip8.emulateCycle();

    return chip8.indexRegister == 0x2F0;
}

int main() {
    chip8.initialize();

    if (!testChip8Opcodes()) {
        std::cout<<"Got unexpected result from opcode test: "<<chip8.indexRegister;
    }

    return 0;
}