#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char* argv[]){	
	if (argc < 2) {
		printf("ERRO: Modo de uso %s dir1 dir2 ...\n", argv[0]);
		exit(-1);
	}
	int exit = 0;
	for (int i = 1; i < argc; ++i) {
		const char *path = argv[i];
		
		// Como faz umask & 0755 => vira as permissões finais
		// Eu garanto que as permissões corretas serão aplicadas com o chmod
		// porque vai que o umask & 0755 nao dê 0755

		if (mkdir(path, 0755) == 0){
			if (chmod(path, 0755) !=0) {
				printf("ERRO: diretorio '%s' criado, mas chmod() falhou.\n", path);
				exit = -2;
			} else {
				printf("Criado: %s (0755)\n", path);
			}
		} else {
			if (errno == EEXIST) {
				struct stat st;
				// Inicializo a esturtura st com o stat
				// e checo primeiro se rodou certo o stat()
				// E Além disso, se o diretorio que eu chequei no stat é um diretório de fato
				// Se passou isso -> roda chmod para tornar 0755
				// Se o S_ISDIR for negativo, ele nao é diretório e já existe.
				if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
					if (chmod(path, 0755) != 0){
						printf("ERRO: '%s' existe, mas chmod falhou\n", path);
						exit = -3;
					} else {
						printf("O '%s' ja existe, mas as permissões foram ajustadas para 0755\n", path);
					}
				} else {
					printf("ERRO: '%s' ja existe e nao eh um diretorio\n", path);
					exit = -4;
				}
			} else{
				printf("ERRO: nao conseguiu criar '%s'\n", path);
				exit = -5;
			}
		}
	}
	return exit;
}



