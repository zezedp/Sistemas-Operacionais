#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	if (argc < 2) {
		printf("ERRO: Modo de uso %s dir1 dir2 ...\n", argv[0]);
		exit(-1);
	}

	int exit = 0;
	// Laço for para iterar pelos diretórios
	// Caso eu consiga dar rmdir(path), então tudo nos conformes
	// Caso contrário, eu printo o erro com a mensagem triggada pelo errno
	// NAO DÁ EXIT A CADA ERRO, PORQUE QUERO QUE TENTE TODOS,
	// SE DER ERRO E DER EXIT NO SEGUNDO DIRETORIO DE 8 NO TOTAL, EU PERCO OS SUBSEQUENTES.
	for (int i = 1; i < argc; ++i){
		const char *path = argv[i];

		if (rmdir(path) == 0){
			printf("Removido: %s\n", path);
		} else {
			fprintf(stderr, "ERRO: Nao conseguiu remover '%s': '%s'\n", path, strerror(errno));
			exit = 1;
		}
	}
	return exit;
}
