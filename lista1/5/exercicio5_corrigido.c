#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

// fstat = stat mas recebe file descriptor no lugar do nome do arquivo
// eles já lidam com o arquivo linkado, entao nao tem como saber se eh soft link. Para isso usa-se lstat
// stat = segue o link, fstat= arquivo já esta aberto
void show_type(mode_t modo, char* argv[])
{
	if (S_ISREG(modo)) {
		printf("%s eh arquivo regular.\n", argv[1]);
	}
	else if (S_ISDIR(modo)){
		printf("%s eh diretorio.\n", argv[1]);
	}
	else if (S_ISLNK(modo)){
		printf("%s eh link simbolico.\n", argv[1]);
	}
	else {
		printf("%s eh outro tipo de arquivo.\n", argv[1]);
	}
} 
int main(int argc, char* argv[]){
	if (argc != 2){
		printf("ERRO: Modo de uso %s <nome arquivo>\n", argv[0]);
	exit(-1);
	}
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1){
		printf("ERRO: open()");
		exit(-1);
	}

	struct stat fileinfo_fstat;
	struct stat fileinfo_stat;
	struct stat fileinfo_lstat;

	if (fstat(fd, &fileinfo_fstat) == -1){
		printf("ERRO: fstat()");
		close(fd);
		exit(-2);
	}
	
	if (stat(argv[1], &fileinfo_stat) == -1){
		printf("ERRO: stat()");
		close(fd);
		exit(-3);
	}
	
	if (lstat(argv[1], &fileinfo_lstat) == -1){
		printf("ERRO: lstat()");
		close(fd);
		exit(-4);
	}
	printf("fstat => ");
	show_type(fileinfo_fstat.st_mode, argv);
	printf("\nstat => ");
	show_type(fileinfo_stat.st_mode, argv);
	printf("\nlstat => ");
	show_type(fileinfo_lstat.st_mode, argv);
	if (fileinfo_fstat.st_mode == fileinfo_stat.st_mode) printf("fstat e stat Tem modos iguais.\n");
	else printf("Os modos stat e fstat nao sao iguais.\n");
	close(fd);
	return 0;
}

