#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome_do_diretorio>\n", argv[0]);
        return 1;
    }

    const char *dirname = argv[1];

    // Cria o diretório
    if (mkdir(dirname, 0755) == -1) {
        perror("Erro ao criar diretório");
        return 1;
    }

    // Define as permissões rwxr-x--- (750 em octal)
    if (chmod(dirname, 0750) == -1) {
        perror("Erro ao alterar permissões");
        return 1;
    }

    printf("Diretório '%s' criado com permissões rwxr-x---\n", dirname);

    return 0;
}

