#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "M_Sintese.h"
#include "M_Passagem_Unica.h"
#include "M_Dicionario.h"

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

void gravandoNoArquivo(linha_Instrucao *trad, FILE *saida)
{
	linha_Instrucao *p, *final;

	final = trad;

	for (p = trad; p!=NULL; p=p->prox)
	{
		final = p;
	}

	for (p = final; p != trad; p = p->ant)
	{
		fprintf(saida, "%s\n", p->traducao);
		printf("Saida = %s\n", p->traducao);
	}

	fprintf(saida, "%s\n", p->traducao);

}



//funcao principal do modulo que gera o cógigo objeto, porem ainda não resolve as pendencias
void Sintese (infoLinha *linha_info, char *nomeArquivoSaida, TS *TabelaSimbolos)
{
	_Bool status;
	assembly *listaAssembly = NULL, *resultadoBuscaAssembly;
	TS *resultadoBuscaSimbolo, *resultadoBuscaSimbolo2;
	FILE *saida;
	char *EhValido, *EhData;
	char convertido;
	int valor;
	Traducao *traducao;

	traducao = (Traducao *)malloc(1*sizeof(Traducao));

	saida = fopen(nomeArquivoSaida, "a");
	
    int i;
	for ( i = 0; i < linha_info->numTokens; ++i)
	{
		if (!strcmp(linha_info->Tokens[i], "ADD"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = addTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = addTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}

			gravandoNoArquivo(traducao->traducao, saida);
			
		}
		else if (!strcmp(linha_info->Tokens[i], "SUB"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = subTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = subTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "MULT"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				// convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = multTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				// convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = multTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "DIV"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = divTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = divTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "JMP"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = jmpTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = jmpTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "JMPN"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = jmpnTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = jmpnTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "JMPP"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = jmppTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = jmppTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "JMPZ"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = jmpzTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = jmpzTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "COPY"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);
			resultadoBuscaSimbolo2 = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+2]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				traducao = copyTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, linha_info->Tokens[i+2], resultadoBuscaSimbolo2->valor);
			}
			else
			{
				traducao = copyTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, linha_info->Tokens[i+2], resultadoBuscaSimbolo2->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "LOAD"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = addTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = addTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "STORE"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = storeTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = storeTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			}
			gravandoNoArquivo(traducao->traducao, saida);
		}
		else if (!strcmp(linha_info->Tokens[i], "INPUT"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			// if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valor);
			// }
			// else
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			// }
		}
		else if (!strcmp(linha_info->Tokens[i], "OUTPUT"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			// if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valor);
			// }
			// else
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			// }
		}
		else if (!strcmp(linha_info->Tokens[i], "C_INPUT"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			// if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valor);
			// }
			// else
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			// }
		}
		else if (!strcmp(linha_info->Tokens[i], "C_OUTPUT"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			// if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valor);
			// }
			// else
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			// }
		}
		else if (!strcmp(linha_info->Tokens[i], "S_INPUT"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			// if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valor);
			// }
			// else
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			// }
		}
		else if (!strcmp(linha_info->Tokens[i], "S_OUTPUT"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			// if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valor);
			// }
			// else
			// {
			// 	traducao = addTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
			// }
		}
		else if (!strcmp(linha_info->Tokens[i], "STOP"))
		{
			traducao = stopTraducao(traducao);
			
			gravandoNoArquivo(traducao->traducao, saida);
		}
	}

	fclose(saida);	
}


void declaravariaveis(char *nomeArquivoSaida, TS *TabelaSimbolos)
{
	TS* p;
	FILE *saida;

	saida = fopen(nomeArquivoSaida, "w");

 	for (p = TabelaSimbolos; p!= NULL; p = p->prox)
 	{
 		if (!strcmp(p->tipoDeDefinicao, "CONST"))
 		{
 			fprintf(saida, "define %s %d\n", p->nome, p->valorDeDefinicao);
 		}		
 	}

 	fprintf(saida, "section .bss\n");

 	for (p = TabelaSimbolos; p!= NULL; p = p->prox)
 	{
 		if (!strcmp(p->tipoDeDefinicao, "SPACE"))
 		{
 			fprintf(saida, "%s resw %d\n", p->nome, p->valorDeDefinicao);
 		}		
 	}

 	fprintf(saida, "section .text\nglobal _start\n_start:\n");

 	fclose(saida);

}





