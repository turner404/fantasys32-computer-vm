#include <stdint.h>

class VirtualMachine {
   public:
    const uint8_t SP = 14;
    const uint8_t PC = 15;
    const uint8_t SIZE_MEM = (16 * 1024 * 1024);  // 32.7KiB This is the max size that our games must have.

    /*
     * Registers:
     * Each register has 4 byte.
     * regs[0] -> R0, regs[1] -> R1, regs[2] -> R2, etc...
     * The last register (regs[15]) has the address of the next instruction.
     * It's our PC.
     */
    int32_t regs[16];

    // The memory that is load the binary program (our games).
    uint8_t* mem;

    VirtualMachine();
    ~VirtualMachine();
    void loadCode(char* binFile);
    void executeInstruction();
};