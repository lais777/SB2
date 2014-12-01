#include <stdio.h>
#include "M_Dicionario.h"
#include "M_Sintese.h"
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
#define OPjg 0
#define OPjmp 0
#define OPje 0
#define OPeax 0
#define OPebx 0
#define OPint 0
#define OPsection 0
#define OPdata 0
#define OPspace 0 




/*struct linhaInstrucao
{
    char * instrucao;
    char * opcode;
    struct linhaInstrucao *prox;
};

typedef struct LinhaInstrucao linha_Instrucao;*/


void PrintTraducao(Traducao *t)
{
	printf("Entrei PrintTraducao \n");
  linha_Instrucao *aux1;
  linha_Instrucao *aux2;

  aux1 = t->traducao;
  aux2 = t->opcode;

  
  while(aux1 != NULL || aux2 != NULL)
  {
  	if(aux1 != NULL)
  	printf("COD  = %s\n",aux1->traducao);
    {
    	aux1 = aux1->prox;
    }

    if(aux2 != NULL)
    {
  		printf("OP  = %s\n",aux2->traducao);
  		aux2 = aux2->prox;
    }
  	
  }
printf("Sai PrintTraducao\n" );


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

Traducao * addTraducao(Traducao * linha, char * x, int op)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instrucao));
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPadd;
   int opReg = OPax;

   char *InstrucaoLinha  = (char *)malloc((13 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc( 20*sizeof(char));

   sprintf(InstrucaoLinha,"add ax , [%s]\0", x);
   sprintf(OPcodes,"66 03 05 %x 00 00 00\0",op); //VER O QUE FAZER AQUI SOBRE O [X]
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;



 return linha;
}

Traducao * jmpnTraducao(Traducao * linha, char * x, int op)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"cmp ax , 0\0");
   sprintf(OPcodes,"66 83 f8 00\0");
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((3 + strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"jl %s\0",x);
   sprintf(OPcodes2,"7c %x\0", op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;
}


Traducao * loadTraducao(Traducao * linha, char * x, int op)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"mov ax , [%s]\0", x);
   sprintf(OPcodes,"66 a3 %x 00 00 00\0", op);  //VER O QUE FAZER AQUI SOBRE O [X]
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;

}

Traducao * storeTraducao(Traducao * linha, char * x, int op)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"mov WORD [%s] , AX\0", x);
   sprintf(OPcodes,"66 a3 %x 00 00 00\0",op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}

Traducao * multTraducao(Traducao * linha, char * x, int  op)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((14 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"imul word [%s]\0", x);
   sprintf(OPcodes,"66 f7 2d %x 00 00 00\0" , op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}


Traducao * divTraducao(Traducao * linha, char * x, int op)
{

// linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc( 10 *sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"cwd ax\0");
   sprintf(OPcodes,"66 99\0");
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10+ strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"idiv WORD [%s]\0",x);//VERIFICAR SE PRECISA de OPCODE para WORD
   sprintf(OPcodes2,"66 f7 3d %x 00 00 00\0", op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

 
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;

}

Traducao * subTraducao(Traducao * linha, char * x, int op)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((11 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"sub ax , [%s]\0", x);
   sprintf(OPcodes,"66 2b 05 %x 00 00 00\0", op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD


   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}

Traducao * copyTraducao(Traducao * linha, char * x, int op, char * y, int opY)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc(7 *sizeof(char));
   char *OPcodes = (char *) malloc( 20 *sizeof(char));

   sprintf(InstrucaoLinha,"push dx\0");
   sprintf(OPcodes,"66 52\0");
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10 + strlen(y))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"mov dx, [%s]\0",y);
   sprintf(OPcodes2,"66 8b 15 %x 00 00 00\0", opY);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   /*======================== Terceira Linha ======================= */
   char *InstrucaoLinha3  = (char *)malloc((15 + strlen(x))*sizeof(char));
   char *OPcodes3 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha3,"mov WORD [%s], dx\0",x);
   sprintf(OPcodes3,"66 89 15 %x 00 00 00\0", op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha3);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes3);
   /*======================== FIM Terceira Linha ======================= */

	/*======================== Quarta Linha ======================= */
   char *InstrucaoLinha4  = (char *)malloc(7 *sizeof(char));
   char *OPcodes4 = (char *) malloc( 20 *sizeof(char));

   sprintf(InstrucaoLinha4,"pop dx\0");
   sprintf(OPcodes4,"66 5a\0");
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha4);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes4);
   /*======================== FIM Quarta Linha ======================= */



   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;
}

