//
// Created by william on 2020-10-24.
//

#include "chip8.h"

void chip8::executeOpcode() {
    char instruction[8];

    sprintf(instruction, "%x", opcode);

    switch(instruction[0]) {
        case '0':
            if (instruction[4] == '0') {
                
            }
        case 'a':
            indexRegister = opcode & 0x0FFF;
            programCounter += 2;
    }
}

void chip8::emulateCycle() {
    opcode = memory[programCounter] << 8 | memory[programCounter + 1];

    executeOpcode();
}

void chip8::initialize() {
    programCounter = 0;
}