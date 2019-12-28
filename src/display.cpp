//
// A class that handles all interactions with the display using SDL2
//

#include <cstring>
#include <SDL.h>
#include <sstream>
#include <string>

#include "display.h"
#include "tools.h"

using namespace std;

// Standard color constants
const unsigned int Display::BLACK = color(0, 0, 0);
const unsigned int Display::WHITE = color(255, 255, 255);


Display::Display(unsigned int background, unsigned int foreground, unsigned int scale) {
    stringstream errmsg;
    unsigned int rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    log(DEBUG, "Initializing video memory");

    this->background = background;
    this->foreground = foreground;
    this->scale = scale >= 1 ? scale : 1;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("chip8",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              this->width(), this->height(), 0);
    if (!window) {
        errmsg << "Error creating main display window: " << SDL_GetError();
        throw runtime_error(errmsg.str());
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        errmsg << "Error creating display renderer" << SDL_GetError();
        throw runtime_error(errmsg.str());
    }

    // This allows the surface to be the size of the chip 8 display (64x32) while the window can
    // be larger by the scale value.  This will automatically scale the surface to the window.
    SDL_RenderSetLogicalSize(renderer, VMemWidth, VMemHeight);

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                VMemWidth,
                                VMemHeight);
    if (!texture) {
        errmsg << "Error creating texture" << SDL_GetError();
        throw runtime_error(errmsg.str());
    }

    vram = SDL_CreateRGBSurface(0, VMemWidth, VMemHeight, 32, rmask, gmask, bmask, amask);
    if (!vram) {
        errmsg << "Error creating VRAM surface: " << SDL_GetError();
        throw runtime_error(errmsg.str());
    }

    clear();
}

Display::~Display() {
    SDL_FreeSurface(vram);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//
// Clears the current screen with the background color
//
void Display::clear() {
    unsigned int *pixels = (unsigned int *)vram->pixels;

    memset32(pixels, background, VMemWidth * VMemHeight);
    dirty = true;
}

unsigned int Display::height() {
    return VMemHeight * scale;
}

//
// Plots a single pixel to the display surface based on the foreground color
//
// (1) x is the column
// (2) y is the row
//
void Display::pixel(unsigned int x, unsigned int y) {
    int offset = (y * VMemWidth) + x;

    *((unsigned int *)vram->pixels + offset) = foreground;
    dirty = true;
}

//
// Updates the current display by taking the current surface and updating the
// main texture.  The display is only updated when the dirty flag is set by
// a pixel operation, so the display will not be updated on each tick, but
// only when something actually writes to teh screen.
//
void Display::update() {
    stringstream errmsg;

    if (dirty) {
        if (SDL_UpdateTexture(texture, NULL, vram->pixels, vram->pitch)) {
            errmsg << "Can't update texture: " << SDL_GetError();
            throw runtime_error(errmsg.str());
        }

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        dirty = false;
    }
}

unsigned int Display::width() {
    return VMemWidth * scale;
}
