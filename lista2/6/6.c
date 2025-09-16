#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int main(int argc, char *argv[]){
	char prime[PATH_MAX];
	char atual[PATH_MAX];

	if (argc != 2){
		printf("ERRO: Modo de uso %s <novo_dir>", argv[0]);
		exit(-1);
	}

	const char *novo = argv[1]; // PAssando como argumento o diretorio para o qual eu vou
				    // Claro que nao preciso passar o diretorio atual, ele já consegue pegar pelo getcwd()
	
	// Pega e salva o diretorio atual em 'prime' para depois voltarmos
	if (getcwd(prime, sizeof(prime)) == NULL){
		fprintf(stderr, "ERRO: %s", strerror(errno));
		exit(-2);
	}

	printf("Primeiro diretorio: %s\n", prime);

	// Tenta mudar pro novo diretorio
	if (chdir(novo) != 0){
		fprintf(stderr, "ERRO: Nao pode mudar diretorio: %s", strerror(errno));
		exit(-3);
	}
	// Get curent working directory - DEPOIS DE MUDAR
	if (getcwd(atual, sizeof(atual)) == NULL){
		fprintf(stderr, "ERRO: Nao consigo obter o diretorio atual : %s", strerror(errno));
		exit(-4);
	}

	printf("Diretorio apos mudar: %s\n", atual);

	// VOltando pro original
	if (chdir(prime) != 0){
		fprintf(stderr, "ERRO: Nao pode voltar ao primeiro diretorio : %s", strerror(errno));
		exit(-5);
	}
	// Confirmando que voltamos pro direotrio inicial, pegamos ele pelo getcwd e printamos no atual ele de volta.
	// Nesse contexto, usamos (atual) apenas como convenção
	if (getcwd(atual, sizeof(atual)) == NULL){ 
		fprintf(stderr, "ERRO: Nao pode obter o diretorio original", strerror(errno));
		exit(-6);
	}

	printf("Diretorio apos voltar: %s\n", atual);
	return 0;
}
