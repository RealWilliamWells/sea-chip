//
// Created by william on 2020-10-24.
//

#include "chip8.h"

void chip8::clearDisplay() {
    for (int i = 0; i<screenHeight; i++) {
        for (int j = 0; j<screenLength; j++) {
            screen[i][j] = false;
        }
    }
}

void chip8::decodeAndExecuteOpcode() {
    char instruction[8];
    int x = (opcode >> 8) & 0x0F;
    int y = (opcode >> 4) & 0x0F;

    unsigned short nn = opcode & 0xFF;
    unsigned short nnn = opcode & 0x0FFF;

    sprintf(instruction, "%x", opcode);

    switch(instruction[0]) {
        case '0':
            if (instruction[3] == '0') {
                clearDisplay();
                programCounter += 2;
            } else if (instruction[3] == 'e') {
                programCounter = stack[stackPointer];
                stackPointer--;
            } else {
                // TODO: Call machine code routine
            }
            break;

        case '1':
            programCounter = opcode & 0x0FFF;
            break;

        case '2':
            stack[stackPointer] = programCounter;
            stackPointer++;
            programCounter = opcode & 0x0FFF;
            break;

        case '3':
            if (V[x] == nn) {
                programCounter += 2;
            }
            break;

        case '4':
            if (V[x] != nn) {
                programCounter += 2;
            }
            break;

        case '5':
            if (V[x] == V[y]) {
                programCounter += 2;
            }
            break;

        case '6':
            V[x] = nn;
            programCounter += 2;
            break;

        case '7':
            V[x] += nn;
            programCounter += 2;
            break;

        case '8':
            switch(instruction[3]) {
                case '0':
                    V[x] = V[y];
                    programCounter += 2;
                    break;

                case '1':
                    V[x] = V[x]|V[y];
                    programCounter += 2;
                    break;

                case '2':
                    V[x] = V[x]&V[y];
                    programCounter += 2;
                    break;

                case '3':
                    V[x] = V[x]^V[y];
                    programCounter += 2;
                    break;

                case '4':
                    if(V[x] > (0xFF - V[y])) {
                        V[0xF] = 1;
                    } else {
                        V[0xF] = 0;
                    }
                    V[x] += V[y];
                    programCounter += 2;
                    break;

                case '5':
                    if(V[x] < V[y]) {
                        V[0xF] = 0;
                    } else {
                        V[0xF] = 1;
                    }
                    V[x] -= V[y];
                    programCounter += 2;
                    break;

                case '6':
                    V[0xF] = V[x] & 1;
                    V[x]>>=1;
                    programCounter += 2;
                    break;

                case '7':
                    if(V[x] > V[y]) {
                        V[0xF] = 0;
                    } else {
                        V[0xF] = 1;
                    }
                    V[x] = V[y]-V[x];
                    programCounter += 2;
                    break;

                case 'e':
                    V[0xF] = V[x] & 1;
                    V[x]<<=1;
                    programCounter += 2;
                    break;

                default:
                    // TODO: Throw exception
                    break;
            }
            break;

        case '9':
            if (V[x] != V[y]) {
                programCounter += 2;
            }
            break;

        case 'a':
            indexRegister = nnn;
            programCounter += 2;
            break;

        case 'b':
            programCounter = V[0] + nnn;
            break;

        case 'c':
            V[x]=(rand() % 256) & nn;
            programCounter += 2;
            break;

        case 'd': {
            unsigned short height = opcode & 0x000F;
            unsigned short pixel;

            V[0xF] = 0;
            for (int yLine = 0; yLine < height; yLine++) {
                pixel = memory[indexRegister + yLine];
                for (int xLine = 0; xLine < 8; xLine++) {
                    if ((pixel & (0x80 >> xLine)) != 0) {
                        if (screen[x + xLine][y + yLine] == 1) {
                            V[0xF] = 1;
                        }
                        screen[x + xLine][y + yLine] ^= 1;
                    }
                }
            }

            drawFlag = true;
            programCounter += 2;
        }
        break;

        case 'e':
            if (instruction[3] == 'e') {
                // TODO: Implement keyboard controls
//                if (keyPressed() == V[x]) {
//                    programCounter += 2;
//                }
            } else {
                // TODO: Implement keyboard controls
//                if (keyPressed() != V[x]) {
//                    programCounter += 2;
//                }
            }
            break;

        case 'f':
            switch (instruction[3]) {
                case '5':
                    switch (instruction[2]) {
                        case '1':
                            delayTimer = V[x];
                            programCounter += 2;
                            break;

                        case '5':
                            for (int i = 0; i<=x; i++) {
                                memory[indexRegister + (i+1)] = V[i];
                            }
                            programCounter += 2;
                            break;

                        case '6':
                            for (int i = 0; i<=x; i++) {
                                V[i] = memory[indexRegister + (i+1)];
                            }
                            programCounter += 2;
                            break;

                        default:
                            // TODO: Throw Exception
                            break;
                    }
                    break;

                case '8':
                    soundTimer = V[x];
                    programCounter += 2;
                    break;

                case 'e':
                    indexRegister += V[x];
                    programCounter += 2;
                    break;

                case '9':
                    // TODO: Will very likely need to be changed
                    indexRegister += fontSet[V[x]];
                    programCounter += 2;
                    break;

                case '3':
                    memory[indexRegister] = V[x] / 100;
                    memory[indexRegister + 1] = (V[x] / 10) % 10;
                    memory[indexRegister + 2] = (V[x] % 100) % 10;
                    programCounter += 2;
                    break;
            }
            break;

        default:
            // TODO: Throw Exception
            break;
    }
}

void chip8::emulateCycle() {
    opcode = memory[programCounter] << 8 | memory[programCounter + 1];

    decodeAndExecuteOpcode();

    if (delayTimer > 0) {
        delayTimer--;
    }

    if (soundTimer > 0) {
        if (soundTimer == 1) {
            // TODO: Beep Sound!
        }
        soundTimer--;
    }
}

void chip8::initialize() {
    programCounter = 0x200;
    opcode = 0;
    indexRegister = 0;
    stackPointer = 0;

    // Load font set
    for (int i = 0; i < 80; i++) {
        memory[i] = fontSet[i];
    }
}

void chip8::loadGame(const char *rom) {
    FILE * file;
    file = fopen (rom,"rb");
    fseek (file , 0 , SEEK_END);
    long bufferSize = ftell (file);
    rewind (file);
    char * buffer = (char*) malloc (sizeof(char)*bufferSize);

    if (buffer!=NULL)
    {
        for (int i = 0; i < bufferSize; ++i) {
            memory[i + 512] = buffer[i];
        }
    } else {
        // TODO: Throw exception
    }

    fclose (file);
}