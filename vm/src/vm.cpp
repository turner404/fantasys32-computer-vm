#pragma once
#include "../includes/vm.h"

#include <stdlib.h>
#include <string.h>

#include <iostream>

void VirtualMachine::loadCode(char* binFile) {
    FILE* bin = fopen(binFile, "rb");             // read the file in binary mode.
    fseek(bin, 0, SEEK_END);                      // go to the end of file.
    int sizeBin = ftell(bin) - sizeof(uint32_t);  // Get the size of code less the first instruction. (instructions size is 4 bytes normally)
    rewind(bin);                                  // Go to begin of file.

    uint32_t beginCode;
    fread(&beginCode, sizeof(uint32_t), 1, bin);  // Read the initial position of the first instruction.
    beginCode = __builtin_bswap32(beginCode);     // Make the swap the bits sequences from Big-Endian to Little-Endian.

    fread(mem, 1, sizeBin, bin);  // Load the rest of code file in the vm memory.
    regs[PC] = beginCode;         // Load the initial position of the first instructions in the VM registers.
}
