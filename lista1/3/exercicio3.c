#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
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


int main(int argc, char* argv[]){
	if (argc != 2) {
		printf("ERRO: Modo de uso %s <nome do arquivo>\n", argv[0]);
		exit(-1);
	}
	// int stat(const char *caminho, struct stat *buf)
	// buf é um ponteiro para uma struct onde vai preencher as informacoes do arquivo
	// Campos: st_size = tamanho em bytes
	// st_nlink = n de links para o arquivo
	// st_uid = ID do dono
	// st_mode = Permissoes de acesso
	// st_mtime = Data da ultima mod.
	struct stat fileinfo;
	if (stat(argv[1], &fileinfo) == -1) {
		printf("ERRO: acesso arquivo\n");
		exit(-2);
	}

	printf("Tamanho do arquivo: %lld bytes\n", (long long) fileinfo.st_size);
	printf("Número de links: %ld\n", (long) fileinfo.st_nlink);
	printf("UID do dono: %d\n", fileinfo.st_uid);

	show_perm(fileinfo.st_mode);

	char data_formatada[100];
	struct tm *tempo = localtime(&fileinfo.st_mtime);
	strftime(data_formatada, sizeof(data_formatada), "%d/%m/%Y %H:%M:%S", tempo);
	printf("Última mod. : %s\n", data_formatada);

	return 0;
}
