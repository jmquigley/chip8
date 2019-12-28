#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <SDL.h>

#include "tools.h"

class Display {

public:
    static const unsigned int VMemHeight = 32;
    static const unsigned int VMemWidth = 64;

    static const unsigned int BLACK;
    static const unsigned int WHITE;

    Display(unsigned int background = BLACK, unsigned int foreground = WHITE, unsigned int scale = 10);
    ~Display();

    void clear();
    unsigned int height();
    void pixel(unsigned int x, unsigned int y);
    void update();
    unsigned int width();

private:

    // background color and clear
    unsigned int background;

    // if the display texture has been updated, then set this to true
    bool dirty = true;

    // foreground color for each pixel plotted on the display
    unsigned int foreground;

    SDL_Renderer *renderer;

    // scaling factor for video memory
    unsigned int scale = 10;

    // This texture is drawn to the window
    SDL_Texture *texture = NULL;

    // Video ram buffer represented by an SDL surface
    SDL_Surface *vram = NULL;

    // A reference to the main window of the app
    SDL_Window *window = NULL;

};

#endif
