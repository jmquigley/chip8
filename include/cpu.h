#ifndef CPU_H_
#define CPU_H_

#include <string>

using namespace std;

class CPU {

public:
    static const int MemSize = 4096;
    static const int StackSize = 16;
    static const int TotalRegisters = 16;
    static const int VMemHeight = 32;
    static const int VMemWidth = 64;

    CPU();
    ~CPU();

    void load(string const &filename);
    void reset(void);
    void run(void);
    void step(void);

private:

    // address contained within the current instruction
    unsigned short int address;

    // flag to stop the main loop
    bool halting = false;

    // The MSB of the instruction
    unsigned char hiByte;

    // The current instruction after a fetch operation
    unsigned short int instruction;

    // The left 4 bits of the instruction
    unsigned char lNibble;

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

    // 16 general purpose register, v0 - vF (v0-v15)
    unsigned char v[TotalRegisters];

    // special I register
    unsigned short int vi;

    // special delay register
    unsigned char vDelay;

    // Video ram buffer 2D array
    unsigned char vram[VMemWidth][VMemHeight];

    // special sound register
    unsigned char vSound;

    // instruction register index x
    unsigned char x;

    // instruction register index y
    unsigned char y;

    void decode(void);
    void execute(void);
    void fetch(void);
};

#endif
