#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "chip8.h"

chip8 chip8;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
bool quit = false;
SDL_Event e;
SDL_Window* window = NULL;
SDL_Renderer* renderer;

void setupGraphics() {
    SDL_Surface* screenSurface = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        std::cout<<"SDL could not initialize! SDL_Error: %s\n"<<SDL_GetError();
    } else {
        window = SDL_CreateWindow("Sea-Chip", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (window == NULL) {
            std::cout<<"Window could not be created! SDL_Error: %s\n"<<SDL_GetError();
        } else {
            screenSurface = SDL_GetWindowSurface( window );

            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00 ) );

            SDL_UpdateWindowSurface( window );


        }
    }
}

void drawGraphics() {
    SDL_Rect fillRect;
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(renderer);

    for (int i = 0; i < chip8.SCREEN_WIDTH; i++) {
        for (int j = 0; j < chip8.SCREEN_HEIGHT; j++) {
            if (chip8.screen[i][j] == 1) {
                fillRect.x = i*(SCREEN_WIDTH/chip8.SCREEN_WIDTH);
                fillRect.y = j*(SCREEN_HEIGHT/chip8.SCREEN_HEIGHT);
                fillRect.w = SCREEN_WIDTH/chip8.SCREEN_WIDTH;
                fillRect.h = SCREEN_HEIGHT/chip8.SCREEN_HEIGHT;

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
    chip8.drawFlag = false;
}

int main(int, char **) {
    setupGraphics();
    //setupInput();

    chip8.initialize();
    chip8.loadGame("../c8games/INVADERS");

    // Emulation loop
    while( !quit ) {
        while (SDL_PollEvent( &e ) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        chip8.emulateCycle();

        if(chip8.drawFlag) {
            drawGraphics();
        }

        //chip8.setKeys();

        // Set to run at 600hz
        SDL_Delay(10/6);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );

    SDL_Quit();
    return 0;
}
