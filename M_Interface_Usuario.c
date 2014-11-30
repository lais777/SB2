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
	char nomeEntrada[] = "inventado.asm";
	char nomeSaidaPre[] = "inventadoPRE.pre";
	char nomeSaidaMacro[] = "inventadoMACRO.mcr";
	char nomeSaida[] = "saidaIA32.asm";

	// strcpy(nomeEntrada, argv[2]);
	// strcpy(nomeSaida, argv[3]);
	// strcpy(nomeSaidaPre, argv[3]);
	// strcpy(nomeSaidaMacro, argv[3]);

	// strcat(nomeEntrada, ".asm");
	// // strcat(nomeSaida, ".o");
	// strcat(nomeSaidaPre, ".pre");
	// strcat(nomeSaidaMacro, ".mcr");
	
	//gerando o arquivo .pre
	resolvePreProcessamento(nomeEntrada, nomeSaidaPre);
	
	//gerando .mcr 
	resolveMacro(nomeSaidaPre, nomeSaidaMacro);

	resolvePassagemUnica(nomeSaidaMacro, nomeSaida);

	


	return 0;
}