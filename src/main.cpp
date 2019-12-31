#include <iostream>
#include <SDL.h>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>
#include <string>

#include "cpu.h"
#include "loader.h"
#include "tools.h"

using namespace std;

int main(int argc, char **argv) {
    stringstream errmsg;
    const unsigned char *keyboardState = NULL;

    try {
        if (argc != 2) {
            cout << "usage: " << argv[0] << " {rom file}" << endl;
            errmsg.clear();
            errmsg << "Invalid number of parameters: " << argc;
            throw runtime_error(errmsg.str());
        }

        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

        Display display;
        Loader loader(argv[1]);
        CPU cpu(display, loader);

        bool done = false;
        SDL_Event event;

        while (!done) {
            SDL_PollEvent(&event);

            switch (event.type) {

                case SDL_KEYUP:
                    cpu.resetKey();
                    break;

                case SDL_QUIT:
                    done = true;
                    break;
            }

            keyboardState = SDL_GetKeyboardState(NULL);
            if (keyboardState[SDL_SCANCODE_1]) cpu.setKey(0x01);
            else if (keyboardState[SDL_SCANCODE_2]) cpu.setKey(0x02);
            else if (keyboardState[SDL_SCANCODE_3]) cpu.setKey(0x03);
            else if (keyboardState[SDL_SCANCODE_4]) cpu.setKey(0x0C);
            else if (keyboardState[SDL_SCANCODE_Q]) cpu.setKey(0x04);
            else if (keyboardState[SDL_SCANCODE_W]) cpu.setKey(0x05);
            else if (keyboardState[SDL_SCANCODE_E]) cpu.setKey(0x06);
            else if (keyboardState[SDL_SCANCODE_R]) cpu.setKey(0x0D);
            else if (keyboardState[SDL_SCANCODE_A]) cpu.setKey(0x07);
            else if (keyboardState[SDL_SCANCODE_S]) cpu.setKey(0x08);
            else if (keyboardState[SDL_SCANCODE_D]) cpu.setKey(0x09);
            else if (keyboardState[SDL_SCANCODE_F]) cpu.setKey(0x0E);
            else if (keyboardState[SDL_SCANCODE_Z]) cpu.setKey(0x0A);
            else if (keyboardState[SDL_SCANCODE_X]) cpu.setKey(0x00);
            else if (keyboardState[SDL_SCANCODE_C]) cpu.setKey(0x0B);
            else if (keyboardState[SDL_SCANCODE_V]) cpu.setKey(0x0F);

            display.pixel(rand() % 64, rand() % 32);
            display.update();

            cpu.step();
        }

    } catch(exception &e) {
        log(ERROR, "%s", e.what());
        return 127;
    }

    return 0;
}
