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

int * converteBinario(char * string)
{

   char *numAtual = (char *) malloc(3*sizeof(char));
   numAtual[2] = '\0';
   int numGrupos = 0;

   int fim = strlen(string);
   int i;
   int k = 0;
   int *Grupos;
    printf("String = %s", string);

   for(i = 0;i< fim;i++)
   {

      if(string[i] != ' ')
      {
         numAtual[k] = string[i];
         k++;        
      }  
        
      if(k == 2)
      {
         int num;
         num = atoi(numAtual);
         k = 0;
         numGrupos++;
      }
   }

   Grupos = (int *)malloc((numGrupos)*sizeof(int));
   
   numGrupos = 0;

   for(i = 0;i< fim;i++)
   {

      if(string[i] != ' ')
      {
         numAtual[k] = string[i];
         k++;
      }  
        
      if(k == 2)
      {
         int num;
         num = atoi(numAtual);
         k = 0;
         Grupos[numGrupos] = num;
         numGrupos++;
      }
   }

   
   return Grupos;
}

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

Traducao * addTraducao(Traducao * linha, char * x, int op,FILE *arq)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instrucao));
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
      
   int opInst = OPadd;
   int opReg = OPax;

   char *InstrucaoLinha  = (char *)malloc((13 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc( 20*sizeof(char));

   sprintf(InstrucaoLinha,"add ax , [%s]", x);
   
   sprintf(OPcodes,"66 03 05 %x 00 00 00",op); //VER O QUE FAZER AQUI SOBRE O [X]
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");
   
   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),7,arq );
   int i;

   for ( i = 0; i < 7; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");


   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;



 return linha;
}

Traducao * jmpnTraducao(Traducao * linha, char * x, int op,FILE *arq)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"cmp ax , 0");
   sprintf(OPcodes,"66 83 f8 00");
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");


   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),4,arq );

   int i;

   for ( i = 0; i < 4; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((3 + strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"jl %s",x);
   sprintf(OPcodes2,"7c %x", op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);
   strcat(OPcodes2, "\0");
   strcat(InstrucaoLinha2, "\0");



   Grupos =  converteBinario(OPcodes2);


   fwrite(Grupos, sizeof(int),2,arq );
   for ( i = 0; i < 2; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;
}


Traducao * loadTraducao(Traducao * linha, char * x, int op,FILE *arq)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"mov ax , [%s]", x);
   sprintf(OPcodes,"66 a3 %x 00 00 00", op);  //VER O QUE FAZER AQUI SOBRE O [X]
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");
   
   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),6,arq );

   int i;

   for ( i = 0; i < 6; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;

}

Traducao * storeTraducao(Traducao * linha, char * x, int op,FILE *arq)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"mov WORD [%s] , AX", x);
   sprintf(OPcodes,"66 a3 %x 00 00 00",op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),6,arq );
   int i;
   for ( i = 0; i < 6; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;


}

Traducao * multTraducao(Traducao * linha, char * x, int  op,FILE *arq)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((14 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"imul word [%s]", x);
   sprintf(OPcodes,"66 f7 2d %x 00 00 00" , op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),7,arq );
   
   int i;

   for ( i = 0; i < 7; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");   

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}


Traducao * divTraducao(Traducao * linha, char * x, int op,FILE *arq)
{

// linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc( 10 *sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"cwd ax");
   sprintf(OPcodes,"66 99");

   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),2,arq );

   int i;

   for ( i = 0; i < 2; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10+ strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"idiv WORD [%s]",x);//VERIFICAR SE PRECISA de OPCODE para WORD
   sprintf(OPcodes2,"66 f7 3d %x 00 00 00", op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);
   strcat(OPcodes2, "\0");
   strcat(InstrucaoLinha2, "\0");



   Grupos =  converteBinario(OPcodes2);

   fwrite(Grupos, sizeof(int),7,arq );


   for ( i = 0; i < 7; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
 
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;

}

Traducao * subTraducao(Traducao * linha, char * x, int op,FILE *arq)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((11 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"sub ax , [%s]", x);
   sprintf(OPcodes,"66 2b 05 %x 00 00 00", op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),7,arq );


   int i;

   for ( i = 0; i < 7; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   

   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}

