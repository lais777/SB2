#ifndef _SINTESE_H_
#define _SINTESE_H_

#include <stdio.h>
#include <stdlib.h>

#include "M_Passagem_Unica.h"
//#include "M_Dicionario.h"

extern struct infoLinha *linha_info;
extern struct TS *TabelaSimbolos;

void Sintese (infoLinha *linha_info, char *nomeArquivoSaida, TS *TabelaSimbolos);
void resolveIndefinicoes(char *nomeArquivoSaida, TS *TabelaSimbolos);
void declaravariaveis(char *nomeArquivoSaida, TS *TabelaSimbolos);

struct Assembly
{
    char * mnemonico;
    int codigo;
    int tamanho;
    struct Assembly *pa;
};

typedef struct Assembly assembly;

struct traducao
{
    struct linhaInstrucao *traducao;
    struct linhaInstrucao *opcode;
};

typedef struct traducao Traducao;

// struct linhaInstrucao
// {
//     char * traducao;
//     struct linhaInstrucao *prox;
//     struct linhaInstrucao *ant;
// };

// typedef struct linhaInstrucao linha_Instrucao;



#endif
