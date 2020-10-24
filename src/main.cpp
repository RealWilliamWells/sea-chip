#include <iostream>
#include "chip8.h"

chip8 chip8;

int main() {
    //setupGraphics();
    //setupInput();

    chip8.initialize();
    chip8.loadGame("pong");

    // Emulation loop
    for(;;)
    {
        chip8.emulateCycle();

        if(chip8.drawFlag)
            //drawGraphics();

        chip8.setKeys();
    }

    return 0;
}