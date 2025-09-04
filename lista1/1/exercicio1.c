#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char* argv[]){
	int fd;
	off_t tam_arq;

	if (argc != 2) {
		printf("ERRO: Execute %s <nomearquivo>\n", argv[0]);
		exit(-1);
	}
	
	fd = open(argv[1], O_RDONLY);
	
	// Como open() é uma syscall, que pode ou nao conseguir abrir o arquivo, tratamos com o if abaixo dando um 'catch' 
	if (fd == -1) {
		perror("ERRO: open()");
		exit(-2);
	}
	// Pede para mover 0 bytes de offset partindo do fim do arquivo
	tam_arq = lseek(fd, 0, SEEK_END); // Move o ponteiro pro final do arquivo
	if (tam_arq == -1){
		perror("ERRO: lseek()");
		close(fd);
		exit(-3);
	}

	printf("Tamanho do arquivo '%s' é %lld bytes\n", argv[1], (long long) tam_arq);

	close(fd);
	return 0;
}
