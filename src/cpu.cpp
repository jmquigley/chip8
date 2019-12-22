#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include "cpu.h"
#include "tools.h"

using namespace std;

CPU::CPU() {
    m = new unsigned char [CPU::MemSize];
    reset();
}

CPU::~CPU() {
    delete[] m;
}

void CPU::fetch(void) {
}

void CPU::decode(void) {
}

void CPU::execute(void) {
}

//
// Loads a c8 rom image into the CPU memory.
//
void CPU::load(string const &filename) {
    stringstream errmsg;
    string full_filename;

    // check if file exists
    char *rp = realpath(filename.c_str(), NULL);
    if (rp == NULL) {
        errmsg.clear();
        errmsg << "Invalid input rome file: " << filename;
        throw runtime_error(errmsg.str());
    }

    full_filename = rp;
    free(rp);

    if (!exists(full_filename)) {
        errmsg.clear();
        errmsg << "File " << full_filename << " does not exist";
        throw runtime_error(errmsg.str());
    }

    log(INFO, "Loading input file: %s", full_filename.c_str());

    // open file for binary, check size

    // if size can fit in memory, read the file and load it

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
    memset(vram, 0, sizeof(vram[0][0]) * VMemHeight * VMemWidth);
}

//
// Performs the fetch, decode, execute for the current instruction and then increments
// the program counter to the next instruction
//
void CPU::step(void) {
    log(INFO, "Step to next instruction");

    fetch();
    decode();
    execute();

    pc += 2;
}
