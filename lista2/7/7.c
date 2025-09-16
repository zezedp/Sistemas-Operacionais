#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main(){
	char data[11]; // YYYY-MM-DD
	time_t agora = time(NULL);
	struct tm *tm_info = localtime(&agora);

	if (strftime(data, sizeof(data), "%Y-%m-%d", tm_info) == 0){
		fprintf(stderr, "ERRO: Formatar data : %s\n", strerror(errno));
		exit(-1);
	}

	// Constroi o caminho /tmp/YYYY-MM-DD
	char path[256];
	snprintf(path, sizeof(path), "/tmp/%s", data);

	if (mkdir(path, 0755) == 0){
		printf("Diretorio foi criado: %s\n", path);
	} else {
		if (errno == EEXIST){
			printf("ERRO: Diretorio ja existe\n");
			exit(-2);
		} else{
			fprintf(stderr, "ERRO: Nao foi possivel criar o diretorio %s : %s", path, strerror(errno));
			exit(-3);
		}
	}
	return 0;
}
