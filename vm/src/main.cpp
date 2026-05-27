#include "../includes/vm.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Deve informar o caminho do código fonte do jogo." << std::endl;
        return -1;
    }

    char* file = argv[1];
    int flag = 0;

    if (argc > 2)
        flag = std::stoi(argv[2]);

    VirtualMachine* vm = new VirtualMachine(file, flag);

    while (1) {
        vm->executeInstruction();
    }

    return 0;
}