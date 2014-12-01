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
	}

	fprintf(saida, "%s\n", p->traducao);

}

void gravandoNoArquivoOpcodes(linha_Instrucao *opcode, FILE *saidaDebug)
{
	linha_Instrucao *p, *final;

	final = opcode;

	for (p = opcode; p!=NULL; p=p->prox)
	{
		final = p;
	}

	for (p = final; p != opcode; p = p->ant)
	{
		fprintf(saidaDebug, "%s ", p->traducao);
	}

	fprintf(saidaDebug, "%s ", p->traducao);

}


//funcao principal do modulo que gera o cógigo objeto, porem ainda não resolve as pendencias
void Sintese (infoLinha *linha_info, char *nomeArquivoSaida, char *nomeSaidaBin, char *nomeSaidaDebug, TS *TabelaSimbolos)
{
	_Bool status;
	assembly *listaAssembly = NULL, *resultadoBuscaAssembly;
	TS *resultadoBuscaSimbolo, *resultadoBuscaSimbolo2;
	FILE *saida, *saidaBin, *saidaDebug;
	char *EhValido, *EhData;
	char convertido;
	char *argumentos;
	int valor;
	Traducao *traducao;

	traducao = (Traducao *)malloc(1*sizeof(Traducao));

	saida = fopen(nomeArquivoSaida, "a");
	saidaBin = fopen(nomeSaidaBin, "ab");
	saidaDebug = fopen(nomeSaidaDebug, "a");

	argumentos = (char *)malloc(100*sizeof(char));
	
    int i;
	for ( i = 0; i < linha_info->numTokens; ++i)
	{
		if (!strcmp(linha_info->Tokens[i], "ADD"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			strcpy(argumentos ,linha_info->Tokens[i+1]);

			if (!strcmp(linha_info->Tokens[i], "+"))
			{
				printf("eu vejo o +\n");
			}

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				// convertido = (char)resultadoBuscaSimbolo->valor;
				strcat(argumentos, "\0");
				traducao = addTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				// convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = addTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, saidaBin);
			}

			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
			
		}
		else if (!strcmp(linha_info->Tokens[i], "SUB"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = subTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = subTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "MULT"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				// convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = multTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				// convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = multTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "DIV"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = divTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = divTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "JMP"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = jmpTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor,saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = jmpTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao,saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "JMPN"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = jmpnTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = jmpnTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "JMPP"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = jmppTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = jmppTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "JMPZ"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = jmpzTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = jmpzTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "COPY"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);
			resultadoBuscaSimbolo2 = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+2]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				traducao = copyTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, linha_info->Tokens[i+2], resultadoBuscaSimbolo2->valor, saidaBin);
			}
			else
			{
				traducao = copyTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, linha_info->Tokens[i+2], resultadoBuscaSimbolo2->valorDeDefinicao, saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "LOAD"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = addTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = addTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "STORE"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			{
				// itoa(resultadoBuscaSimbolo->valor, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valor;
				traducao = storeTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valor, saidaBin);
			}
			else
			{
				// itoa(resultadoBuscaSimbolo->valorDeDefinicao, convertido, 10);
				convertido = (char)resultadoBuscaSimbolo->valorDeDefinicao;
				traducao = storeTraducao(traducao, linha_info->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao, saidaBin);
			}
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
		else if (!strcmp(linha_info->Tokens[i], "INPUT"))
		{
			resultadoBuscaSimbolo = buscaSimbolo(TabelaSimbolos, linha_info->Tokens[i+1]);

			// if (!strcmp(resultadoBuscaSimbolo->tipoDeDefinicao, "SPACE"))
			// {
			// 	traducao = Traducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valor);
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
			// 	traducao = Traducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valor);
			// }
			// else
			// {
			// 	traducao = outputTraducao(traducao, linha->Tokens[i+1], resultadoBuscaSimbolo->valorDeDefinicao);
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
			traducao = stopTraducao(traducao, saidaBin);
			
			gravandoNoArquivo(traducao->traducao, saida);
			gravandoNoArquivoOpcodes(traducao->opcode, saidaDebug);
		}
	}

	fclose(saida);	
}

