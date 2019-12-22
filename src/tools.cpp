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
