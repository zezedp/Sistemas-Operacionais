#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
	if (argc != 2){
		printf("ERRO: Modo de uso %s <nome arquivo>\n", argv[0]);
		exit(-1);
	}

	int fd = open(argv[1], O_RDONLY);

	if (fd == -1) {
		printf("ERRO: open()");
		exit(-1);
	}

	// Pega o tamanho do arquivo
	off_t tamanho_arq = lseek(fd, 0, SEEK_END);
	if (tamanho_arq == -1){
		printf("ERRO: lseek() SEEK_END");
		close(fd);
		exit(-2);
	}
	// VOlta pro começo, offset de zero partindo do inicio
	if (lseek(fd, 0, SEEK_SET) == -1){
		printf("ERRO: lseek() SEEK_SET");
		close(fd);
		exit(-3);
	}

	int count = 0;
	char byte;
	
	for (off_t i = 0; i < tamanho_arq; ++i){
		// Move o ponteiro do arquivo (leitura) para posicao inicial + i, assim, 
		// toda vez ele parte do inicio do arquivo e soma o offset do laço,
		// percorrendo todo o arquivo quando chega no tamanho_arq encontrado anteriormente
		if (lseek(fd, i, SEEK_SET) == -1) {
			printf("ERRO: lseek() LOOP");
			close(fd);
			exit(-4);
		}

		if (read(fd, &byte, 1) != 1) {
			printf("ERRO: Leitura do byte");
			close(fd);
			exit(-5);
		}

		if (byte == 0){
			count++;
		}
	}
	printf("Total de bytes nulos: %d\n", count);
}
