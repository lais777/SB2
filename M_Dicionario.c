#include <stdio.h>
#include "M_Dicionario.h"
#include <stdlib.h>
#include <string.h>

#define OPadd 0
#define OPcall 0
#define OPax 0
#define OPcmp 0
#define OPjg 0
#define OPjl 0
#define OPmov 0
#define OPload 0 
#define OPidiv 0
#define OPcwd 0
#define OPstore 0 
#define OPimul 0
#define OPsub 0
#define OPpush 0
#define OPpop 0
#define OPdx 0



/*struct linhaInstrucao
{
    char * instrucao;
    char * opcode;
    struct linhaInstrucao *prox;
};

typedef struct LinhaInstrucao linha_Instrucao;*/


void PrintTraducao(Traducao *t)
{
	printf("AAQQQUUIII \n");
  linha_Instrucao *aux1;
  linha_Instrucao *aux2;

  aux1 = t->traducao;
  aux2 = t->opcode;

  while(aux1 != NULL || aux2 != NULL)
  {
  	printf("COD  = %s\n",aux1->traducao);
  	printf("OP  = %s\n",aux2->traducao);
  	aux1 = aux1->prox;
    aux2 = aux2->prox;
  }



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
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instrucao));
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPadd;
   int opReg = OPax;

   char *InstrucaoLinha  = (char *)malloc((13 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha,"add ax , [%s]", x);
   sprintf(OPcodes,"%d %d %s", opInst, opReg, op); //VER O QUE FAZER AQUI SOBRE O [X]
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;



 return linha;
}

Traducao * jmpnTraducao(Traducao * linha, char * x, char * op)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha,"cmp ax , 0");
   sprintf(OPcodes,"%d %d 0", OPcmp, OPax);
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((3 + strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha2,"jl %s",x);
   sprintf(OPcodes2,"%d %s", OPjl, op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;
}


Traducao * loadTraducao(Traducao * linha, char * x, char * op)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(( 3 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha,"mov ax , [%s]", x);
   sprintf(OPcodes,"%d %d %s",OPmov , OPax, op);  //VER O QUE FAZER AQUI SOBRE O [X]
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;

}

Traducao * storeTraducao(Traducao * linha, char * x, char * op)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(( 3 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha,"mov WORD [%s] , AX ", x);
   sprintf(OPcodes,"%d %s %d",OPmov , op,  OPax);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}

Traducao * multTraducao(Traducao * linha, char * x, char * op)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((8 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(( 3 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha,"imul [%s]", x);
   sprintf(OPcodes,"%d %s",OPimul , op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}


Traducao * divTraducao(Traducao * linha, char * x, char * op)
{

// linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc( 10 *sizeof(char));
   char *OPcodes = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha,"cwd ax");
   sprintf(OPcodes,"%d %d", OPcwd, OPax);
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10+ strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha2,"idiv WORD [%s]",x);//VERIFICAR SE PRECISA de OPCODE para WORD
   sprintf(OPcodes2,"%d %s", OPidiv, op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;

}

Traducao * subTraducao(Traducao * linha, char * x, char * op)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((11 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha,"sub ax , [%s]", x);
   sprintf(OPcodes,"%d %d %s",OPsub,OPax, op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}

Traducao * copyTraducao(Traducao * linha, char * x, char * op, char * y, char * opY)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc(7 *sizeof(char));
   char *OPcodes = (char *) malloc( 4 *sizeof(char));

   sprintf(InstrucaoLinha,"push dx");
   sprintf(OPcodes,"%d %d", OPpush, OPdx);
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10 + strlen(y))*sizeof(char));
   char *OPcodes2 = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha2,"mov dx, [%s]",y);
   sprintf(OPcodes2,"%d %d %s", OPmov, OPdx, opY);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   /*======================== Terceira Linha ======================= */
   char *InstrucaoLinha3  = (char *)malloc((15 + strlen(x))*sizeof(char));
   char *OPcodes3 = (char *) malloc(( 4 + strlen(op))*sizeof(char));

   sprintf(InstrucaoLinha3,"mov WORD [%s], dx",x);
   sprintf(OPcodes3,"%d %s %d ", OPmov, op, OPdx);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha3);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes3);
   /*======================== FIM Terceira Linha ======================= */

	/*======================== Quarta Linha ======================= */
   char *InstrucaoLinha4  = (char *)malloc(7 *sizeof(char));
   char *OPcodes4 = (char *) malloc( 4 *sizeof(char));

   sprintf(InstrucaoLinha4,"pop dx");
   sprintf(OPcodes4,"%d %d", OPpop, OPdx);
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha4);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes4);
   /*======================== FIM Quarta Linha ======================= */



   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;
}



int main()
{


Traducao *teste = (Traducao *)malloc(sizeof(Traducao)); 
//teste = addTraducao(teste, "LAIS","12");

//printf("%s\n",teste->traducao->traducao);
  // printf("%s\n", teste->opcode->traducao);

//teste = jmpnTraducao(teste, "LAIS", "7");
//PrintTraducao(teste);


//teste = divTraducao(teste, "LAIS", "7");

//teste = storeTraducao(teste, "LAIS", "7");
//teste = multTraducao(teste, "LAIS", "7");

//teste = subTraducao(teste, "LAIS", "7");


teste = copyTraducao(teste, "LAIS", "7", "LUIZ", "8");

PrintTraducao(teste);


return 0;

}





