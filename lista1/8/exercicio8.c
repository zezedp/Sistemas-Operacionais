#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void show_perm(mode_t mode){
        printf("Permissões de acesso: ");
        // S_IRUSR ... sao macros definidas no sys/stat.h
        //
        // Dono
        if (mode & S_IRUSR) printf("r"); else printf("-");
        if (mode & S_IWUSR) printf("w"); else printf("-");
        if (mode & S_IXUSR) printf("x"); else printf("-");

        // Grupo
        if (mode & S_IRGRP) printf("r"); else printf("-");
        if (mode & S_IWGRP) printf("w"); else printf("-");
        if (mode & S_IXGRP) printf("x"); else printf("-");

        // Others
        if (mode & S_IROTH) printf("r"); else printf("-");
        if (mode & S_IWOTH) printf("w"); else printf("-");
        if (mode & S_IXOTH) printf("x"); else printf("-");

        printf("\n");
}

void show_type(mode_t modo){
	if (S_ISREG(modo)) printf("Arquivo Regular\n");
	else if (S_ISDIR(modo)) printf("Diretório\n");
   	else if (S_ISLNK(modo)) printf("Link simbólico\n");
    	else printf("Desconhecido\n");
}

int main(int argc, char* argv[]){
	if (argc <2) {
		printf("ERRO: Modo de uso %s <nome arquivo> <arquivo 2> .....\n", argv[0]);
		exit(-1);
	}

	struct stat fileinfo;

	for (int i = 1; i < argc; ++i) {
		printf("\nARQUIVO = %s\n", argv[i]);
		if (stat(argv[i], &fileinfo) == -1){
			printf("ERRO: stat()");
			continue;
		}

		printf("Tamanho do arquivo eh de %ld bytes\n", (long) fileinfo.st_size);
		show_type(fileinfo.st_mode);
		show_perm(fileinfo.st_mode);
		
	}
	return 0;
}
