#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

class VirtualMachine {
   private:
    uint32_t readInstructionFromRegister(uint32_t index);

   public:
    const int32_t SP = 14;
    const int32_t PC = 15;

    /*
     * Registers:
     * Each register has 4 byte.
     * regs[0] -> R0, regs[1] -> R1, regs[2] -> R2, etc...
     * The last register (regs[15]) has the address of the next instruction.
     * It's our PC.
     */
    int32_t regs[16];

    /*
     * The memory that is load the binary program (our games).
     * A game must have max size of 16MB.
     */
    uint8_t* mem;

    VirtualMachine();
    ~VirtualMachine();
    void loadCode(const char* binFile);
    void executeInstruction();
};