#ifndef _PRE_PROCESSAMENTO_H_
#define _PRE_PROCESSAMENTO_H_

#include <stdio.h>
#include <stdlib.h>

//struct para guardar as linhas do codigo da macro
struct Codigo
{
    char *linha;
    int posicao;
    struct Codigo *pl;
    struct Codigo *pla;
};

typedef struct Codigo codigo;


//struct para guardar os ifs
struct SE
{
    char *determinante;
    int linha;
    struct SE *pf;
};

typedef struct SE se;


//struct para guardar os EQUs
struct EQU
{
    char *tokenDeterminado;
    struct EQU *pt;
};

typedef struct EQU equ;

void resolvePreProcessamento(char *nomeArqEntrada, char *nomeArqSaida);



#endif