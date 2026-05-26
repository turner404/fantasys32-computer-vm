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

uint32_t VirtualMachine::readInstructionFromRegister(uint32_t reg) {
    uint32_t data = (mem[reg] << 24);
    data |= (mem[reg + 1] << 16);
    data |= (mem[reg + 2] << 8);
    data |= (mem[reg + 3]);

    return data;
}

void VirtualMachine::executeInstruction() {
    uint32_t instr = readInstructionFromRegister(regs[PC]);
    uint32_t opcode = instr >> 26;

    uint32_t i_rs;
    uint32_t i_rt;
    uint32_t i_imm18;

    uint32_t i_ra;
    uint32_t i_rb;
    uint32_t i_rc;
    uint32_t i_rd;
    uint32_t i_re;

    uint32_t addr26;

    if (opcode >= ADD && opcode <= ROR) {  // Type R
        i_rs = (instr >> 22) & 0xF;
        i_rt = (instr >> 18) & 0xF;
        i_rd = (instr >> 14) & 0xF;
    }
    if (opcode >= ADDI && opcode <= BGE) {  // Type I
        i_rs = (instr >> 22) & 0xF;
        i_rt = (instr >> 18) & 0xF;
        i_imm18 = instr & 0x3FFFF;
    }
    if (opcode == JMP || opcode == CALL) {  // Type J
        addr26 = instr & 0x3FFFFFF;
    }
    if (opcode >= PUSH && opcode <= RET) {  // Type U
        i_rd = (instr >> 22) & 0xF;
    }
    if (opcode >= RECT && opcode <= HALT) {  // Type S
        i_ra = (instr >> 22) & 0xF;
        i_rb = (instr >> 18) & 0xF;
        i_rc = (instr >> 14) & 0xF;
        i_rd = (instr >> 10) & 0xF;
        i_re = (instr >> 6) & 0xF;
    }

    // Next instruction
    regs[PC] += 4;

    switch (opcode) {
        case ADD:
            regs[i_rd] = regs[i_rs] + regs[i_rt];
            break;
        case MOVL:
            regs[i_rt] = i_imm18 & 0xFFFF;
            break;
        case MOVH:
            regs[i_rt] = regs[i_rt] | (i_imm18 << 16);
            break;
        // TODO others intructions
        case CLEAR:
            printf("Limpa a tela. (instr: 0x%08X, opcode 0x%08X)\n", instr, opcode);
            break;
        case RECT:
            printf("Cria um Rect. (instr: 0x%08X, opcode 0x%08X)\n", instr, opcode);
            break;
        default:
            printf("Instrução não implementada: 0x%08X (opcode 0x%08X)\n", instr, opcode);
            exit(1);
    }
}