Traducao * copyTraducao(Traducao * linha, char * x, int op, char * y, int opY,FILE *arq)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc(7 *sizeof(char));
   char *OPcodes = (char *) malloc( 20 *sizeof(char));

   sprintf(InstrucaoLinha,"push dx");
   sprintf(OPcodes,"66 52");
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");
   
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);
   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),2,arq );

   int i;

   for ( i = 0; i < 2; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10 + strlen(y))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"mov dx, [%s]",y);
   sprintf(OPcodes2,"66 8b 15 %x 00 00 00", opY);
   strcat(OPcodes2, "\0");
   strcat(InstrucaoLinha2, "\0");
   
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);


   Grupos =  converteBinario(OPcodes2);

   fwrite(Grupos, sizeof(int),7,arq );

   for ( i = 0; i < 7; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   /*======================== Terceira Linha ======================= */
   char *InstrucaoLinha3  = (char *)malloc((15 + strlen(x))*sizeof(char));
   char *OPcodes3 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha3,"mov WORD [%s], dx",x);
   sprintf(OPcodes3,"66 89 15 %x 00 00 00", op);
   strcat(OPcodes3, "\0");
   strcat(InstrucaoLinha3, "\0");
   
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   Grupos =  converteBinario(OPcodes3);

   fwrite(Grupos, sizeof(int),7,arq );

   

   for ( i = 0; i < 7; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha3);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes3);
   /*======================== FIM Terceira Linha ======================= */

	/*======================== Quarta Linha ======================= */
   char *InstrucaoLinha4  = (char *)malloc(7 *sizeof(char));
   char *OPcodes4 = (char *) malloc( 20 *sizeof(char));

   sprintf(InstrucaoLinha4,"pop dx");
   sprintf(OPcodes4,"66 5a");
   strcat(OPcodes4, "\0");
   strcat(InstrucaoLinha4, "\0");


   Grupos =  converteBinario(OPcodes4);

   fwrite(Grupos, sizeof(int),2,arq );


   for ( i = 0; i < 2; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha4);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes4);
   /*======================== FIM Quarta Linha ======================= */



   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;
}

Traducao * jmppTraducao(Traducao * linha, char * x, int op,FILE *arq)
{

// linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc( 10 *sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"cmp ax, 0");
   sprintf(OPcodes,"66 83 f8 00");//
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),4,arq );

   int i;

   for ( i = 0; i < 4; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10+ strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(10*sizeof(char));

   sprintf(InstrucaoLinha2,"jg %s",x);//VERIFICAR SE PRECISA de OPCODE para WORD
   sprintf(OPcodes2,"7f %x", op);
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);
   strcat(OPcodes2, "\0");
   strcat(InstrucaoLinha2, "\0");
   


   Grupos =  converteBinario(OPcodes2);

   fwrite(Grupos, sizeof(int),2,arq );

   for ( i = 0; i < 2; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;

}


