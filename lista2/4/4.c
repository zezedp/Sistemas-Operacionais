#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	char path[1024];
	char *p;

	if (argc != 2){
		printf("ERRO: Modo de uso %s <pasta1/pasta2/pasta3/...>\n", argv[0]);
		exit(-1);
	}

	strncpy(path, argv[1], sizeof(path));

	for (p = path + 1; *p; ++p){
		// Vai iterando pela string do path
		// Se chegar no '/' ele trunca o diretorio atual com o byte nulo e cria o diretório completo até ali
		// CLARO, se der erro em algum dos diretórios, nao posso continuar criando os subsequentes, tem buraco no meio
		if (*p == '/'){
			*p = '\0';
			if (mkdir(path, 0755) != 0 && errno != EEXIST){
				fprintf(stderr, "ERRO: Nao foi possivel criar o diretorio '%s' - %s", p, strerror(errno));
				exit(-2);
			}
			*p = '/'; // Depois que criei o diretório do laço atual, eu posso trocar o byte nulo pelo '/' de verdade
				  // Continuando a listar esses diretórios.
		}
	}
	
	printf("Diretorios criados: %s\n", argv[1]);
	return 0;
}
