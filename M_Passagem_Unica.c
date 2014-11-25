#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "M_Sintese.h"
#include "M_Passagem_Unica.h"
#include "M_Analise.h"



void resolvePassagemUnica(char *nomeEntrada, char *nomeSaida)
{

	
	infoLinha *linha;
	FILE *ptr_file, *saida;

	FILE *argErros = fopen("erros.txt", "w");
	fclose(argErros);    

	int i =0,j = 0, k, fim,m, posicao = 1;
	int *primeiraVez;
	TS * tabelaSims = NULL;
	int * numSim = NULL;
	opLinha * linhas = NULL;
	saida = fopen (nomeSaida, "w");
	fclose(saida);

	ptr_file =fopen(nomeEntrada,"r");


	//verifica se o arquivo para leitura foi aberto
    if (!ptr_file)
    {
        printf("Não foi possível abrir o arquivo para leitura/escrita.\nPor favor, tente novamente mais tarde.\n");
	}

	linha = (infoLinha *) malloc(1*sizeof(infoLinha));

	//laco principal que le o arquivo de codigo
	while(1)
	{
		fim = Analise (linha, ptr_file, tabelaSims, numSim);

		if(fim)
		{
			break;
		}
		EscreveNumLinha(linha, j);

		 j++;
	
	 	tabelaSims = retornaTabelaSimbolos(linha, tabelaSims,  posicao);
	 	posicao+= contaSomaPos( linha); 

	 	linhas = AnaliseSintatica( linha, tabelaSims,linhas);
	 
	// 	//chamando a funcao de sintese para gerar o codigo objeto
		Sintese (linha, nomeSaida, tabelaSims);
	 }
	 

	 analiseSemantica(linhas, tabelaSims);
	// //resolvendo as indefinicoes de simbolos do codigo objeto
	 resolveIndefinicoes(nomeSaida,tabelaSims);
	fclose(ptr_file);
}



