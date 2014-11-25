#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Sintese.h"

assembly* carregaMenmonicos(assembly *listaAssembly);
assembly* insereAssembly(assembly* listaAssembly, char *mnemonico, int codigo, int tamanho);
void imprime (assembly* l);
TS* buscaSimbolo (TS* lista, char *nome);
assembly* buscaAssembly (assembly* lista, char *mnemonico);
void resolvePendencia(char *nomeArquivoSaida, int posicao, int valor);


//função que insere os mnemonicos de assembly em uma lista encadeada
assembly* insereAssembly(assembly* listaAssembly, char *mnemonico, int codigo, int tamanho)
{
	assembly* listaAux = (assembly*) malloc(sizeof(assembly));

	listaAux->mnemonico = mnemonico;
	listaAux->codigo = codigo;
	listaAux->tamanho = tamanho;

	listaAux->pa = listaAssembly;

	return listaAux;
}

//funcao que busca na lista de mnemonicos assembly o mnemonico que eu quero
assembly* buscaAssembly (assembly* lista, char *mnemonico)
{
	assembly* p;
 	for (p = lista; p!= NULL; p = p->pa){
 		if (!strcmp(p->mnemonico, mnemonico)){
 			return p;			
 		}		
 	}
 	return NULL;
}

//funcao busca na tabela de simbolos o simbolo que eu quero
TS* buscaSimbolo (TS* lista, char *nome)
{
	TS* p;
 	for (p = lista; p!= NULL; p = p->prox){
 		if (!strcmp(p->nome, nome)){
 			return p;			
 		}		
 	}
 	return NULL;
}

//funcao principal que constroi a lista encadeada de mnemonicos
assembly* carregaMenmonicos(assembly *listaAssembly)
{
	FILE *assembler;
	assembly *listaAux = NULL;
	int vez = 0;
	char *mnemonico;
	char separador;
	int codigo;
	int tamanho;

	assembler = fopen("assembly.txt", "r");

	while(!feof(assembler))
	{
		mnemonico = (char*) malloc(1*sizeof(char));
		fscanf(assembler, "%s %d %d %c", mnemonico, &codigo, &tamanho, &separador);

		listaAssembly = insereAssembly(listaAssembly, mnemonico, codigo, tamanho);
	}

	free(mnemonico);

	return listaAssembly;
}

//funcao principal do modulo que gera o cógigo objeto, porem ainda não resolve as pendencias
void Sintese (infoLinha *linha, char *nomeArquivoSaida, TS *TabelaSimbolos)
{
	_Bool status;
	assembly *listaAssembly = NULL, *resultadoBuscaAssembly;
	TS *resultadoBuscaSimbolo;
	FILE *saida;
	char *EhValido, *EhData;
	int valor;

	listaAssembly = carregaMenmonicos(listaAssembly);


	saida = fopen(nomeArquivoSaida, "a");
	
    int i;
	for ( i = 0; i < linha->numTokens; ++i)
	{	
		//verifica se o simbolo é uma instrucao de assembly
		resultadoBuscaAssembly = buscaAssembly(listaAssembly, linha->Tokens[i]);

		//se o simbolo for uma instrucao ele grava
		if (resultadoBuscaAssembly != NULL)
		{
			if (resultadoBuscaAssembly->codigo > 9)
			{
				fprintf(saida, " %d", resultadoBuscaAssembly->codigo);
			}
			else
			{
				fprintf(saida, " 0%d", resultadoBuscaAssembly->codigo);	
			}
		}
		else{

			EhValido = strstr(linha->Tokens[i], ":");

			//verifica se é uma label, se for ele pula
			if (EhValido == NULL)
			{
				//se nao for instrucao ele procura na tabela de simbolo
				resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha->Tokens[i]);

				//se for um simbolo ele grava
				if (resultadoBuscaSimbolo != NULL)
				{
					valor = resultadoBuscaSimbolo->valor + resultadoBuscaSimbolo->offset +1;

					if (valor < 0 || valor > 9)
					{
						fprintf(saida, " %d", valor);
					}
					else
					{
						fprintf(saida, " 0%d", valor);	
					}
				}
			}

			EhData = strstr(linha->Tokens[i], "CONST");

			//verifica se é uma definicao
			if(EhData != NULL)
			{
				valor = atoi(linha->Tokens[i+1]);

				if (valor < 0 || valor > 9)
				{
					fprintf(saida, " %d", valor);
				}
				else
				{
					fprintf(saida, " 0%d", valor);	
				}
			}

			EhData = strstr(linha->Tokens[i], "SPACE");

			//verifica se é para guardar esqpaco
			if(EhData != NULL)
			{
				if (i+1 == linha->numTokens)
				{
					fprintf(saida, " XX");
				}
				else
				{
					valor = atoi(linha->Tokens[i+1]);

					int j;
					for ( j = 0; j < valor; ++j)
					{
						fprintf(saida, " XX");
					}
				}
			}
		}
	}

	fclose(saida);
	
}

//funcao que muda os zeros absolutos do arquivo para os valores definidos
void resolveIndefinicoes(char *nomeArquivoSaida, TS *TabelaSimbolos)
{
	TS* simbolo;
	pilhaPos *pilha;

 	for (simbolo = TabelaSimbolos; simbolo!= NULL; simbolo = simbolo->prox)
 	{
 		for (pilha = simbolo->pilhaDePosicoes; pilha != NULL; pilha = pilha->pilhaPosProx)
 		{
 			resolvePendencia(nomeArquivoSaida, pilha->pos, simbolo->valor);

 		}		
 	}

}


//funcao que resolve as pensadencias da tabela de simbolos
void resolvePendencia(char *nomeArquivoSaida, int posicao, int valor)
{
	FILE *saida;
	int numero, contPosicao = 0, seek;
	char *subs, *token;
	fpos_t position;
	
	subs = (char*)malloc(sizeof(char*));
	token = (char*)malloc(sizeof(char*));
	
	saida = fopen (nomeArquivoSaida, "r+");

	//colocando o ponteiro do arquivo na posicao da indefinicao
	seek = (posicao-1) * 3;

	fseek(saida, seek, SEEK_SET);

	//lendo se algum offset foi gravado
	fscanf(saida, "%s", token);
	rewind(saida);

	fseek(saida, seek, SEEK_SET);

	//calculando o valor do simbolo mais o offset
	valor = valor + atoi(token);
	sprintf(subs, "%d", valor);

	//coloando o valor calculado no lugar da indefinicao
	fprintf(saida, " %s" , subs);

	rewind(saida);
	
	fclose(saida);

}




