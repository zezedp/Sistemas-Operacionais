#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char* argv[]){
	if (argc != 2) {
		printf("ERRO: Modo de uso %s <nome arquivo>\n", argv[0]);
		exit(-1);
	}

	int fd = open(argv[1], O_WRONLY);
	if (fd == -1) {
		printf("ERRO: open()\n");
		exit(-2);
	}
	// Pula offset de 20 bytes partindo do inicio do arquivo
	if (lseek(fd, 20, SEEK_SET) == -1) {
		printf("ERRO: lseek()");
		close(fd);
		exit(-3);
	}

	char *msg = "FIM\n";
	if (write(fd, msg, 4) == -1){
		printf("ERRO: write()");
		close(fd);
		exit(-4);
	}

	close(fd);
	printf("Tarefa realizada com sucesso!\n");
	return 0;
}
