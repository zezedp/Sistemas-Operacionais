#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

void listar_diretorio(const char *path) {
    DIR *dir;
    struct dirent *entry;

    printf("Listando conteúdo de: %s\n", path);
    dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;
        printf(" - %s\n", entry->d_name);
    }

    closedir(dir);
}

int main() {
    const char *base_path = "/tmp/q10";
    char dirA[PATH_MAX];
    char dirB[PATH_MAX];

    // Cria diretório base
    if (mkdir(base_path, 0755) != 0) {
        if (errno != EEXIST) {
            perror("mkdir /tmp/q10");
            return 1;
        }
    }
    printf("Criado ou já existe: %s\n", base_path);

    // Caminhos A e B
    snprintf(dirA, sizeof(dirA), "%s/A", base_path);
    snprintf(dirB, sizeof(dirB), "%s/B", base_path);

    // Criar A
    if (mkdir(dirA, 0755) != 0) {
        perror("mkdir A");
        return 1;
    }
    printf("Criado: %s\n", dirA);

    // Criar B
    if (mkdir(dirB, 0755) != 0) {
        perror("mkdir B");
        return 1;
    }
    printf("Criado: %s\n", dirB);

    // Navegar até /tmp/q10
    if (chdir(base_path) != 0) {
        perror("chdir base_path");
        return 1;
    }

    // Listar conteúdo de /tmp/q10
    listar_diretorio(".");

    // Voltar para /
    chdir("/");

    // Remover diretórios
    if (rmdir(dirA) != 0)
        perror("rmdir A");
    else
        printf("Removido: %s\n", dirA);

    if (rmdir(dirB) != 0)
        perror("rmdir B");
    else
        printf("Removido: %s\n", dirB);

    if (rmdir(base_path) != 0)
        perror("rmdir /tmp/q10");
    else
        printf("Removido: %s\n", base_path);

    return 0;
}

