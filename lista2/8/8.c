#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

void list_dir(const char *path){
	DIR *dir;
	struct dirent *entrada;
	struct stat info;

	char path_atual[PATH_MAX];
	char path_novo[PATH_MAX];

	dir = opendir(path);
	if (dir == NULL){
		printf("ERRO: Nao pode abrir diretorio\n");
		return;
	}
	// Salva diretorio atual pra ter como voltar depois
	getcwd(path_atual, sizeof(path_atual));

	chdir(path);

	while ((entrada = readdir(dir)) != NULL){
		// Ignorar "." e ".."
		if (strcmp(entrada->d_name, ".") == 0 || 
				strcmp(entrada->d_name, "..")==0) continue;
		

		if (stat(entrada->d_name, &info) == 0){
			if (S_ISDIR(info.st_mode)){ // RECURSIVO
						    // SE eu acho um diretório, eu passo ele como parametro da list_dir
						    // Funciona semelhante a um DFS - Busca em PRofundidade
						    // ASsim, que eu acho um nó, eu percorro ele até o fim (no caso ate 
						    // nao ter mais diretórios) ai eu volto de nó em nó.
				getcwd(path_novo, sizeof(path_novo));
				printf("%s/%s\n", path_novo, entrada->d_name);
				list_dir(entrada->d_name);
			}
		}
	}
	chdir(path_atual);
	closedir(dir);

}

int main(int argc, char* argv[]){
	if (argc < 2){
		printf("ERRO: Modo de uso %s <path inicial>", argv[0]);
		return 1;
	}

	printf("Listar diretorios a partir de %s\n", argv[1]);
	list_dir(argv[1]);
	return 0;
}
