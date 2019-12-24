#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "loader.h"
#include "tools.h"

//
// Constructor that will read a ROM file and load it into a buffer
// for use by the CPU.
//
Loader::Loader(string const &filename) {
    stringstream errmsg;
    string full_filename;

    // check if file exists
    char *rp = realpath(filename.c_str(), NULL);
    if (rp == NULL) {
        errmsg.clear();
        errmsg << "Invalid ROM file given on CLI: " << filename;
        throw runtime_error(errmsg.str());
    }

    full_filename = rp;
    free(rp);

    if (!exists(full_filename)) {
        errmsg.clear();
        errmsg << "File " << full_filename << " does not exist.";
        throw runtime_error(errmsg.str());
    }

    log(INFO, "Reading ROM file: %s", full_filename.c_str());

    ifstream is(full_filename, ifstream::binary| ios::in);
    if (is) {
        // get the size of the ROM file.
        is.seekg(0, is.end);
        _size = is.tellg();
        is.seekg(0, is.beg);

        // check input file size to make sure it can fit in available memory
        if (_size > 0 && _size > MaxProgramSize) {
            errmsg.clear();
            errmsg << "File size (" << _size << ") too big for available memory ("
                   << MaxProgramSize << ").";
            throw runtime_error(errmsg.str());
        }

        // Read the file into the buffer
        _buffer = new unsigned char [_size];
        is.read((char *)_buffer, _size);
        is.close();
    } else {
        errmsg.clear();
        errmsg << "Error opening file '" << filename << "' for reading";
        throw runtime_error(errmsg.str());
    }
}

//
// Frees the ROM buffer when the CPU is done with the loader
//
Loader::~Loader() {
    delete[] _buffer;
}

//
// Getter for the ROM buffer
//
unsigned char *Loader::buffer(void) {
    return _buffer;
}

//
// Returns the size of the ROM buffer used by the CPU
//
int Loader::size(void) {
    return _size;
}
