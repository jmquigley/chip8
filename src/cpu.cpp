#include <cstring>
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

    // Load the program into the CPU memory
    memcpy(m+this->pc, loader.buffer(), loader.size());
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
    pc += 2;
}

//
// Resets the internals for the CPU.
//
void CPU::reset() {
    memset(m, 0, sizeof(unsigned char) * CPU::MemSize);
    memset(v, 0, sizeof(v[0]) * CPU::TotalRegisters);
    this->vi = 0;
    this->vDelay = 0;
    this->vSound = 0;
    this->pc = 0x200;
    memset(stack, 0, sizeof(stack[0]) * CPU::StackSize);
    this->sp = 0;
}

//
// Infinite run loop for the CPU.
//
void CPU::run() {
    while (!halting) {
        step();
    }
}

//
// Performs the fetch, decode, execute for the current instruction and then increments
// the program counter to the next instruction
//
void CPU::step(void) {
    log(DEBUG, "Step to next instruction");

    fetch();
    decode();
    execute();
}
