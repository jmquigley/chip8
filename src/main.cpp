#include <iostream>
#include <SDL.h>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <string>

#include "cpu.h"
#include "tools.h"

using namespace std;

int main(int argc, char **argv) {
    stringstream errmsg;

    try {
        if (argc != 2) {
            cout << "usage: " << argv[0] << " {rom file}" << endl;
            errmsg.clear();
            errmsg << "Invalid number of parameters: " << argc;
            throw runtime_error(errmsg.str());
        }

        bool quit = false;
        SDL_Event event;
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window *window = SDL_CreateWindow("chip8",
                                              SDL_WINDOWPOS_UNDEFINED,
                                              SDL_WINDOWPOS_UNDEFINED,
                                              640, 320, 0);

        CPU cpu;
        cpu.load(argv[1]);

        cpu.step();
        cpu.step();
        cpu.step();
        cpu.step();

        while (!quit) {
            SDL_PollEvent(&event);

            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        SDL_DestroyWindow(window);
        SDL_Quit();

    } catch(exception &e) {
        log(ERROR, "%s", e.what());
        return 127;
    }

    return 0;
}
