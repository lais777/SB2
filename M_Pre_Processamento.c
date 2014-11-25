#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "M_Pre_Processamento.h"


codigo* insereLinha(codigo* listaCodigo, char *linha, int posicao);
codigo* lendoLinha(FILE *arquivoEntrada, codigo *implementacao);
char* preparaLinha(char *linha);


// //função cujo motivo principal é o debug, pois imprimi na tela a lista encadeada
// void imprime (codigo* l)
// {
// 	codigo* p;
// 	int i = 0;
// 	for (p = l; p != NULL; p = p->pl)
// 	{
// 		printf("linha[%d] = %s\n",p->posicao, p->linha);

// 		i++;
// 	}
	
// }

//função cujo motivo principal é o debug, pois imprimi na tela a lista encadeada
void imprimeIfs (se* l)
{
	se* p;
	
	for (p = l; p != NULL; p = p->pf)
	{
		printf("determinante = %s\n", p->determinante);
		printf("posicao = %d\n", p->linha);
	}
	
}

//funcao que transforma tudo em maiuscula
char * maiusculaPre(char *string)
{
    int i, tamanho;
    char *stringOut, *stringAux;
    int n = strlen(string);

    stringOut = ( char *)malloc((strlen(string)+1)*sizeof(char));
    stringAux = ( char *)malloc((strlen(string)+1)*sizeof(char));
    
    tamanho = strlen(string);

    strcpy(stringAux, string);

    for(i=0;i<tamanho;i++)
    {
        stringOut[i]=toupper(stringAux[i]);
    }

    stringOut[i]= '\0';

    return stringOut;
}

//função que insere os ifs na sua respectiva lista
se* insereIf(se* listaIfs, char *determinante, int posicaoLinha)
{
	se* listaAux = (se*)malloc(sizeof(se));
	listaAux->determinante = (char*)malloc(100 *sizeof(char));

	strcpy(listaAux->determinante, determinante);
	strcat(listaAux->determinante, "\0");
	listaAux->linha = posicaoLinha;

	listaAux->pf = listaIfs;

	return listaAux;
}


//função que insere os EQUs na sua respectiva lista
equ* insereEqu(equ* listaEqus, char *tokenDeterminado)
{
	equ* listaAux = (equ*)malloc(sizeof(equ));
	listaAux->tokenDeterminado = (char*)malloc(100 *sizeof(char));

	strcpy(listaAux->tokenDeterminado, tokenDeterminado);
	strcat(listaAux->tokenDeterminado, "\0");

	listaAux->pt = listaEqus;

	return listaAux;
}

//função que insere os as linhas do codigo
codigo* insereLinha(codigo* listaCodigo, char *linha, int posicao)
{
	codigo* listaAux = (codigo*)malloc(sizeof(codigo));
	listaAux->linha = (char*)malloc((strlen(linha)+3)*sizeof(char));

	strcpy(listaAux->linha, linha);
	strcat(listaAux->linha, "\0");
	listaAux->posicao = posicao;

	listaAux->pl = listaCodigo;
	
	if (listaCodigo != NULL)
	{
		listaCodigo->pla = listaAux;
	}

	return listaAux;
}

//funcao que trata a criacao da lista de ifs
se* verificaIf(char *linha, int posicaoLinha, se* listaIfs)
{
	char *EhIf, *determinante;

	determinante =	(char *)malloc(100 * sizeof(char));
	determinante = (char*)strtok (linha," ");
	determinante = (char*)strtok (NULL," ");

	listaIfs = insereIf(listaIfs, determinante, posicaoLinha);

	return listaIfs;

}

//funcao que trata a criacao da lista de equs
equ* verificaEqus(char *linha, equ* listaEqus)
{
	char *EhUm, *token;

	EhUm = strstr(linha, "0");

	if (EhUm != NULL)
	{
		token =	(char *)malloc(100 *sizeof(char));
		token = (char*)strtok (linha,": ");

		listaEqus = insereEqu(listaEqus, token);
	}

	return listaEqus;

}

/* função retira: retira elemento da lista */
codigo* retira (codigo* lista, int posicao) 
{
	codigo* ant = NULL; 
	codigo* p = lista; 

	while (p != NULL && p->posicao != posicao) 
	{
		p = p->pl;
 	}
 
	//verifica se achou elemento
 	if (p == NULL)
 	{
 		return lista; 
 	}
 		
	//retira elemento
	if (lista == p) {
		lista = p->pl;
 	}
 	else 
 	{
 		ant = p->pla;
 		ant->pl = p->pl;
 		p->pl->pla = ant;
 	}
 	
 	free(p);
 	return lista;
}


