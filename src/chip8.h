//
// Created by william on 2020-10-24.
//

#ifndef SEA_CHIP_CHIP8_H
#define SEA_CHIP_CHIP8_H

#include <string>

class chip8 {
public:
    unsigned short opcode;
    unsigned char memory[4096];
    unsigned char V[16];

    unsigned short indexRegister;
    unsigned short programCounter;

    bool screen[64 * 32];

    unsigned char delayTimer;
    unsigned char soundTimer;

    unsigned short stack[16];
    unsigned short stackPointer;

    unsigned char keypad[16];

    bool drawFlag;

    void loadGame(std::string rom) {}

    void emulateCycle();

    void initialize();

    void setKeys() {}

    void executeOpcode();
};


#endif //SEA_CHIP_CHIP8_H
