#ifndef _MACROS_H_
#define _MACROS_H_

#include <stdio.h>
#include <stdlib.h>

//struct para guardar as linhas do codigo da macro
struct LinhaMacro
{
    char *linha;
    struct LinhaMacro *pl;
    struct LinhaMacro *pla;
};

typedef struct LinhaMacro linha_Macro;

//struct para guardar a macro
struct Macro
{
    char *nome;
    linha_Macro *codigo;
    struct Macro *pm;
};

typedef struct Macro macro;

//funcao principal do modulo
void resolveMacro (char *, char *);



#endif