//verifica quais linhas tem if e quais foram definidas
codigo* resolveIfs(se *listaIfs, equ *listaEQUs, codigo *listaCodigo)
{
	se *pSe;
	equ *pEQU;

	if (listaEQUs == NULL)
	{
		return listaCodigo;
	}

 	for (pEQU = listaEQUs; pEQU != NULL; pEQU = listaEQUs->pt)
 	{	
 		for (pSe = listaIfs; pSe != NULL; pSe = listaIfs->pf)
 		{
 			if (!strcmp(pSe->determinante, pEQU->tokenDeterminado))
 			{
 				listaCodigo = retira(listaCodigo, pSe->linha);
 			}	
 		}	
 	}

 	return listaCodigo;
}

//funcao para retornar a ultima linha da lista de codigo
codigo* finalCodigo (codigo *lista)
{
	codigo *p, *ultima_linha;

	for (p = lista; p != NULL; p = p->pl)
	{	
		ultima_linha = p;
	}
	
	return ultima_linha;
}

void gravaArquivoSaida(FILE *arquivoSaida, codigo* listaCodigo)
{
	codigo *codigo, *ultima_linha;

	ultima_linha = finalCodigo(listaCodigo);

	while(ultima_linha != listaCodigo)
	{
		fprintf(arquivoSaida, "%s\n", ultima_linha->linha);
		
		ultima_linha = ultima_linha->pla;
	}

	fprintf(arquivoSaida, "%s\n", ultima_linha->linha);

	fclose(arquivoSaida);
	// free(codigo);
	// free(ultima_linha);

}


//funccao que le o arquivo e avalia se é uma macro ou nao
codigo* lendoLinha(FILE *arquivoEntrada, codigo *implementacao)
{
	char *linha, *linha_preparada, new_line, primeiro_token;
	char *EhIf, *EhEqu;
	int posicaoLinha = 0, contadorIfs = 0, contadorEqus = 0;
	se *listaIfs = NULL;
	equ *listaEQUs = NULL;
	fpos_t position;

	linha = (char*)malloc(100 * sizeof(char));
	linha_preparada = (char*)malloc(100* sizeof(char));

	//lendo linha do arquivo
	fgetpos(arquivoEntrada, &position);
	fscanf(arquivoEntrada, "%c", &primeiro_token);

	while(!feof(arquivoEntrada))
	{
		if (primeiro_token != '\n')
		{
			fsetpos(arquivoEntrada, &position);
			fscanf(arquivoEntrada, "%[^\n]", linha);
			fscanf(arquivoEntrada, "%c", &new_line);
   
			linha_preparada = preparaLinha(linha);

			linha_preparada = maiusculaPre(linha_preparada);

			EhIf = strstr(linha_preparada, "IF");

			if (EhIf != NULL)
			{
				listaIfs = verificaIf(linha_preparada, posicaoLinha, listaIfs);
			}
			else
			{
				EhEqu = strstr(linha_preparada, "EQU");

				if (EhEqu != NULL)
				{
					listaEQUs = verificaEqus(linha_preparada, listaEQUs);
				}
				else
				{
					implementacao = insereLinha(implementacao, linha_preparada, posicaoLinha);	
					posicaoLinha++;
				}
			}
			
		}
		
		fgetpos(arquivoEntrada, &position);
		fscanf(arquivoEntrada, "%c", &primeiro_token);
	}

	implementacao = resolveIfs(listaIfs, listaEQUs, implementacao);


	return implementacao;

}

char* preparaLinha(char *linha)
{
	char *token;
	char *instrucao;
  	
  	instrucao = (char*)calloc(strlen(linha)+3 , sizeof(char));
  	token = strtok (linha," \t");

  	strcpy(instrucao, token);

  	while (token != NULL)
  	{
    	token = strtok (NULL, " \t");

    	if (token != NULL)
    	{
    		strcat(instrucao, " ");
    		strcat(instrucao, token);
    	}
    	
  	}

  	strcat(instrucao, "\0");

  	return instrucao;
}


void resolvePreProcessamento(char *nomeArqEntrada, char *nomeArqSaida)
{
	FILE *entrada;
	FILE *saida;
	codigo *implementacao = NULL;

	entrada = fopen(nomeArqEntrada, "r");
	saida = fopen(nomeArqSaida, "w");

	if (entrada != NULL && saida != NULL)
	{
		implementacao = lendoLinha(entrada, implementacao);

		gravaArquivoSaida(saida, implementacao);

		fclose(entrada);
	}
	else
	{
		printf("Não foi possível abrir o arquivo para leitura/escrita.\nPor favor, tente novamente mais tarde.\n");
	}

}