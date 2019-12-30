#ifndef CPU_H_
#define CPU_H_

#include <string>
#include <time.h>

#include "display.h"
#include "loader.h"

using namespace std;

class CPU {

public:
    static const int MemSize = 4096;
    static const int StackSize = 16;
    static const int TotalRegisters = 16;

    // The delay timer is 60Hz.  Each cycle the delay register is decremented.
    // ceil((1 sec / 60 cycles) * (1000ms / 1 sec)) = 17 ms/cycle
    static const int TimerTick = 17;

    CPU(Display &display, Loader &loader);
    ~CPU();

    void reset(void);
    void step(void);

private:

    // address contained within the current instruction
    unsigned short int address;

    // reference to the screen where pixels will be written
    Display *display = NULL;

    // The MSB of the instruction
    unsigned char hiByte;

    // The current instruction after a fetch operation
    unsigned short int instruction;

    // The left 4 bits of the instruction
    unsigned char lNibble;

    Loader *loader = NULL;

    // The LSB of the instruction
    unsigned char loByte;

    // System memory, 4K
    unsigned char *m;

    // program counter
    unsigned short int pc;

    // The right 4 bits of the instruction
    unsigned char rNibble;

    // stack pointer index
    unsigned char sp;

    // call return stack
    unsigned short int stack[StackSize];

    // The timer structure for computing elapsed time between ticks
    struct timespec timer;

    // 16 general purpose register, v0 - vF (v0-v15)
    unsigned char v[TotalRegisters];

    // special I register
    unsigned short int vi;

    // special delay register
    unsigned char vDelay;

    // special sound register
    unsigned char vSound;

    // instruction register index x
    unsigned char x;

    // instruction register index y
    unsigned char y;

    void decode(void);
    void execute(void);
    void fetch(void);
    void timerTick(void);
};

#endif
