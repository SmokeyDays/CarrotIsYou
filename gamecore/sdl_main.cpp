//
//  tutorial.cpp
//  SDLTest
//
//  Created by 闂鼎閭?on 2023/10/16.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <queue>
#include <mutex>
#include <thread>
#include "CarrotOS.h"
#undef main

std::queue<int> keyq;
std::mutex qmtx;
SDL_Texture *texture;
SDL_Renderer *renderer;
// game has a 16 * 16 blocks
// each block contains 8 * 8 chunks
// each chunk takes up 4 bits.
unsigned int sdlDisplayMemory[16 * 16 * 8];
const int maxx = 767;
const int maxy = 1023;

void sdlSetDisplayMemory(int x, int yBlock, unsigned int val) {
    sdlDisplayMemory[x * 16 + yBlock] = val;
}

char getDisplayMemory(int x, int y) {
    unsigned int d = sdlDisplayMemory[x * 16 + y / 8];
    char ret = (d >> ((y % 8) * 4)) & 0xF;
    return ret;
}

unsigned colors[16] = {0x000000FF, 0xFFFFFFFF, 0x313131FF, 0x969696FF, 0xFF1414FF, 0xF7CC18FF, 0x6EBED5FF, 0x1477ACFF, 
  0x57BB83FF, 0xEE378BFF, 0xFA8361FF, 0x2F1A0FFF, 0x60483CFF, 0xA47F2CFF, 0xFA8361FF, 0xFAD4B5FF};

int getColorId(int x, int y) {
    x /= 6;
    y /= 6;
    return getDisplayMemory(x, y);

}

void octopus() {
    CarrotOS *os = new CarrotOS();
    os->run();
}

bool keyEmpty() {
    qmtx.lock();
    bool ret = keyq.empty();
    qmtx.unlock();
    return ret;
}

int keyPop() {
    qmtx.lock();
    int ret = keyq.front();
    keyq.pop();
    qmtx.unlock();
    return ret;
}



void updateScreen(SDL_Texture *texture) {
    int *pixels = new int[1024 * 768];
    for(int x = 0; x < maxx; x++) {
        for(int y = 0; y < maxy; y ++) {
            if(y < 128 || y >= 896) {
                // pixels[x * 1024 + y] = colors[0];
                pixels[x * 1024 + y] = 0x222222FF;
                continue;
            }
            int id = getColorId(x, y - 128);
            pixels[x * 1024 + y] = colors[id];
        }
    }
    
    if(-1 == SDL_UpdateTexture(texture, nullptr, pixels, 1024 * 4)) {
        printf("update texture error: %s\n", SDL_GetError());
        exit(-1);
    }
    
    delete []pixels;
}

void sdlUpdate() {
    updateScreen(texture);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

int main() {
    
    SDL_Event event;
    int quit = 0;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Init error: %s\n", SDL_GetError());
        exit(-1);
    }
    
    SDL_Window *window = SDL_CreateWindow("Carrot is you.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(nullptr == renderer) {
        printf("render error: %s\n", SDL_GetError());
        return -1;
    }
    
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
    
    std::thread t(octopus);
    t.detach();
//    sdlUpdate();
    while(!quit) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                   printf("key %s down\n", SDL_GetKeyName(event.key.keysym.sym));
                   printf("id = %X\n", event.key.keysym.sym);
                    qmtx.lock();
                    keyq.push(event.key.keysym.sym);
                    qmtx.unlock();
                    break;
                case SDL_KEYUP:
//                    printf("key %s up\n", SDL_GetKeyName(event.key.keysym.sym));
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
                default:
                    break;
            }
            
        }
    }
    
}