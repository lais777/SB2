#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Macros.h"

//funcoes auxiliares para o modulo
void gravaLinha(char *, char *);
macro* insereMacro(macro* listaMacro, char *nome, linha_Macro *listaLinhaMacro);
void lendoLinhaMacro(FILE *arquivoEntrada, char *NomeArquivoSaida);
char * separaTokens(char *PrimeiroToken, char *SegundoToken, char *linha);
macro* buscaMacro (macro* listaMacros, char *nome);
macro* guardandoMacro(macro *macro, FILE *arquivoEntrada, char *linha);
void gravaMacro(char *NomeArquivoSaida, macro *resultadoBusca);
linha_Macro* insereLinhaMacro(linha_Macro* listaLinhaMacro, char *linha);
linha_Macro* tamanhoCodigo (linha_Macro *);


// //funcao para salvar no arquivo de erros, caso o programador nao defina o final da macro
// void EscreveArgErro(int linha)
// {

//     FILE *argErros = fopen("erros.txt", "a");
    

//     fprintf(argErros, "4 %d |", linha);
//     fclose(argErros);
// }

//funcao para gravar linhas normais 
void gravaLinha(char *NomeArquivoSaida, char *linha)
{
	FILE *arquivoSaida;

	arquivoSaida = fopen(NomeArquivoSaida, "a");

	strcat(linha,"\n");
	fprintf(arquivoSaida, "%s", linha);

	fclose(arquivoSaida);
}

//funcao para achar a macro que esta sendo referenciada no codigo
macro* buscaMacro (macro* listaMacros, char *nome)
{
	macro *macro;

 	for (macro = listaMacros; macro != NULL; macro = macro->pm){
 		if (!strcmp(macro->nome, nome))
 		{
 			return macro;			
 		}		
 	}

 	return NULL;
}

//funcao que grava a macro no arquivo
void gravaMacro(char *NomeArquivoSaida, macro *resultadoBusca)
{
	FILE *arquivoSaida;
	linha_Macro *codigo, *ultimo_elemento;
	int tamanho, contador = 0;

	arquivoSaida = fopen(NomeArquivoSaida, "a");

	ultimo_elemento = tamanhoCodigo(resultadoBusca->codigo);

	while(ultimo_elemento != resultadoBusca->codigo)
	{
		fprintf(arquivoSaida, "%s\n", ultimo_elemento->linha);
		
		ultimo_elemento = ultimo_elemento->pla;
	}

	fprintf(arquivoSaida, "%s\n", ultimo_elemento->linha);

	fclose(arquivoSaida);
}

//função que insere os as linhas do codigo de uma macro
linha_Macro* insereLinhaMacro(linha_Macro* listaLinhaMacro, char *linha)
{
	linha_Macro* listaAux = (linha_Macro*)malloc(sizeof(linha_Macro));
	listaAux->linha = (char*)malloc(100 * sizeof(char));

	strcpy(listaAux->linha, linha);
	strcat(listaAux->linha, "\0");

	listaAux->pl = listaLinhaMacro;
	
	if (listaLinhaMacro != NULL)
	{
		listaLinhaMacro->pla = listaAux;
	}

	return listaAux;
}

//funcao para retornar a ultima linha da macro
linha_Macro* tamanhoCodigo (linha_Macro *lista)
{
	linha_Macro *p, *ultimo_elemento;
	int tamanho = 0;

	for (p = lista; p != NULL; p = p->pl)
	{	
		ultimo_elemento = p;
		tamanho++;
	}
	
	return ultimo_elemento;
}

//funccao que le o arquivo e avalia se é uma macro ou nao
void lendoLinhaMacro(FILE *arquivoEntrada, char *NomeArquivoSaida)
{
	char *linha, *ehMacro;
	macro *macro = NULL, *resultadoBusca;
	int contador = 0;

	linha = (char*)malloc(100*sizeof(char));

	//lendo linha do arquivo
	fscanf(arquivoEntrada, "%[^\n]%*c", linha);


	while(!feof(arquivoEntrada))
	{
		ehMacro = strstr(linha, "MACRO");

		if (ehMacro != NULL)
		{
			macro = guardandoMacro(macro, arquivoEntrada, linha);

			//resolvendo caso o programador nao coloque o final da macro
			if (feof(arquivoEntrada))
			{
				// EscreveArgErro(contador);
				break;
			}
		}
		else
		{
			resultadoBusca = buscaMacro (macro, linha);

			if (resultadoBusca != NULL)
			{
				gravaMacro(NomeArquivoSaida, resultadoBusca);
			}
			else
			{
				gravaLinha(NomeArquivoSaida, linha);
			}
		}



		fscanf(arquivoEntrada, "%[^\n]%*c", linha);
		contador++;
	}


}

//funcao que gera a lista de macros
macro* guardandoMacro(macro *macro, FILE *arquivoEntrada, char *linha)
{
	char *nomeMacro, *NAME;
	char *linhaMacro;
	
	linha_Macro *linhaCodigo = NULL;

	linhaMacro = (char*)malloc(100 * sizeof(char));

	fscanf(arquivoEntrada, "%[^\n]%*c", linhaMacro);

	while(!feof(arquivoEntrada) && strcmp(linhaMacro, "END"))
	{
		linhaCodigo = insereLinhaMacro(linhaCodigo, linhaMacro);
		fscanf(arquivoEntrada, "%[^\n]%*c", linhaMacro);
	}

	nomeMacro =	(char *)malloc(100 *sizeof(char));
	nomeMacro = (char*)strtok (linha,": ");
	NAME =	(char *)malloc(100*sizeof(char));	
	strcpy(NAME, nomeMacro);
	strcat(NAME, "\0");

	macro = insereMacro(macro, NAME, linhaCodigo);
	
	return macro;

}


//função que insere os mnemonicos de assembly em uma lista encadeada
macro* insereMacro(macro* listaMacro, char *nome, linha_Macro *listaLinhaMacro)
{
	macro* listaAux = (macro*) calloc(1, sizeof(macro));

	listaAux->nome = nome;
	listaAux->codigo = listaLinhaMacro ;

	listaAux->pm = listaMacro;

	return listaAux;
}

//funcao principal do modulo
void resolveMacro (char *nomeArquivoEntrada, char *nomeArquivoSaida)
{
	
	FILE *arquivoEntrada, *arquivoSaida;

	arquivoEntrada = fopen(nomeArquivoEntrada, "r");

	arquivoSaida = fopen(nomeArquivoSaida, "w");

	fclose(arquivoSaida);

	if (arquivoEntrada != NULL && arquivoSaida != NULL)
	{
		lendoLinhaMacro(arquivoEntrada, nomeArquivoSaida);

		fclose(arquivoEntrada);

	}
	else
	{
		printf("Não foi possível abrir o arquivo para leitura/escrita.\nPor favor, tente novamente mais tarde.\n");
	}
}