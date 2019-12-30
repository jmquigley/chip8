#include <cstdarg>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "tools.h"

using namespace std;

//
// Convenience method for creating a 32 bit color value in the format
// RGBA (Red/Green/Blue/Alpha).  This sets alpha to 255 by default.
//
unsigned int color(unsigned int r, unsigned int g, unsigned int b) {
    return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + 0xFF;
}

//
// Takes an input file by name and checks if it exists.
// returns true if the file is found, otherwise false.
//
bool exists(string const &filename) {
    struct stat buffer;
    return stat(filename.c_str(), &buffer) == 0;
}

//
// Prints a logging message to the terminal.  Works with four modes:
//
// - INFO
// - ERROR
// - DEBUG
// - INFO
//
void log(unsigned int level, const char *msg, ...) {

    // set DEBUG env variable to "true" to print debugging messages
    if (level == DEBUG && getenv("DEBUG") == NULL) {
        return;
    }

    va_list args;
    va_start(args, msg);

    stringstream fmt;
    const char *level_str;
    time_t timer;
    struct tm *tm_info;
    char tmbuf[TM_BUFSIZE];
    char tmp[BUFSIZE];

    time(&timer);
    tm_info = localtime(&timer);

    switch(level) {
        case ERROR: level_str = "ERROR"; break;
        case WARNING: level_str = "WARN "; break;
        case DEBUG: level_str = "DEBUG"; break;
        case INFO:
        default:
            level_str = "INFO ";
    }

    strftime(tmbuf, TM_BUFSIZE, "%Y-%m-%d@%H:%M:%S", tm_info);
    fmt << "[" << level_str << "] " << tmbuf << " ~> " << msg;
    vsprintf(tmp, fmt.str().c_str(), args);

    if (level == ERROR) {
        cerr << tmp << endl;
    } else {
        cout << tmp << endl;
    }

    va_end(args);
}

//
// The standard memset only handles single byte values.  This is a variant that will
// handle 4 byte word memset values.
// (1) the pointer to the memory to set
// (2) the int value to set for each word
// (3) the number of words contained in the memory region specified by #1
//
void memset32(void *ptr, int value, int size) {
    for (int i = 0; i<size; i++) {
        *((unsigned int *)ptr + i) = value;
    }
}
