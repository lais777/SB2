#ifndef _DICIONARIO_H_
#define _DICIONARIO_H_

#include <stdlib.h>
#include "M_Sintese.h"


extern struct Traducao *linha;
// extern struct linha_Instrucao *listaAuxTraducao;


struct linhaInstrucao
{
    char * traducao;
    struct linhaInstrucao *prox;
    struct linhaInstrucao *ant;
};

typedef struct linhaInstrucao linha_Instrucao;

// struct traducao
// {
//     struct linhaInstrucao *traducao;
//     struct linhaInstrucao *opcode;
// };


// typedef struct linhaInstrucao linha_Instrucao;

// typedef struct traducao Traducao;


Traducao * addTraducao(Traducao * linha, char * x, int op);
Traducao * jmpnTraducao(Traducao * linha, char * x, int op);
Traducao * loadTraducao(Traducao * linha, char * x, int op);
Traducao * storeTraducao(Traducao * linha, char * x, int op);
Traducao * multTraducao(Traducao * linha, char * x, int op);
Traducao * divTraducao(Traducao * linha, char * x, int op);
Traducao * subTraducao(Traducao * linha, char * x, int op);
Traducao * copyTraducao(Traducao * linha, char * x, int op, char * y, int opY);
Traducao * jmppTraducao(Traducao * linha, char * x, int op);
Traducao * jmpTraducao(Traducao * linha, char * x, int op);
Traducao * jmpzTraducao(Traducao * linha, char * x, int op);
Traducao * stopTraducao(Traducao * linha);
Traducao * sectiondataTraducao(Traducao * linha);
Traducao * spaceTraducao(Traducao * linha, char * x, int op, char * y, int  opY );
Traducao * sectiontextTraducao(Traducao * linha);
Traducao * sectiontextTraducao(Traducao * linha);
Traducao * constTraducao(Traducao * linha, char * x, char * y );


//struct para guardar a macro
/*struct Opcode
{
    int codigo;
    struct Opcode *prox;
};

typedef struct Opcode opcode;*/

#endif