Traducao * jmpTraducao(Traducao * linha, char * x, int op,FILE *arq)
{

   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   
   int opInst = OPload;
   int opReg = OPax;
   
   char *InstrucaoLinha  = (char *)malloc((4 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(10*sizeof(char));

   sprintf(InstrucaoLinha,"jmp %s", x);
   sprintf(OPcodes,"eb %x", op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),2,arq );

   int i;

   for ( i = 0; i < 2; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}


Traducao * jmpzTraducao(Traducao * linha, char * x, int op,FILE *arq)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc((10 + strlen(x))*sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"cmp ax , 0");
   sprintf(OPcodes,"66 83 f8 00");
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),4,arq );
   

   int i;

   for ( i = 0; i < 4; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((3 + strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"je %s",x);
   sprintf(OPcodes2,"74 %x", op);
   strcat(OPcodes2, "\0");
   strcat(InstrucaoLinha2, "\0");

   Grupos =  converteBinario(OPcodes2);

   fwrite(Grupos, sizeof(int),2,arq );
   

   for ( i = 0; i < 2; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;
}

Traducao * stopTraducao(Traducao * linha,FILE *arq)
{
  // linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc(9 *sizeof(char));
   char *OPcodes = (char *) malloc( 20 *sizeof(char));

   sprintf(InstrucaoLinha,"mov eax, 1");
   sprintf(OPcodes,"b8 01 00 00 00");
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),5,arq );

   int i;

   for ( i = 0; i < 5; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc(10*sizeof(char));
   char *OPcodes2 = (char *) malloc( 20*sizeof(char));

   sprintf(InstrucaoLinha2,"mov ebx, 0");
   sprintf(OPcodes2,"bb 00 00 00 00");
   strcat(OPcodes2, "\0");
   strcat(InstrucaoLinha2, "\0");
   

   Grupos =  converteBinario(OPcodes2);

   fwrite(Grupos, sizeof(int),5,arq );


   for ( i = 0; i < 5; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes2);
   /*======================== FIM Segunda Linha ======================= */

   /*======================== Terceira Linha ======================= */
   char *InstrucaoLinha3  = (char *)malloc(8*sizeof(char));
   char *OPcodes3 = (char *) malloc( 10*sizeof(char));

   sprintf(InstrucaoLinha3,"int 80h");
   sprintf(OPcodes3,"cd 80");
   strcat(OPcodes3, "\0");
   strcat(InstrucaoLinha3, "\0");

   Grupos =  converteBinario(OPcodes3);

   fwrite(Grupos, sizeof(int),2,arq );


   for ( i = 0; i < 2; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),7,arq );

   
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

   sprintf(InstrucaoLinha,"section .data");
   sprintf(OPcodes,"%d %d",OPsection, OPdata);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");
   
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

   sprintf(InstrucaoLinha,"%s: space %s", x,y);
   sprintf(OPcodes,"%d",op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");
   
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
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");
   

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
   //strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");
   
   //sprintf(OPcodes,"%s",op);  //VER O QUE FAZER AQUI SOBRE O [X] e sobre WORD
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = NULL;

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;

 return linha;



}


Traducao * outputTraducao(Traducao * linha, char * x, int op, FILE *arq )
{

// linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc( 10 *sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"push %s", x);
   sprintf(OPcodes,"68 %x 00 00 00", op);
   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int *Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),5,arq );
   

   int i;

   for ( i = 0; i < 5; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10+ strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"call _LerInteiro");//VERIFICAR SE PRECISA de OPCODE para WORD
   sprintf(OPcodes2,"66 f7 3d %x 00 00 00", op);
   strcat(OPcodes2, "\0");
   strcat(InstrucaoLinha2, "\0");


   Grupos =  converteBinario(OPcodes2);

   fwrite(Grupos, sizeof(int),7,arq );
   

   for ( i = 0; i < 7; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

 
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = NULL; //VERIFICAR DEPOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOIIIIIIIIIIIIIISSSSSS
   /*======================== FIM Segunda Linha ======================= */

   linha->traducao = listaAuxTraducao;
   linha->opcode = listaAuxOpcode;


 return linha;

}



Traducao * inputTraducao(Traducao * linha, char * x, int op,FILE *arq )
{

// linha_Instrucao* listaAux = (linha_Instrucao *)malloc(sizeof(linha_Instr//ucao));
   int opInst = OPadd;
   int opReg = OPax;
   
   linha_Instrucao* listaAuxTraducao = NULL;
   linha_Instrucao* listaAuxOpcode = NULL;
   

   /*======================== Primeira Linha ======================= */
   char *InstrucaoLinha  = (char *)malloc( 10 *sizeof(char));
   char *OPcodes = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha,"push %s", x);
   sprintf(OPcodes,"ff 35 %x 00 00 00", op);

   strcat(OPcodes, "\0");
   strcat(InstrucaoLinha, "\0");

   int * Grupos;

   Grupos =  converteBinario(OPcodes);

   fwrite(Grupos, sizeof(int),6,arq );

   int i;

   for ( i = 0; i < 6; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
   //printf("%s\n",InstrucaoLinha);
   //printf("%s\n", OPcodes);

   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha);
   listaAuxOpcode = insereInstrucao(listaAuxOpcode, OPcodes);
   /*======================== FIM Primeira Linha ======================= */

   /*======================== Segunda Linha ======================= */
   char *InstrucaoLinha2  = (char *)malloc((10+ strlen(x))*sizeof(char));
   char *OPcodes2 = (char *) malloc(20*sizeof(char));

   sprintf(InstrucaoLinha2,"call _EscreverInteiro");//VERIFICAR SE PRECISA de OPCODE para WORD
   sprintf(OPcodes2,"66 f7 3d %x 00 00 00",op);
   strcat(OPcodes2, "\0");
   strcat(InstrucaoLinha2, "\0");


   Grupos =  converteBinario(OPcodes2);

   fwrite(Grupos, sizeof(int),7,arq );


   for ( i = 0; i < 7; i++)
   {
      printf("%d ", Grupos[i]);
   }
   printf("\n");
   
   //printf("%s\n",InstrucaoLinha2);
   //printf("%s\n", OPcodes2);

 
   listaAuxTraducao = insereInstrucao(listaAuxTraducao, InstrucaoLinha2);
   listaAuxOpcode = NULL; //VERIFICAR DEPOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOIIIIIIIIIIIIIISSSSSS
   /*======================== FIM Segunda Linha ======================= */

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





