#include <cstring>
#include <stdlib.h>
#include <string>

#include "cpu.h"
#include "loader.h"
#include "tools.h"

using namespace std;

CPU::CPU(Display &display, Loader &loader) {
    m = new unsigned char [CPU::MemSize];
    this->display = &display;
    this->loader = &loader;

    reset();
}

CPU::~CPU() {
    delete[] m;
}

//
// Retrieves the instruction from memory based on the current PC
//
void CPU::fetch(void) {
    // Each instruction in chip8 is in big-endian.  x86 memory is little endian, so the program
    // must swap the MSB and LSB bytes (and turn it into little endian)
    hiByte = *(m+this->pc);
    instruction =  hiByte << 8;  // store the first byte into instruction MSB
    loByte = *(m+this->pc + 1);
    instruction |= loByte;  // store the second byte into instruction LSB
    log(DEBUG, "Instruction: 0x%04x", instruction);
}

//
// Takes the instruction and breaks it up into constiutent parts.  Not all parts are meaningful
// for every instruction.
//
void CPU::decode(void) {

    // the left 4 bits of the instruction using bitmask
    lNibble = (instruction & 0xF000) >> 12;

    // the right 4 bits of the instruction using bitmask
    rNibble = instruction & 0x000F;

    // instruction address
    address = instruction & 0x0FFF;

    // the x register index
    x = (instruction & 0x0F00) >> 8;

    // the y register index
    y = (instruction & 0x00F0) >> 4;

    log(DEBUG, "lNibble: %d, rNibble: %d, address: %d, x: %d, y: %d", lNibble, rNibble, address, x, y);
}

void CPU::execute(void) {

    switch(lNibble) {
        case 0:
            if (instruction == 0xE0) {
                opClear();
            } else if (instruction == 0xEE) {
                opReturn();
            } else {
                opSysCall();
            }
            break;

        case 1:
            opJump();
            break;

        case 2:
            opCall();
            break;

        case 3:
            opSkipEqual();
            break;

        case 4:
            opSkipNotEqual();
            break;
    }
}

//
// Adds an address to the call stack
//
void CPU::push(unsigned int addr) {
    stack[++sp] = addr;
}

//
// Removes an address from the top of the call stack
//
unsigned int CPU::pop() {
    unsigned int addr = stack[sp--];
    return(addr);
}

//
// Resets the internals for the CPU.
//
void CPU::reset() {
    clock_gettime(CLOCK_MONOTONIC_RAW, &timer);
    memset(m, 0, sizeof(unsigned char) * CPU::MemSize);
    memset(v, 0, sizeof(v[0]) * CPU::TotalRegisters);
    this->vi = 0;
    this->vDelay = 0;
    this->vSound = 0;
    this->pc = 0x200;
    memset(stack, 0, sizeof(stack[0]) * CPU::StackSize);
    this->sp = -1;
    this->address = 0;
    this->hiByte = 0;
    this->loByte = 0;
    this->rNibble = 0;
    this->lNibble = 0;
    this->x = 0;
    this->y = 0;
    this->keypress = -1;

    // Load the fonts to the system area
    memcpy(m, fonts, sizeof(fonts));

    // Load the program into the CPU memory
    memcpy(m+this->pc, loader->buffer(), loader->size());
}

//
// When a key is no longer pressed this function is used to reset the internal
// key settings to NoKey(-1)
//
void CPU::resetKey(void) {
    if (this->keypress != NoKey) {
        setKey(NoKey);
    }
}

//
// Sets the internal flag for a key (pseudo interrupt)
//
void CPU::setKey(int keypress) {
    this->keypress = keypress;
}

//
// Performs the fetch, decode, execute for the current instruction and then increments
// the program counter to the next instruction
//
void CPU::step(void) {
    timerTick();

    fetch();
    decode();
    execute();
}

//
// Called each step through the code to compute the elapsed time between calls.  It uses
// this to decrement the delay register (only if it's greater than 0).  It uses the constant
// 17 ms / tick to determine each tick.
//
void CPU::timerTick() {
    div_t decrementDelay;
    unsigned long int elapsed;
    struct timespec newTimer;
    bool reset = false;

    clock_gettime(CLOCK_MONOTONIC_RAW, &newTimer);

    // The number of milliseconds between calls to this routine
    // clock gives nanosecond difference, so convert to milliseconds
    elapsed = 1000.0 * (newTimer.tv_sec - timer.tv_sec) +
        (double)(newTimer.tv_nsec - timer.tv_nsec) / 1.0e+6;

    if (elapsed > TimerTick) {
        decrementDelay = div(elapsed, TimerTick);

        if (vDelay > 0) {
            if (decrementDelay.quot > vDelay) {
                vDelay = 0;
            } else {
                vDelay -= decrementDelay.quot;
            }

            reset = true;
        }

        if (vSound > 0) {
            if (decrementDelay.quot > vSound) {
                vSound = 0;
            } else {
                vSound -= decrementDelay.quot;
            }

            reset = true;
        }

        if (reset) {
            timer = newTimer;
        }
    } else {
        timer = newTimer;
    }
}


void CPU::opCall() {
    push(pc);
    pc = address;
}

void CPU::opClear() {
    display->clear();
    pc += 2;
}

void CPU::opJump() {
    pc = address;
}

void CPU::opReturn() {
    pc = pop();
}

void CPU::opSkipEqual() {
    unsigned char r = v[x];

    if (loByte == r) {
        pc += 2;
    }

    pc += 2;
}

void CPU::opSkipNotEqual() {
    unsigned char r = v[x];

    if (loByte != r) {
        pc += 2;
    }

    pc += 2;
}

void CPU::opSysCall() {
    push(address);
    pc = address;
}
