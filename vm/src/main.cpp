#include "../includes/vm.h"

int main() {
    VirtualMachine* vm = new VirtualMachine();
    vm->loadCode("../games/bin/prog1");

    while (1) {
        vm->executeInstruction();
    }

    return 0;
}