void imprimeFuncaoEscreverInteiro(FILE *saida, FILE *saidaBin, FILE *saidaDebug)
{
	fprintf(saida, "enter 0,0 \n");
	fprintf(saida, "push eax \n");
	fprintf(saida, "mov esi,io_buf\n");
	fprintf(saida, "mov ebx,[EBP+8]\n");
	fprintf(saida, "mov ecx,10\n");
	fprintf(saida, "mov DWORD [esi],0\n");
	fprintf(saida, "mov DWORD [esi],0 \n");
	fprintf(saida, "mov DWORD [esi],0 \n");
	fprintf(saida, "_EIloop: \n");
	fprintf(saida, "mov edx,0 \n");
	fprintf(saida, "mov eax,ebx \n");
	fprintf(saida, "mov bl,[eax]\n");
	fprintf(saida, "idiv ecx\n");
	fprintf(saida, "add edx,30h \n");
	fprintf(saida, "mov BYTE [esi],dl \n");
	fprintf(saida, "mov ebx,eax \n");
	fprintf(saida, "inc esi \n");
	fprintf(saida, "cmp ebx,0 \n");
	fprintf(saida, "jne _EIloop \n");
	fprintf(saida, "mov eax,io_buf \n");
	fprintf(saida, "mov edx,esi \n");
	fprintf(saida, "dec esi \n");
	fprintf(saida, "_EIswap: \n");
	fprintf(saida, "mov bl,[eax]\n");
	fprintf(saida, "mov cl,[esi] \n");
	fprintf(saida, "mov [eax],cl  \n");
	fprintf(saida, "mov [esi],bl \n");
	fprintf(saida, "inc eax \n");
	fprintf(saida, "dec esi \n");
	fprintf(saida, "cmp eax,esi \n");
	fprintf(saida, "jl _EIswap \n");
	fprintf(saida, "mov BYTE [edx],0Ah  \n");
	fprintf(saida, "inc edx \n");
	fprintf(saida, "mov BYTE [edx],0 \n");
	fprintf(saida, "mov eax,4 \n");
	fprintf(saida, "mov ebx,1 \n");
	fprintf(saida, "mov ecx,io_buf \n");
	fprintf(saida, "mov edx,12 \n");
	fprintf(saida, "int 80h \n");
	fprintf(saida, "pop eax \n");
	fprintf(saida, "leave \n");
	fprintf(saida, "ret 4 \n");

}

void imprimeFuncaoLerInteiro(FILE *saida, FILE *saidaBin, FILE *saidaDebug)
{
	fprintf(saida, "enter 0,0 \n");
	fprintf(saida, "push eax \n");
	fprintf(saida, "mov eax,3\n");
	fprintf(saida, "mov ebx,0\n");
	fprintf(saida, "mov ecx,io_buf\n");
	fprintf(saida, "mov edx,12\n");
	fprintf(saida, "int 80h \n");
	fprintf(saida, "mov eax,io_buf \n");
	fprintf(saida, "mov ebx,0 \n");
	fprintf(saida, "mov ecx,0 \n");
	fprintf(saida, "_LIloop: \n");
	fprintf(saida, "mov bl,[eax]\n");
	fprintf(saida, "cmp bl,0Ah\n");
	fprintf(saida, "je _LIend \n");
	fprintf(saida, "cmp bl,0 \n");
	fprintf(saida, "je _LIend \n");
	fprintf(saida, "sub bl,30h \n");
	fprintf(saida, "imul ecx,ecx,10 \n");
	fprintf(saida, "add ecx,ebx \n");
	fprintf(saida, "inc eax \n");
	fprintf(saida, "jmp _LIloop \n");
	fprintf(saida, "_LIend: \n");
	fprintf(saida, "mov edx,[EBP+8] \n");
	fprintf(saida, "mov [edx],ecx \n");
	fprintf(saida, "pop eax \n");
	fprintf(saida, "leave  \n");
	fprintf(saida, "ret 4 \n");


}

void declaravariaveis(char *nomeArquivoSaida, char *nomeSaidaBin, char *nomeSaidaDebug, TS *TabelaSimbolos)
{
	TS* p;
	FILE *saida, *saidaBin, *saidaDebug;
	char percent = "%";

	saida = fopen(nomeArquivoSaida, "w");
	saidaBin = fopen(nomeSaidaBin, "wb");
	saidaDebug = fopen(nomeSaidaDebug, "w");

 	for (p = TabelaSimbolos; p!= NULL; p = p->prox)
 	{
 		printf("tipoDeDefinicao = %s\n", p->tipoDeDefinicao);
 		if (!strcmp(p->tipoDeDefinicao, "CONST"))
 		{
 			printf("entrei no if\n");
 			fprintf(saida, "%c", percent);

 			fprintf(saida, "define %s %d\n", p->nome, p->valorDeDefinicao);
 		}		
 	}
 	
 	fprintf(saida, "section .bss\n");
 	fprintf(saida, "io_buf resb 12\n");

 	for (p = TabelaSimbolos; p!= NULL; p = p->prox)
 	{
 		if (!strcmp(p->tipoDeDefinicao, "SPACE"))
 		{
 			fprintf(saida, "%s resw %d\n", p->nome, p->valorDeDefinicao);
 		}		
 	}

 	fprintf(saida, "section .text\nglobal _start\n_start:\n");
 	imprimeFuncaoLerInteiro(saida, saidaBin, saidaDebug);
 	imprimeFuncaoEscreverInteiro(saida, saidaBin, saidaDebug);

 	fclose(saida);
 	fclose(saidaBin);
 	fclose(saidaDebug);

}







