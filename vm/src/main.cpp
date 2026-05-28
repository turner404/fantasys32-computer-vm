#include <filesystem>

#include "../includes/vm.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Deve informar o caminho do código fonte do jogo." << std::endl;
        return -1;
    }

    if (!std::filesystem::exists(argv[1])) {
        std::cerr << "Arquivo não existe." << std::endl;
        return -1;
    }

    if (std::filesystem::file_size(argv[1]) > TAM_MEM) {
        std::cerr << "Arquivo muito grande! O tamanho máximo para o arquivo de entrada é de 16MB." << std::endl;
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