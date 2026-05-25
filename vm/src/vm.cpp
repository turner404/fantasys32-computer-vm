#include "../includes/vm.h"

VirtualMachine::VirtualMachine() {
    uint size = (uint)16 * (uint)1024 * (uint)1024;  // setting 16MB to our mem size. The casts is for avoid the compiler warning.
    mem = new uint8_t[size];
    memset(mem, 0, sizeof(uint8_t) * size);
    memset(regs, 0, sizeof(int32_t) * 16);
}

void VirtualMachine::loadCode(const char* binFile) {
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

uint32_t VirtualMachine::readInstructionFromRegister(uint32_t index) {
    uint32_t data = (mem[index] << 24);
    data |= (mem[index + 1] << 16);
    data |= (mem[index + 2] << 8);
    data |= (mem[index + 3]);

    return data;
}

void VirtualMachine::executeInstruction() {
    uint32_t instr = readInstructionFromRegister(regs[PC]);
    uint32_t opcode = instr >> 26;

    // TODO -> diferents types...
    // Decoding instruction type of I
    uint32_t i_rs = (instr >> 22) & 0xF;
    uint32_t i_rt = (instr >> 18) & 0xF;
    uint32_t i_imm18 = instr & 0x3FFFF;

    // Next instruction
    regs[PC] += 4;

    switch (opcode) {
        case 0x0D:  // MOVL
            regs[i_rt] = i_imm18 & 0x3FFFF;
            break;
        default:
            printf("Instrução não implementada: 0x%08X (opcode 0x%08X)\n", instr, opcode);
            exit(1);
    }
}
