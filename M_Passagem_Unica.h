#ifndef _PASSAGEM_H_
#define _PASSAGEM_H_

#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int numTokens;
    int numChars;
    int numLinha;
    char * linha;
    char **Tokens;
}infoLinha;


struct pilhaPos
{
    int pos;
    int linha;
    struct pilhaPos * pilhaPosProx ;
};


typedef struct pilhaPos pilhaPos;

struct opLinha
{
   int linha;
   char * operacao;
   char ** args;
   int numArgs;
   int posInicial;
   struct opLinha* opLinhaProx;
};

typedef struct opLinha opLinha; 

struct ts 
{
    int numAparicoes;
    pilhaPos * pilhaDePosicoes;
    char *nome;
    int valor;
    int def;
    int valido;
    int offset;
    char * tipoDeDefinicao;
    int valorDeDefinicao;
    struct ts * prox;

};

typedef struct ts TS;


void resolvePassagemUnica(char *nomeEntrada, char *nomeSaida);



#endif







