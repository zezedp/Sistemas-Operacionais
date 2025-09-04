#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// lstat => tamaho do nome do destino do link, nesse caso 'arquivo.txt' = 11 bytes
// stat tamanho do conteudo do arquivo.txt
int main(){
	struct stat fileinfo_stat;
	struct stat fileinfo_lstat;

	if (stat("link.txt", &fileinfo_stat) == -1){
		printf("ERRO: stat()");
		exit(-1);
	}

	if (lstat("link.txt", &fileinfo_lstat) == -1){
		printf("ERRO: lstat()");
		exit(-1);
	}

	printf("stat(\"link.txt\"):\n");
	printf("Tamanho do arquivo real: %lld bytes\n", (long long) fileinfo_stat.st_size);

	printf("lstat(\"link.txt\"):\n");
	printf("Tamanho do link simbólico: %lld bytes\n", (long long) fileinfo_lstat.st_size);
	return 0;
}
