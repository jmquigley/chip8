#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <string>

using namespace std;

// log function level codes
#define ERROR             0x01
#define WARNING           0x08
#define DEBUG             0x04
#define INFO              0x02
#define SUCCESS           0x00

// general temporary buffer sizing
#ifndef BUFSIZE
#define BUFSIZE           1024
#endif

// time buffer sizing
#ifndef TM_BUFSIZE
#define TM_BUFSIZE        50
#endif

bool exists(string const &filename);
void log(unsigned int level, const char *msg, ...);

#endif