Traducao * jmppTraducao(Traducao * linha, char * x, int op)
{

// linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc( 10 *sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"cmp ax, 0\0");
   sprintf(OPcodes,"66 83 f8 00\0");//
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10+ strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(10*sizeof(char));

   sprintf(InstrucaoLinha2,"jg %s\0",x);//VERIFICAR SE PRECISA de OPCODE para WORD
   sprintf(OPcodes2,"7f %x\0", op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;

}


Traducao * jmpTraducao(Traducao * linha, char * x, int op)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((4 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(10*sizeof(char));

   sprintf(InstrucaoLinha,"jmp %s\0", x);
   sprintf(OPcodes,"eb %x\0", op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}


Traducao * jmpzTraducao(Traducao * linha, char * x, int op)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"cmp ax , 0\0");
   sprintf(OPcodes,"66 83 f8 00\0");
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((3 + strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"je %s\0",x);
   sprintf(OPcodes2,"74 %x\0", op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;
}

Traducao * stopTraducao(Traducao * linha)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc(9 *sizeof(char));
   char *OPcodes = (char *) malloc( 20 *sizeof(char));

   sprintf(InstrucaoLinha,"mov eax, 1\0");
   sprintf(OPcodes,"b8 01 00 00 00\0");
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc(10*sizeof(char));
   char *OPcodes2 = (char *) malloc( 20*sizeof(char));

   sprintf(InstrucaoLinha2,"mov ebx, 0\0");
   sprintf(OPcodes2,"bb 00 00 00 00\0");
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   /*======================== Terceira Linha ======================= */
   char *InstrucaoLinha3  = (char *)malloc(8*sizeof(char));
   char *OPcodes3 = (char *) malloc( 10*sizeof(char));

   sprintf(InstrucaoLinha3,"int 80h\0");
   sprintf(OPcodes3,"cd 80\0");
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha3);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes3);
   /*======================== FIM Terceira Linha ======================= */




   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;
}

Traducao * sectiondataTraducao(Traducao * linha)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc(15*sizeof(char));
   char *OPcodes = (char *) malloc( 3*sizeof(char));

   sprintf(InstrucaoLinha,"section .data\0");
   sprintf(OPcodes,"%d %d",OPsection, OPdata);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = NULL;

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}




Traducao * spaceTraducao(Traducao * linha, char * x, int op, char * y, int opY )
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((7 + strlen(x) + strlen(y))*sizeof(char));
   char *OPcodes = (char *) malloc( 4*sizeof(char));

   sprintf(InstrucaoLinha,"%s: space %s\0", x,y);
   sprintf(OPcodes,"%d",op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}

Traducao * sectiontextTraducao(Traducao * linha)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc(15*sizeof(char));
   char *OPcodes = (char *) malloc( 3*sizeof(char));

   sprintf(InstrucaoLinha,"section .text");
   sprintf(OPcodes,"%d %d",OPsection, OPdata);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = NULL;

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}



Traducao * constTraducao(Traducao * linha, char * x, char * y )
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   char * aux1 = "%";   
   char *InstrucaoLinha  = (char *)malloc((9 + strlen(x) + strlen(y))*sizeof(char));
   char *OPcodes = (char *) malloc( 4*sizeof(char));

   sprintf(InstrucaoLinha,"%sdefine %s %s",aux1, x,y);
   //sprintf(OPcodes,"%s",op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = NULL;

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}

// int main()
// {


// Traducao *teste = (Traducao *)malloc(sizeof(Traducao)); 
// //teste = addTraducao(teste, "LAIS","12");

// //printf("%s\n",rrteste->traducao->traducao);
//   // printf("%s\n", teste->opcode->traducao);

// //teste = jmpnTraducao(teste, "LAIS", "7");
// //PrintTraducao(teste);


// //teste = divTraducao(teste, "LAIS", "7");

// //teste = storeTraducao(teste, "LAIS", "7");
// //teste = multTraducao(teste, "LAIS", "7");

// //teste = subTraducao(teste, "LAIS", "7");


// //teste = copyTraducao(teste, "LAIS", "7", "LUIZ", "8");
// //teste = jmpzTraducao(teste, "LAIS", "7");
// //teste = stopTraducao(teste);
// //teste = sectiontextTraducao(teste);
// teste = constTraducao(teste, "LAIS", "LUIZ" );
// //teste = spaceTraducao(teste , "LAIS", "7", "LUIZ", "8");
// //teste = jmpTraducao(teste, "LAIS", "7");
// PrintTraducao(teste);


// return 0;

// }





