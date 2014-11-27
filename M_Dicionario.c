#include <stdio.h>
#include "M_Dicionario.h"
#include <stdlib.h>
#include <string.h>

#define OPadd 0
#define  OPcall 0
#define OPax 0
#define OPcmp 0
#define OPjg 0
#define OPjl 0 


/*struct linhaInstrucao
{
    char * instrucao;
    char * opcode;
    struct linhaInstrucao *prox;
};

typedef struct LinhaInstrucao linha_Instrucao;*/

linha_Instrucao* insereInstrucao(linha_Instrucao* linhaInstrucao, char *instrucao);
Traducao * addTraducao(Traducao * linha, char * x, char * op);
Traducao * jmpnTraducao(Traducao * linha, char * x, char * op);
void PrintTraducao(Traducao * teste);

int main()
{


Traducao *teste = (Traducao *)malloc(sizeof(Traducao)); 
teste = addTraducao(teste, "LAIS","12");

printf("%s\n",teste->traducao->traducao);
   printf("%s\n", teste->opcode->traducao);

teste = jmpnTraducao(teste, "LAIS", "7");


return 0;

}

void PrintTraducao(Traducao * teste)
{
    linha_Instrucao * aux;


}





linha_Instrucao* insereInstrucao(linha_Instrucao* linhaInstrucao, char *instrucao)
{
	linha_Instrucao* listaAux = (linha_Instrucao*)malloc(sizeof(linha_Instrucao));


	listaAux->traducao = (char *)malloc(strlen(instrucao)*sizeof(char));
	//listaAux->opcode = (char *)malloc(strlen(opcode)*sizeof(char));
    listaAux->prox = (linha_Instrucao*)malloc(sizeof(linha_Instrucao));
    listaAux->ant = (linha_Instrucao*)malloc(sizeof(linha_Instrucao));

	listaAux->traducao = instrucao;
	//listaAux->opcode = opcode;

	listaAux->prox = linhaInstrucao;
	if(linhaInstrucao != NULL)
	{
		linhaInstrucao->ant = listaAux;
	}

	listaAux->ant = NULL;

	return listaAux;
}

Traducao * addTraducao(Traducao * linha, char * x, char * op)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((13 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha,"add ax , [%s]", x);
   sprintf(OPcodes,"%d %d %s", opInst, opReg, op);
   printf("%s\n",InstrucaoLinha);
   printf("%s\n", OPcodes);

   linha->traducao = insereInstrucao(linha->traducao, InstrucaoLinha);
   linha->opcode = insereInstrucao(linha->opcode, OPcodes);



 return linha;
}

Traducao * jmpnTraducao(Traducao * linha, char * x, char * op)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha,"cmp ax , 0");
   sprintf(OPcodes,"%d %d , 0", OPcmp, OPax);
   printf("%s\n",InstrucaoLinha);
   printf("%s\n", OPcodes);

   linha->traducao = insereInstrucao(linha->traducao, InstrucaoLinha);
   linha->opcode = insereInstrucao(linha->opcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((3 + strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha2,"jl %s",x);
   sprintf(OPcodes2,"%d %s", OPjl, op);
   printf("%s\n",InstrucaoLinha2);
   printf("%s\n", OPcodes2);

   
   linha->traducao = insereInstrucao(linha->traducao, InstrucaoLinha2);
   linha->opcode = insereInstrucao(linha->opcode, OPcodes2);




 return linha;
}




