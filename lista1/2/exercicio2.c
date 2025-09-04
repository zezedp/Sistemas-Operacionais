#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd;
	ssize_t bytes_lidos;
	char buffer1[101]; // Declaro 101 = 100 bytes + 1 para o '\0'
	char buffer2[51]; // Declaro 51 = 50 + 1 pro '\0'
	
	if (argc != 2) {
		printf("ERRO: Modo de uso %s <nome arquivo>\n", argv[0]);
		exit(-1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1){
		printf("ERRO: open()");
		exit(-2);
	}

	bytes_lidos = read(fd, buffer1, 100);
	if (bytes_lidos == -1){
		printf("ERRO: primeiros 100 bytes");
		close(fd);
		exit(-3);
	}
	
	buffer1[bytes_lidos] = '\0';
	
	// Pula pro 200 partindo do 0
	if (lseek(fd, 200, SEEK_SET) == -1){
		printf("ERRO: lseek() para byte 200");
		close(fd);
		exit(-4);
	}

	bytes_lidos = read(fd, buffer2, 50);
	if (bytes_lidos == -1){
		printf("ERRO: read() 50 bytes a partir do 200");	
		close(fd);
		exit(-5);
	}
	buffer2[bytes_lidos] = '\0';

	printf("Primeiros 100 bytes do arquivo:\n%s\n", buffer1);
	printf("50 bytes depois do 200:\n%s\n", buffer2);

}
