#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int check_empty(const char *path){
	DIR *dir = opendir(path);
	struct dirent* entrada;
	int count = 0;

	if (!dir){
		fprintf(stderr, "ERRO: Nao foi possivel abrir o diretorio",strerror(errno));
		exit(-1);
	}
	// Como readdir lê a proxima entrada de um diretório aberto, eu posso iterar sobre o diretório
	// todo inicio de loop eu leio o próximo ate finalizar e dar NULL
	while ((entrada = readdir(dir)) != NULL){
		// Loop vai ignorar . e .., que tem em todos os diretorios
		// SE achar algo, ele dá count++ e dá break, porque só nos importa
		// se for vazio. Como tem algo ali, nao é vazio e portanto noa dá pra remover.
		if (strcmp(entrada->d_name, ".") != 0 &&
				strcmp(entrada->d_name, "..") != 0){
			count++;
			break;
		}
	}

	closedir(dir);
	return (count == 0);
}

int main(int argc, char* argv[]){
	if (argc != 2){
		printf("ERRO: Modo de uso %s <path>\n", argv[0]);
		exit(-2);
	}

	const char *path = argv[1];
	int resultado = check_empty(path);
	if (resultado == 1){
		// DIR VAZIO (count == 0 -> retornou 1)
		if (rmdir(path) == 0) printf("'%s' removido!\n", path);
		else fprintf(stderr, "ERRO: %s", strerror(errno));
	}

	else if (resultado == 0) {
		// dir nao ta vazio (count == 0 -> retornou 0)
		printf("ERRO: Diretorio '%s' nao esta vazio, nao removemos\n", path);
	}
	else {
		printf("ERRO: Nao consegui acessar o diretorio '%s'\n", path);
	}
	return 0;
}
