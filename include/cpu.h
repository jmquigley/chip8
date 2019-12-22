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
    void step(void);

private:

    // System memory, 4K
    unsigned char *m;

    // 16 general purpose register, v0 - vF (v0-v15)
    unsigned char v[TotalRegisters];

    // special I register
    unsigned short int vi;

    // special delay register
    unsigned char vDelay;

    // special sound register
    unsigned char vSound;

    // program counter
    unsigned short int pc;

    // call return stack
    unsigned short int stack[StackSize];

    // stack pointer index
    unsigned char sp;
    unsigned char vram[VMemWidth][VMemHeight];

    void decode(void);
    void execute(void);
    void fetch(void);
};

#endif
