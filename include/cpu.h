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
    static const int NoKey = -1;
    static const int StackSize = 16;
    static const int TotalRegisters = 16;

    // The delay timer is 60Hz.  Each cycle the delay register is decremented.
    // ceil((1 sec / 60 cycles) * (1000ms / 1 sec)) = 17 ms/cycle
    static const int TimerTick = 17;

    CPU(Display &display, Loader &loader);
    ~CPU();

    void reset(void);
    void resetKey(void);
    void setKey(int keypress);
    void step(void);

private:

    // address contained within the current instruction
    unsigned short int address;

    // reference to the screen where pixels will be written
    Display *display = NULL;

    // The MSB of the instruction
    unsigned char hiByte;

    // Built in fonts for 0-9, A-F saved in the first 80 bytes of RAM
    unsigned char fonts[16][5] = {
         {0xF0, 0x90, 0x90, 0x90, 0xF0}, // 0
         {0x20, 0x60, 0x20, 0x20, 0x70}, // 1
         {0xF0, 0x10, 0xF0, 0x80, 0xF0}, // 2
         {0xF0, 0x10, 0xF0, 0x10, 0xF0}, // 3
         {0x90, 0x90, 0xF0, 0x10, 0x10}, // 4
         {0xF0, 0x80, 0xF0, 0x10, 0xF0}, // 5
         {0xF0, 0x80, 0xF0, 0x90, 0xF0}, // 6
         {0xF0, 0x10, 0x20, 0x40, 0x40}, // 7
         {0xF0, 0x90, 0xF0, 0x90, 0xF0}, // 8
         {0xF0, 0x90, 0xF0, 0x10, 0xF0}, // 9
         {0xF0, 0x90, 0xF0, 0x90, 0x90}, // A
         {0xE0, 0x90, 0xE0, 0x90, 0xE0}, // B
         {0xF0, 0x80, 0x80, 0x80, 0xF0}, // C
         {0xE0, 0x90, 0x90, 0x90, 0xE0}, // D
         {0xF0, 0x80, 0xF0, 0x80, 0xF0}, // E
         {0xF0, 0x80, 0xF0, 0x80, 0x80}  // F
    };

    // The current instruction after a fetch operation
    unsigned short int instruction;

    // The SDL keypress from the main loop.  -1 means no keypress
    int keypress = NoKey;

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
    short int sp;

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
    void push(unsigned int);
    unsigned int pop();
    void timerTick(void);

    void opCall();
    void opClear();
    void opJump();
    void opReturn();
    void opSkipEqual();
    void opSkipNotEqual();
    void opSysCall();

};

#endif
