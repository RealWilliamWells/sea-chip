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

    static const int screenLength = 64;
    static const int screenHeight = 32;
    bool screen[screenLength][screenHeight];

    unsigned char delayTimer;
    unsigned char soundTimer;

    unsigned short stack[16];
    unsigned short stackPointer;

    unsigned char keypad[16];

    unsigned char fontSet[80];

    bool drawFlag;

    void loadGame(const char *rom);

    void emulateCycle();

    void initialize();

    void setKeys() {}

    void decodeAndExecuteOpcode();

    void clearDisplay();
};


#endif //SEA_CHIP_CHIP8_H
