#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Interface_Usuario.h"
#include "M_Macros.h"
#include "M_Pre_Processamento.h"
#include "M_Passagem_Unica.h"


int main(int argc, char const *argv[])
{
	char *nomeEntrada;
	char *nomeSaidaPre, *nomeSaidaMacro, *nomeSaida, *nomeSaidaBin, *nomeSaidaDebug;

	nomeEntrada = (char*)malloc((strlen(argv[2])+6)*sizeof(char));
	nomeSaida = (char*)malloc((strlen(argv[2])+6)*sizeof(char));
	nomeSaidaBin = (char*)malloc((strlen(argv[2])+6)*sizeof(char));
	nomeSaidaDebug = (char*)malloc((strlen(argv[2])+6)*sizeof(char));

	nomeSaidaPre = (char*)malloc((strlen(argv[2])+6)*sizeof(char));
	nomeSaidaMacro = (char*)malloc((strlen(argv[2])+6)*sizeof(char));


	// char nomeEntrada[] = "inventado.asm";
	// char nomeSaidaPre[] = "inventadoPRE.pre";
	// char nomeSaidaMacro[] = "inventadoMACRO.mcr";
	// char nomeSaida[] = "saidaIA32.asm";

	strcpy(nomeEntrada, argv[2]);
	strcpy(nomeSaida, argv[2]);
	strcpy(nomeSaidaPre, argv[2]);
	strcpy(nomeSaidaMacro, argv[2]);

	strcat(nomeEntrada, ".asm");
	strcat(nomeSaida, ".s");
	strcat(nomeSaidaBin, ".bin");
	strcat(nomeSaidaDebug, ".txt");

	strcat(nomeSaidaPre, ".pre");
	strcat(nomeSaidaMacro, ".mcr");
	
	//gerando o arquivo .pre
	resolvePreProcessamento(nomeEntrada, nomeSaidaPre);
	
	//gerando .mcr 
	resolveMacro(nomeSaidaPre, nomeSaidaMacro);

	resolvePassagemUnica(nomeSaidaMacro, nomeSaida, nomeSaidaBin, nomeSaidaDebug);

	


	return 0;
}