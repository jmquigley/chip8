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

    try {
        if (argc != 2) {
            cout << "usage: " << argv[0] << " {rom file}" << endl;
            errmsg.clear();
            errmsg << "Invalid number of parameters: " << argc;
            throw runtime_error(errmsg.str());
        }

        Display display;
        Loader loader(argv[1]);
        CPU cpu(display, loader);

        bool done = false;
        SDL_Event event;

        cpu.step();
        cpu.step();
        cpu.step();
        cpu.step();

        while (!done) {
            SDL_PollEvent(&event);

            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
            }

            display.pixel(0, 0);
            display.pixel(63, 31);

            display.update();
        }

    } catch(exception &e) {
        log(ERROR, "%s", e.what());
        return 127;
    }

    return 0;
}
