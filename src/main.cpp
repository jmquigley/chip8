#include <iostream>
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

        CPU cpu;

        cpu.load(argv[1]);
        cpu.step();
    } catch(exception &e) {
        log(ERROR, "%s", e.what());
        return 127;
    }

    return 0;
}
