#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char* argv[]){
	char cwd[1024];

	if (argc != 2){
		printf("ERRO: Modo de uso %s diretorio.\n", argv[0]);
		exit(-1);
	}
	
	// Roda chdir pro argumento
	// Se der diferente de 0 é porque deu erro em algum lugar e a mensagem do errno já nos esclarece isso
	// Como deu erro já no chdir, nao há motivo para continuar rodando o programa. Damos exit()
	if (chdir(argv[1]) != 0){
		fprintf(stderr, "ERRO: Não conseguiu mudar de diretório - %s", strerror(errno));
		exit(-2);
	}

	// Pego o CURRENT WORKING DIRECTORY e armazeno no cwd (array de char)
	// Mesma forma, trato o erro e dou exit
	if (getcwd(cwd, sizeof(cwd)) == NULL){
		fprintf(stderr, "ERRO: getcwd() - %s", strerror(errno));
		exit(-3);
	}

	printf("Diretorio Atual: %s\n", cwd);
	return 0;
}
