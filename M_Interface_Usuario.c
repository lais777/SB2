#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Interface_Usuario.h"
#include "M_Macros.h"
#include "M_Pre_Processamento.h"


int main(int argc, char const *argv[])
{
	char *nomeEntrada;
	char *nomeSaidaPre, *nomeSaidaMacro, *nomeSaida;

	nomeEntrada = (char*)malloc((strlen(argv[2])+4)*sizeof(char*));
	nomeSaida = (char*)malloc((strlen(argv[3])+4)*sizeof(char*));
	nomeSaidaPre = (char*)malloc((strlen(argv[3])+4)*sizeof(char*));
	nomeSaidaMacro = (char*)malloc((strlen(argv[3])+4)*sizeof(char*));

	strcpy(nomeEntrada, argv[2]);
	strcpy(nomeSaida, argv[3]);
	strcpy(nomeSaidaPre, argv[3]);
	strcpy(nomeSaidaMacro, argv[3]);

	strcat(nomeEntrada, ".asm");
	// strcat(nomeSaida, ".o");
	strcat(nomeSaidaPre, ".pre");
	strcat(nomeSaidaMacro, ".mcr");
	
	//gerando o arquivo .pre
	resolvePreProcessamento(nomeEntrada, nomeSaidaPre);
	
	//gerando .mcr 
	resolveMacro(nomeSaidaPre, nomeSaidaMacro);

	


	return 0;
}