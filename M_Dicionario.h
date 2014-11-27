#ifndef _DICIONARIO_H_
#define _DICIONARIO_H_

#include <stdlib.h>

struct linhaInstrucao
{
    char * traducao;
    struct linhaInstrucao *prox;
    struct linhaInstrucao *ant;
};

typedef struct linhaInstrucao linha_Instrucao;

struct traducao
{
    struct linhaInstrucao *traducao;
    struct linhaInstrucao *opcode;
};


typedef struct linhaInstrucao linha_Instrucao;

typedef struct traducao Traducao;

//struct para guardar a macro
/*struct Opcode
{
    int codigo;
    struct Opcode *prox;
};

typedef struct Opcode opcode;*/

#endif