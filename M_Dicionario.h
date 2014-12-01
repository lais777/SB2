#ifndef _DICIONARIO_H_
#define _DICIONARIO_H_

#include <stdlib.h>
#include "M_Sintese.h"


extern struct Traducao *linha;
// extern struct linha_Instrucao *listaAuxTraducao;


// struct linhaInstrucao
// {
//     char * traducao;
//     struct linhaInstrucao *prox;
//     struct linhaInstrucao *ant;
// };

// typedef struct linhaInstrucao linha_Instrucao;

// struct traducao
// {
//     struct linhaInstrucao *traducao;
//     struct linhaInstrucao *opcode;
// };


// typedef struct linhaInstrucao linha_Instrucao;

// typedef struct traducao Traducao;

int * converteBinario(char * string);
Traducao * addTraducao(Traducao * linha, char * x, int op, FILE *arq);
Traducao * jmpnTraducao(Traducao * linha, char * x, int op, FILE *arq);
Traducao * loadTraducao(Traducao * linha, char * x, int op, FILE *arq);
Traducao * storeTraducao(Traducao * linha, char * x, int op,FILE *arq);
Traducao * multTraducao(Traducao * linha, char * x, int op,FILE *arq);
Traducao * divTraducao(Traducao * linha, char * x, int op,FILE *arq);
Traducao * subTraducao(Traducao * linha, char * x, int op,FILE *arq);
Traducao * copyTraducao(Traducao * linha, char * x, int op, char * y, int opY,FILE *arq);
Traducao * jmppTraducao(Traducao * linha, char * x, int op,FILE *arq);
Traducao * jmpTraducao(Traducao * linha, char * x, int op,FILE *arq);
Traducao * jmpzTraducao(Traducao * linha, char * x, int op,FILE *arq);
Traducao * stopTraducao(Traducao * linha,FILE *arq);
Traducao * sectiondataTraducao(Traducao * linha);
Traducao * spaceTraducao(Traducao * linha, char * x, int op, char * y, int  opY,FILE *arq );
Traducao * sectiontextTraducao(Traducao * linha);
Traducao * sectiontextTraducao(Traducao * linha);
Traducao * constTraducao(Traducao * linha, char * x, char * y );
Traducao * inputTraducao(Traducao * linha, char * x, int op, FILE *arq  );
Traducao * outputTraducao(Traducao * linha, char * x, int op, FILE *arq );


//struct para guardar a macro
/*struct Opcode
{
    int codigo;
    struct Opcode *prox;
};

typedef struct Opcode opcode;*/

#endif