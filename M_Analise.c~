#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NumInstr 14
#define NumDire 9

#include "M_Analise.h"
//#include "testeLuiz.h"




typedef struct 
{
    int NumLinha;
    int TipoErro;

}erros;


char ** instrucoes ;
char ** diretivas ;
// infoLinha * Linhas;
//TS * tabelaSims = NULL;
int * LinhaAtual, * NumErros, * posAtual;

int verificaSeDefiniToken(char * Token)
{

    int i = strlen(Token);
/*int j;
printf("strlen = %d \n",i);
for(j = 0; j<=i; j++)
{
    printf("j = %d c = %c\n", j,Token[j]);
}*/

    if(Token[i-1]==':')
    {
        
        return 1;
    }
    else
    {
        return 0;
    }
}

char * obtemNomeLabel(char * Token)
{
   int i;

    if(verificaSeDefiniToken(Token))
    { 
        int size = strlen(Token);
        char * stringOut = (char *)malloc(size*sizeof(char));

        for ( i = 0; i < size-1; i++)
        {
            stringOut[i] = Token[i];
        }

        stringOut[size] = '\0';

        return stringOut;
    }
    else
    {
        return Token;
    }
}









void ini(infoLinha * Linhas)
{
    instrucoes = (char **)malloc(NumInstr*sizeof(char *));
    diretivas = (char **) malloc(NumDire*sizeof(char *));
    //LinhaAtual = (int *)malloc(1*sizeof(int));
    //LinhaAtual[0] = 0;
    //Linhas = NULL;
    NumErros = (int *)malloc(1*sizeof(int));
    NumErros[0] = 0;

    //numSimbolos = (int *)malloc(1*sizeof(int));
    //numSimbolos[0] = 0;
    
    

    int i = 0;

    for(i = 0 ;i < NumInstr;i++)
    instrucoes[i] = (char *)malloc(10*sizeof(char ));

    for(i = 0 ;i < NumDire;i++)
    diretivas[i] = (char *)malloc(10*sizeof(char ));



  instrucoes[0] = "ADD"; //1
    instrucoes[1] = "SUB";// = 2,
    instrucoes[2] = "MULT";// = 3,
    instrucoes[3] = "DIV";// = 4,
    instrucoes[4] = "JMP";// = 5,
    instrucoes[5] = "JMPN";// = 6,
    instrucoes[6] = "JMPP";// = 7,
    instrucoes[7] = "JMPZ";// = 8,
    instrucoes[8] = "COPY";// = 9,
    instrucoes[9] = "LOAD";// = 10,
    instrucoes[10] = "STORE";// = 11,
    instrucoes[11] = "INPUT";// = 12,
    instrucoes[12] = "OUTPUT";// = 13,
    instrucoes[13] = "STOP";// = 14

    diretivas[0] = "SECTION";
    diretivas[1] = "SPACE";
    diretivas[2] = "CONST";
    diretivas[3] = "EQU";
    diretivas[4] = "IF";
    diretivas[5] = "MACRO";
    diretivas[6] = "END";
    diretivas[7] = "DATA";
    diretivas[8] = "TEXT";

  
    
    
    //simbolos = (ListaSim *)realloc(simbolos, 1*sizeof(ListaSim);
    
        


}

char * retiraEspaco(char * Token)
{
    char * stringOut;
//printf("AQUII 44444AAAA = %s\n",Token);
    int i, j = 0, tamanhoReal = 0;

    for(i = 0; i< strlen(Token);i++)
    {
        if(Token[i] != ' ')
            tamanhoReal++;
    }
//printf("AQUI 4444BBBBBBB\n");
    stringOut = (char *)malloc(tamanhoReal*sizeof(char));

    for(i = 0; i< strlen(Token);i++)
    {
        if(Token[i] != ' ') //&& (isdigit(Token[i]) || isalpha(Token[i]) || Token[i] == '_' || Token[i] == ':'|| Token[i] == '+' || Token[i] == '-'))
            {
                stringOut[j] = Token[i];
                j++;
                //printf("out = %c", stringOut[j]);
            }

    }

    //printf("AQUII 44444CCCCC\n");

    stringOut[j] = '\0';
    //printf("%s\n",stringOut );


    return stringOut;


}

char * maiuscula(char *string)
{
    int i;
    char *stringOut;
//printf("AQUII 3333AAAA\n");
    //string = retiraEspaco(string);
    stringOut = ( char *)malloc(strlen(string)*sizeof(char));
    
    for(i=0;i<strlen(string);i++)
    {
        stringOut[i]=toupper(string[i]);
    }
//printf("AQUII 3333\n");

    return stringOut;
}

int verificaSeInstrucao(char * Token)
{
 int i, j = 0;
 char * UPtoken = maiuscula(Token);
 //printf("AQUII 22222 AAAAA\n");
 //UPtoken = retiraEspaco(UPtoken);

    for( i = 0;i < NumInstr ; i++)
    {
        if(!strcmp(UPtoken,instrucoes[i]))
        {    
            j = i+1;
        }

    }

//printf("AQUII 22222\n");
 return j ;

}

int verificaSeDiretiva(char * Token)
{
 int i, j = 0;
 //printf("AQUII 55555AAAA\n");
 char * UPtoken = maiuscula(UPtoken);
   // UPtoken = retiraEspaco(Token);
    for( i = 0;i < NumDire ; i++)
    {
        if(!strcmp(UPtoken,diretivas[i]))
        {    
            j = i+1;
        }

    }

   // printf("AQUII 5555\n");


 return j ;

}

int verificaSeNumero( char *token)
{
   int i;

   //printf("AQUII 66666 AAAA\n");
   token = retiraEspaco(token);


//printf("%s\n", token);


   for ( i = 0; i < strlen(token); i++)
   {   //printf("%c", token[i]);
            
       //if(!(isdigit(token[i])||  (  (i == 0 && token[i] =='0') && ( i + 1 == 1) && token[i+1] == 'x'  ) || (token[i] == '.' && i < strlen(token) -1 ) ))
        if(!(isdigit(token[i])||(i == 0 && token[i] =='0') || ( i == 1) && token[i] == 'x'||(token[i] == '.' && i < strlen(token) -1 )))
            return 0;
   }
//printf("AQUII 66666\n");
   return 1;

}

void printErros(erros *errosInfo, int * NumErros)
{
   int i;

   int NumLinha;
    int TipoErro;


   for (i = 0; i < NumErros[0]; i++)
   {
     //printf("\n  Erro %d, Linha = %d, Tipo = %d", i, errosInfo[i].NumLinha, errosInfo[i].TipoErro);
   }



}



int verificaErroToken(char * Token, int posicao, int op )
{
   int i, size, ehInstrucao, ehDiretiva;
   char c;
   size = strlen(Token);

//printf("AQUII 777777\n");

   //printf("\nNumErros = %d, \nString = %s size = %d \n", NumErros[0], Token, size);
   
// printf("ENTREI = %s\n",Token );

 if(size == 1 && op == 1 )
 {
    if(Token[0] == '+' || Token[0] == '-' )
        return 1;
 }

   if(!verificaSeNumero( Token))  
   for (i = 0; i < size; i++)
   {    
        c = Token[i]; 
       
        if(size > 1)
            if(c =='+' ||c == '-')
                return 0;

       if(i == 0)
        {   
            
            if(!(isalpha(c) || c == '_') || isdigit(c) )
            {
                return 0;            
   
            }
            

        }
        else
        {
            if( i == size -1)
            {
                if(!( isalpha(c) || isdigit(c) || c == '_' || c == ':'))
                {
                    return 0;
                }   

        
            }
            else if(!( isalpha(c) || isdigit(c) || c == '_') )
            {
                if((c != '_') || (c != ':') ) 
                {
                    return 0;
                }
            }
       }


   }

  // printf("77777AAA\n");
return 1;
   
}



/*TS * insereLinhaTab (TS * tabSim,infoLinha Linha, int NumSim)
{
    int i = 0;



    for (i = 0; i < Linha.numTokens; i++)
    {
        
     tabSim = (TS *) realloc(tabSim, (NumSim+i+1)*sizeof(TS));

     tabSim[ NumSim+i+1].simbolo.nome = Linha.Tokens[i];


    }

    return tabSim;
}*/
/*
char * lerToken(FILE *ptr_file, int j)

Funcao para ler um token na linha atual

ARGUMENTOS: 
FILE *ptr_file: Ponteiro para um arquivo


SAIDA:
LINHA atual (String) 



*/
char * lerToken(FILE *ptr_file)
{   

    char * token = (char*)malloc(1*sizeof(char));
    char c;
    int i = 0;
    while((c = fgetc(ptr_file))!=' ')
    {    if ( c == '\n' || c ==-1)
        {
            break;
        }
         token[i] = c;
         token = realloc(token, (i+2)*sizeof(char));
         //printf("A%c", token[i]);
         i++;    
    }

    token[i] = '\0';
    
    return token;
}

//int verifica

/*
char * lerLinha(FILE *ptr_file, fpos_t  pos)

Função para ler a linha atual 

ARGUMENTOS: 
FILE *ptr_file: Ponteiro para um arquivo
fpos_t  pos: Posicao atual de leitura ou escrita no arquivo

SAIDA:
LINHA atual (String) 

*/


int lerLinha(FILE *ptr_file, fpos_t  pos,int * LinhaAtual ,infoLinha * Linhas)
{
	char c, cAntigo, *linha, *token;
    char ** tokensAUX;
    int i = 0, j = 0, numTokens = 0, tamanhoToken = 0;
    long int size;
    //printf("pos = %ld\n", ftell(ptr_file) );
    fpos_t  posAux;
    // Alocacao de espaco das strings
	linha = (char *)malloc(1*sizeof(char));// aloca espaço para a linha
    token = (char *)malloc(100*sizeof(char));// aloca espaço para o token
    fgetpos(ptr_file, &pos);
    // loop para ler a linha e guarda na variavel linha
    
    // alocar mais uma linha no ponteiro da struct
    //Linhas = (infoLinha *)realloc(Linhas, (LinhaAtual[0]+1)*sizeof(infoLinha));
    //Linhas[LinhaAtual[0]].numLinha = LinhaAtual[0]+1;



    
    //printf("\nLinha atual = %d\n", LinhaAtual[0]);
    LinhaAtual[0]++;

// Lendo a linha
    //printf("AAAAA\n");
    while((c = fgetc(ptr_file))!= '\n')
	{
        if(feof(ptr_file))
            return 1;

    if(c == -1)
    break;   
    //Se o caracter nao era espaco e agora eh, entao um token estava sendo lido
        if(i != 0)
        {
            if(cAntigo != ' ')
            {


                if( c == ' ')
                {

                    //Numero de tokens na linha
                    numTokens++;
                }
            }

        }
        cAntigo = c; 
        size = ftell(ptr_file);
     	linha[i] = c;
      //  printf("%c",c);
		i++;
        linha = (char *)realloc(linha,(i+1)*sizeof(char));
     
	}



    numTokens++;
    //marcacao do fim da string
    linha = (char *)realloc(linha,(i+1)*sizeof(char));	
    linha[i] = '\0';
  //  printf("BBBBBBB\n");
    Linhas->linha = (char *)malloc(strlen(linha)*sizeof(char));
    //printf("CCCCC\n" );
    linha = maiuscula(linha);
    Linhas->linha = linha;//retiraEspaco(linha);
    Linhas->numChars = i+1;
    //printf("%s\n", linha );
    //printf("\n Num Tokens = %d\n", numTokens);

	
	
     Linhas->Tokens = (char **)malloc(numTokens*sizeof(char *));
    
     j = 0;i = 0;
    // seguencia de instrucoes para ler token a token na linha
    c = fgetc(ptr_file);
    if(c != ' ' )
    fsetpos (ptr_file, &pos);
    //printf("\n");

    //Lendo todos os tokens da linha e guardando na estrutura
    for(i = 0;i<numTokens;i++)
    {
        token = lerToken(ptr_file); 
        
        Linhas->Tokens[i] = (char *)malloc(sizeof(token)*sizeof(char ));

        //token = maiuscula(token);
        

        Linhas->Tokens[i] = retiraEspaco(token);
        

      //  printf("\nTOKEN = %s tamanho = %d",token, strlen(token));
    }

    
    Linhas->numTokens = numTokens;

    fgetpos(ptr_file,&pos);
    //fazer a posicao voltar ao final da linha
    fsetpos (ptr_file, &pos);
   
    return 0;

}





int LerArquivo( FILE *ptr_file, fpos_t  pos,int * LinhaAtual, infoLinha * Linhas, erros *errosInfo, int * NumErros, TS * tabelaSims, int * numSimbolos )
{
    int NumLinhas = 0, i = LinhaAtual[0], j, k,numErrosAux, fim;
    int posicao = 1, m;
    // char c;
    // while((c = fgetc(ptr_file))!= -1)
    // {
    //     if(c == '\n')
    //         NumLinhas++; 

    // }
    // NumLinhas++;
    //printf("NumLinhas = %d\n",NumLinhas );
    //rewind(ptr_file);

    numErrosAux = NumErros[0];

    //for(i = 0;i <= NumLinhas;i++)
    //{
        fim = lerLinha(ptr_file, pos,LinhaAtual, Linhas);
        //Linhas[LinhaAtual[0]].tokens.
       // LinhaAtual[0]++;
        
      
      

    //}


    
    return fim;
}

FILE * argSemEspacos(FILE * ptr_file)
{

    FILE *semEspacos = fopen("semEspacos.txt", "w+");

    char c, cAntigo;
    int sai = 0; 
    c = ' ';
    cAntigo = c;

    while((c = fgetc(ptr_file)  ) != -1)
    {
        sai = 0;
        //if((cAntigo != ' ' || cAntigo != '\n')
          //  fputc(cAntigo, semEspacos);
        if(c != ' ' ||(cAntigo != ' ' && cAntigo != '\n' && c == ' ' ))
        fputc(c, semEspacos);
        
        while(c == ' ' || c == 9)
        {
            c = fgetc(ptr_file);
            sai = 1;
        }

        if(sai)
        fputc(c, semEspacos);


     cAntigo = c;
       
    }

    rewind(semEspacos);
    
    return semEspacos;
}

infoLinha * EscreveNumLinha(infoLinha * Linhas, int num)
{

    Linhas->numLinha = num;

    return Linhas;
}


int Analise (infoLinha *Linhas, FILE *ptr_file, TS * tabelaSims, int *numSimbolos)
{
    

    //verificacao quem irá fazer será a interface com o usuário
	// if(argc == 1)
	// {
	// 	printf("Digite o nome do arquivo no formato arg.txt ");
 //        return 0;
	// }
int fim;
    LinhaAtual = (int *)malloc(1*sizeof(int));
LinhaAtual[0] = 0;


   ini(Linhas);//INICIALIZAR AS VARIAVEIS GLOBAIS	

    




    

    // FILE *ptr_file;
    char buf[1000];
    char *linha;
	fpos_t  pos;
    long int size;
    //infoLinha * Linhas = NULL;
   // Linhas = NULL;
    erros *errosInfo = NULL;

    //Linhas.Tokens = NULL;
 
    int i, j;

    
    //verificacao que vai fazer á a interface com o usuário
 //    printf("\nNome do arquivo digitado: %s\n", argv[1]);

  //   ptr_file =fopen(argv[1],"r");

  //   if (!ptr_file)
  //   {
  //       return 1;
	 // }


    fgetpos (ptr_file, &pos);

    //colcoar essa funcao no modulo -p
    // FILE *semEspacos;
    //  semEspacos = argSemEspacos(ptr_file);




    fim = LerArquivo(ptr_file, pos, LinhaAtual, Linhas,errosInfo, NumErros, tabelaSims, numSimbolos);
    //printf("FFFFFFF\n");
        

   // fclose(ptr_file);
    //fclose(semEspacos);
    
    return fim;
    

}

TS* buscaTS (TS* lista, char *nome)
{
    TS* p;
    for (p = lista; p!= NULL; p = p->prox){
        if (!strcmp(p->nome, nome)){

        //    printf("nome = %s, nomeobtido = %s\n", nome, p->nome );
            return p;           
        }       
    }
    //printf("nao achei %s\n",nome );
    return NULL;
}



void printfPilhaPos(pilhaPos * lista)
{

  pilhaPos* p;
  int i =  0, j;

    for (p = lista; p!= NULL; p = p->pilhaPosProx){
         printf(" %d", p->pos );
        }
}

void printfOpLinha(opLinha * lista)
{
    opLinha * p;
    int i;
    
    for(p = lista;p!=NULL;p = p->opLinhaProx)
    {

        printf("op = %s, linha = %d, posInicial = %d, numArgs = %d", p->operacao, p->linha,p->posInicial , p->numArgs );
        for(i = p->posInicial;i< p->numArgs+p->posInicial;i++)
        {
            printf(" %s", p->args[i]);
        }
        printf("\n");
    }

}




void printfTS(TS * lista)
{

  TS* p;
  int i =  1, j;

    for (p = lista; p!= NULL; p = p->prox){
         printf("nome = %s, val = %d, def = %d, valido = %d, apari = %d, ", p->nome, p->valor, p->def, p->valido, p->numAparicoes);
         printf(" tipodef = %s, valordef = %d \n", p->tipoDeDefinicao, p->valorDeDefinicao );
         printfPilhaPos(p->pilhaDePosicoes);
         i++;
         printf("\n");
// for (j = 0; i < p->numAparicoes; ++i)
// {
//     /* code */
// }


        }
    

}


  
  
//diretivas[0] = "SECTION";
int verificaSeSection( char * Token)
{
  if(!strcmp(Token, "SECTION") )
        return 1;
    return 0;
 
}



    //diretivas[7] = "DATA";
    //diretivas[8] = "TEXT";


int verificaSeOpTipoSection(char * Token)
{

 if(!strcmp(Token, "DATA") || !strcmp(Token, "TEXT") )
        return 1;
    return 0;
   
}   

    //instrucoes[11] = "INPUT";// = 12,
    //instrucoes[12] = "OUTPUT";// = 13,

int verificaSeOpEntradaSaida(char * Token)
{
    if(!strcmp(Token, "INPUT") || !strcmp(Token, "OUTPUT") )
        return 1;
    return 0;

}




    //instrucoes[9] = "LOAD";// = 10,
    //instrucoes[10] = "STORE";// = 11,
int verificaSeOpMemoria(char * Token)
{

    if(!strcmp(Token, "LOAD") || !strcmp(Token, "STORE") )
        return 1;
    return 0;
}

int verificaSeMaisOuMenos(char * Token)
{

 if(!strcmp(Token, "+") || !strcmp(Token, "-") )
        return 1;
    return 0;   
}



    //instrucoes[0] = "ADD"; //1
    //instrucoes[1] = "SUB";// = 2,
    //instrucoes[2] = "MULT";// = 3,
    //instrucoes[3] = "DIV";// = 4,


int verificaSeOpAritmetica(char * Token)
{
   // printf("token = %s\n",Token );

    

  if(!strcmp(Token, "ADD") || !strcmp(Token, "SUB") ||!strcmp(Token, "MULT") || !strcmp(Token, "DIV"))
  {
    return 1;
  }
   


    return 0;
}



int verificaSeVariavel(char * Token)
{

    if(verificaSeNumero(Token) || verificaSeInstrucao(Token) || verificaSeDiretiva(Token) )
        return 0;
    if(strlen(Token) == 0 && (Token[0] == '+' || Token[0] == '-' ))
       return 0;

        return 1;
}



   // instrucoes[4] = "JMP";// = 5,
   // instrucoes[5] = "JMPN";// = 6,
   // instrucoes[6] = "JMPP";// = 7,
   // instrucoes[7] = "JMPZ";// = 8,
    

int verificaSeOpPulo(char * Token)
{
    
    if(!( !strcmp(Token, "JMPZ") ||!strcmp(Token, "JMPN") || !strcmp(Token, "JMP") || !strcmp(Token, "JMPP")  ))
        return 0;
    else
        return 1;


}



//instrucoes[8] = "COPY";// = 9,
  
int verificaSeOpCopy(char * Token)
{

   if(!strcmp(Token, "COPY"))
    return 1;

    return 0;
}

    
    //diretivas[1] = "SPACE";
    //diretivas[2] = "CONST";
    //diretivas[3] = "EQU";
    
int verificaSeOpAlocacaoMemoria(char * Token)
{
   if(!( !strcmp(Token, "SPACE") || !strcmp(Token, "CONST") || !strcmp(Token, "EQU") ))
        return 0;
    else
        return 1;
}

int verificaAritmeticaExtendida(infoLinha * linha)
{
    int numTokens = linha->numTokens;
    int i;
    int caso;
  


       if(numTokens >= 2)
       if(verificaSeDefiniToken(linha->Tokens[0]))
        {     
              if(!verificaSeOpAritmetica(linha->Tokens[1]))
              return 1; 
          caso = 0;
        }
        else
        {  

            if(!verificaSeOpAritmetica(linha->Tokens[0]))
                return 1;
            caso = 1;
        }

    //    printf("linha = %d caso %d,  numTokens = %d\n",linha->numLinha,caso, numTokens);

   if(caso)
   {
      if(numTokens > 4)
        return 1;
   }
   else
   {
      if(numTokens > 5)
        return 1;

   }

    for ( i = 0; i < numTokens; i++)
    {
    // printf(" i = %d %s\n", i, linha->Tokens[i]  );
     if(caso)// exemplo: ADD N + 1 + N2
     {
        if(i > 0)
        {

            if(i%2 == 0 && !verificaSeMaisOuMenos(linha->Tokens[i]))//CONTINUAR AAQQQQUIIII
            {//printf("A = %s \n", linha->Tokens[i]);
                return 1;
            }

            if(i%2 == 1 && !(verificaSeVariavel(linha->Tokens[i])  || verificaSeNumero(linha->Tokens[i])  ))
            {//printf("B = %s  \n", linha->Tokens[i]);
                return 1;
            }
        }

     }  
     else if(!caso)// exemplo: L1: ADD N +1 +N2
     {
        if(i > 1)
        {
           if(i%2 == 1 && !verificaSeMaisOuMenos(linha->Tokens[i]))//CONTINUAR AAQQQQUIIII
            {//printf("C = %s \n", linha->Tokens[i]);
                return 1;
            }

            if(i%2 == 0 && !(verificaSeVariavel(linha->Tokens[i]) || verificaSeNumero(linha->Tokens[i]) ))
            {//printf("D = %s \n", linha->Tokens[i]);
                return 1;
            }
        }

     } 

    }

return 0;

}






pilhaPos * inserePilhaPos(pilhaPos* p, int posicao, int linha)
{
    pilhaPos* pilhaAUX = (pilhaPos*) malloc(sizeof(pilhaPos));

    
    pilhaAUX->pos = posicao;
    pilhaAUX->linha = linha;
    pilhaAUX->pilhaPosProx = p;

    return pilhaAUX;

}



void EscreveArgErro(int linha, int TipoErro)
{

    FILE *argErros = fopen("erros.txt", "a");
    
    if(TipoErro == 1)
    {
        printf("erro lexico linha %d\n",linha );
    }

    if(TipoErro == 2)
    {
        printf("erro sintatico linha %d\n",linha );
    }
    if(TipoErro == 3)
    {
        printf("erro semantico linha %d\n",linha );
    }



    fprintf(argErros, "%d %d |", TipoErro, linha);
    fclose(argErros);
}

int verificaSeOpAritmeticaLabel(infoLinha * linha)
{
  if(linha->numTokens >= 2)
  {
       if(verificaSeDefiniToken(linha->Tokens[0]))
        {     
              if(!verificaSeOpAritmetica(linha->Tokens[1]))
              return 1; 
          
        }
        else
        {  

            if(!verificaSeOpAritmetica(linha->Tokens[0]))
                return 1;
           
        }
  }
        return 0;
}


// int obtemOffsetOpAritmeticaExtendida(infoLinha *linha)
// {
//   return atoi(linha->Tokens[linha->numTokens -1]);

// }

int retornaOffsetAritmetico(infoLinha * linha)
{
 int i;
 int ini = -1;
 int temOffset =0;
 int sinal = 0;
 int offset = 0;
 int numTokens = linha->numTokens;
 int posNum = 0;
 if(numTokens >= 3)
 {
    if(verificaSeOpAritmetica(linha->Tokens[0]))
        ini = 0;
    if(verificaSeOpAritmetica(linha->Tokens[1]))
        ini = 1;
 }

//printf("AQUI 333\n");
if(ini != -1)
 for ( i = ini; i < numTokens; i++)
 {
    if(verificaSeNumero(linha->Tokens[i]))
        posNum = i;

     if(i < numTokens -1)
     {
        if(verificaSeMaisOuMenos(linha->Tokens[i]))
        {   temOffset = 1;
            if(!strcmp(linha->Tokens[i],"+"))
                sinal = 1;
            else if(!strcmp(linha->Tokens[i],"-"))
                sinal = -1;
        }
     }
 }
//printf("AQUII 444\n");
 if(temOffset)
  {
    offset = sinal*atoi(linha->Tokens[posNum]);
   // printf("%s offset = %d\n",linha->linha, offset );
    return offset;
  }




 return 0;


}

void atualizaTS(infoLinha *linha, TS * lista,char * nome, int pos, int Numlinha)
{

   TS * listaAUX = (TS*)malloc(sizeof(TS));

   int definido = verificaSeDefiniToken(nome);
   int op = 0;
   char *nomeLabel;
   nomeLabel = (char *)malloc(strlen(nome)*sizeof(char));
   nomeLabel = obtemNomeLabel(nome);
  // printf("nome = %s, nomeLabel = %s\n", nome, nomeLabel );
//   int ap = contaNumAparicoes(lista);
        
//printf("ap1 = %d\n",ap );
   if(verificaSeOpAritmeticaLabel(linha))
    op = 1;

   if(!verificaErroToken(nomeLabel,pos, op))
        EscreveArgErro(Numlinha, 1);

//printf("\nATUALIZA %s\n", nomeLabel ); 
   listaAUX = buscaTS(lista, nomeLabel);

   if(verificaSeMaisOuMenos(nome))
   {
    return;
   }
   if(definido)
   {
//printf("DEFINI ATUALIZA \n");
//printf("nome = %s\n", nome );

    //printf("BBBBBBB\n ");
    //listaAUX->numAparicoes++;
    //listaAUX->pilhaDePosicoes = (int *)realloc(listaAUX->pilhaDePosicoes, (listaAUX->numAparicoes)*sizeof(int));
    //listaAUX->pilhaDePosicoes[listaAUX->numAparicoes] = pos;
    //printf("CCCCC\n");
    listaAUX->valor = pos;
    //printf("AAAAA\n");
    listaAUX->def = 1;

    if(linha->numTokens >=2)
     {
        //printf("AQUI 1 = %s\n", linha->Tokens[1]);
         if(!strcmp(linha->Tokens[1], "SPACE"))
         {

            if(linha->numTokens == 3)
            {
             //   printf("AAAAA22222\n");
                listaAUX->tipoDeDefinicao = (char*)malloc(strlen("SPACE")*sizeof(char));
                listaAUX->tipoDeDefinicao = "SPACE";
                listaAUX->valorDeDefinicao = atoi(linha->Tokens[2]);
               // printf("BBBBB222\n");

            }
            else if(linha->numTokens == 2)
            {
                //printf("CCCCC2222\n");

                listaAUX->tipoDeDefinicao = (char*)malloc(strlen("SPACE")*sizeof(char));
                listaAUX->tipoDeDefinicao = "SPACE";
                //printf("AQUI 222 %s\n", linha->Tokens[1]);
                listaAUX->valorDeDefinicao = 0;
                  //   printf("DDDDDD2222\n");

            }

         }
         else if(!strcmp(linha->Tokens[1], "CONST")) 
             {
                    //printf("AAAA 1111\n");
                    listaAUX->tipoDeDefinicao = (char*)malloc(strlen("CONST")*sizeof(char));
                    listaAUX->tipoDeDefinicao = "CONST";
                    listaAUX->valorDeDefinicao = atoi(linha->Tokens[2]);
                  //  printf("BBBB 1111\n");
             }
             else if(!strcmp(linha->Tokens[1], "EQU"))
             {

                //printf("AAAA 2222\n");
                    listaAUX->tipoDeDefinicao = (char*)malloc(strlen("EQU")*sizeof(char));
                    listaAUX->tipoDeDefinicao = "EQU";
                    listaAUX->valorDeDefinicao = atoi(linha->Tokens[2]);
                    //printf("BBBB 2222\n");

             }
             else
         {

                listaAUX->tipoDeDefinicao = (char*)malloc(strlen("LABEL")*sizeof(char));
                listaAUX->tipoDeDefinicao = "LABEL";
                listaAUX->valorDeDefinicao = pos;
         }
     }
    //printf("AAAAABBBBB\n");
    //listaAUX->valido = 1;//MODIFICAR AQUI DEPOIS
    //printf("AAAAACCCCC\n");
    }
    else
    {
     //   printf("NAO DEFINI ATUALIZA \n"); 
    listaAUX->numAparicoes++;
//    if(verificaAritmeticaExtendida(linha))
    //listaAUX=>def
    //printf("INSERE %s pos = %d \n", nomeLabel, pos);
    //printf("nome = %s, val = %d, def = %d, valido = %d, apari = %d, ", listaAUX->nome, listaAUX->valor, listaAUX->def, listaAUX->valido, listaAUX->numAparicoes);
    //printfPilhaPos(listaAUX->pilhaDePosicoes);
  //  printf("AQUI222 \n");
    if(listaAUX->def != 1)
    listaAUX->offset = retornaOffsetAritmetico(linha);
    

    //printfTS(listaAUX); 
  //  printf("%s insere %d \n", nomeLabel,pos );
    listaAUX->pilhaDePosicoes = inserePilhaPos(listaAUX->pilhaDePosicoes, pos, Numlinha);
  //printf("\n");
  //   printfPilhaPos(listaAUX->pilhaDePosicoes);
    
    //listaAUX->valor = -1;
    //listaAUX->def = 0;
    //listaAUX->valido = 1;//MODIFICAR AQUI DEPOIS

    }
  //     ap = contaNumAparicoes(lista);
  //     int ap2= contaNumAparicoes(listaAUX);
  //printf("ap2 = %d,ap3 = %d\n",ap, ap2 ); 


}




TS* insereTS(infoLinha *linha, TS* listaTS,  char *nome, int pos, int Numlinha)   
{
    TS* listaAUX = (TS*) malloc(sizeof(TS));
//    printf("\nINSERE %s\n", nome ); 
    TS* listaAUXJaExiste = buscaTS(listaTS, nome);
    char *nomeLabel;
    pilhaPos *pilha = NULL;
    int op = 0;
    nomeLabel = (char *)malloc(strlen(nome)*sizeof(char));
    nomeLabel = obtemNomeLabel(nome);
     
    //nomeLabel = obtemNomeLabel(nome);
    //printf("Aqui\n");

    int defini = verificaSeDefiniToken(nome);
    //printf("definido = %d string = %s",definido, nome);
    //printf("defini = %d, nome = %s, nomeLabel = %s\n",defini, nome, nomeLabel);
    //if(!(!s!strcmp(linha->Tokens[1], "EQU")trcmp(nomeLabel,"+") && !strcmp(nomeLabel,"-")))
if(verificaSeOpAritmeticaLabel(linha))
    op = 1;

    if(!verificaErroToken(nomeLabel,pos,op))
        EscreveArgErro(Numlinha,1);


if(verificaSeMaisOuMenos(nome))
    return listaTS;

    if(defini)
    {
     
    //printf("DEFINI INSERE \n"); 
     listaAUX->pilhaDePosicoes = pilha;
     listaAUX->nome = nomeLabel;
     listaAUX->valor = pos;
     listaAUX->def = 1;
     listaAUX->valido = verificaErroToken(nomeLabel,pos,op);//MODIFICAR AQUI DEPOIS
     
     if(linha->numTokens >=2)
     {
        //printf("AQUI = %s\n", linha->Tokens[1]);
         if(!strcmp(linha->Tokens[1], "SPACE"))
         {

            if(linha->numTokens == 3)
            {
                //printf("AAAA\n");
                listaAUX->tipoDeDefinicao = (char*)malloc(strlen("SPACE")*sizeof(char));
                listaAUX->tipoDeDefinicao = "SPACE";
                listaAUX->valorDeDefinicao = atoi(linha->Tokens[2]);
              //  printf("BBBB\n");

            }
            else if(linha->numTokens == 2)
            {
            // printf("CCCCC\n");
                listaAUX->tipoDeDefinicao = (char*)malloc(strlen("SPACE")*sizeof(char));
                listaAUX->tipoDeDefinicao = "SPACE";
                listaAUX->valorDeDefinicao = 0;

             //    printf("DDDDD\n");
            }


         }
         else if(!strcmp(linha->Tokens[1], "CONST")) 
         {
            //    printf("AAAA 1111\n");
                listaAUX->tipoDeDefinicao = (char*)malloc(strlen("CONST")*sizeof(char));
                listaAUX->tipoDeDefinicao = "CONST";
                listaAUX->valorDeDefinicao = atoi(linha->Tokens[2]);
          //      printf("BBBB 1111\n");
         }
         else if(!strcmp(linha->Tokens[1], "EQU"))
         {

            //printf("AAAA 2222\n");
                listaAUX->tipoDeDefinicao = (char*)malloc(strlen("EQU")*sizeof(char));
                listaAUX->tipoDeDefinicao = "EQU";
                listaAUX->valorDeDefinicao = atoi(linha->Tokens[2]);
              //  printf("BBBB 2222\n");

         }
         else
         {

                listaAUX->tipoDeDefinicao = (char*)malloc(strlen("LABEL")*sizeof(char));
                listaAUX->tipoDeDefinicao = "LABEL";
                listaAUX->valorDeDefinicao = pos;
         }
     }
     

     listaAUX->numAparicoes = 1;

     listaAUX->prox = listaTS;

    }
    else
    {

        //printf("NAO DEFINI INSERE \n");
        //printf("INSERE %s pos = %d \n", nomeLabel, pos); 
        //printf("nome = %s, val = %d, def = %d, valido = %d, apari = %d, ", listaAUX->nome, listaAUX->valor, listaAUX->def, listaAUX->valido, listaAUX->numAparicoes);
        //printfPilhaPos(listaAUX->pilhaDePosicoes);
    //printf("%s insere %d \n", nomeLabel,pos );
        listaAUX->pilhaDePosicoes = inserePilhaPos(pilha, pos,Numlinha);
//        printfPilhaPos(listaAUX->pilhaDePosicoes);
    //printf("\n");    
        //printfTS(listaAUX);
        listaAUX->nome = nome;
        listaAUX->valor = -1;
    //    printf("AQUI \n");
    if(listaAUX->def != 1)
    listaAUX->offset = retornaOffsetAritmetico(linha);
    

    //if(listaAUX->def != 0 && listaAUX->def != 1)
    //printf("%s DEF = %d\n", linha->linha, listaAUX->def);

        listaAUX->valido = verificaErroToken(nome,pos,op);//MODIFICAR AQUI DEPOIS
        listaAUX->numAparicoes = 2;
        listaAUX->prox = listaTS;

   }

   //int ap = contaNumAparicoes(listaAUX);
   // printf("ap = %d\n",ap ); 
        
        return listaAUX;
    //}

}




int contaSimbolosTS(TS *lista)
{
    TS * p;
    int i = 0;

    for (p = lista; p!= NULL; p = p->prox){
        
            i++;           
        
    }
    return i;
}




int verificaSections(infoLinha *linha)
{

    //printf("TOKEN[0] = %s, TOKEN[1] = %s\n",linha->Tokens[0], linha->Tokens[1] );
    //if(linha->numTokens == 2)
    //{
      //  printf("AQUI 1");
        if(!strcmp( maiuscula(linha->Tokens[0]), "SECTION")){
        //    printf("AQUI 2");
            if(!strcmp( maiuscula(linha->Tokens[1]), "DATA") ||!strcmp( maiuscula(linha->Tokens[1]), "TEXT")){
          //      printf("AQUI 3 retorno 1 nao soma\n");
              return 1;
            }
        }
    //}


   return 0;
}



TS * retornaTabelaSimbolos(infoLinha * linha, TS * tabelaSims,int  posicao) //int * numSim)
{   

    int k, m, numSimbolosDefinidos;
    numSimbolosDefinidos = contaSimbolosTS(tabelaSims);
    TS *listaAUX;
    int pos = posicao;
    

    for(k = 0; k < linha->numTokens; k++)
        {
         //   printf("token = %s\n", linha->Tokens[k] );
            char *nomeLabel;
            nomeLabel = (char *)malloc(strlen(linha->Tokens[k])*sizeof(char));

            nomeLabel = obtemNomeLabel(linha->Tokens[k]);
    
            //printf("ABCD\n");
            
            if(!verificaSeInstrucao(linha->Tokens[k]) && !verificaSeDiretiva(linha->Tokens[k]) && !verificaSeNumero(linha->Tokens[k]) && !verificaSeMaisOuMenos(linha->Tokens[k]) &&  strcmp(linha->Tokens[k], ","))
            {
                //printf("ABCD2\n");

                //listaAUX = buscaTS(tabelaSims, linha->Tokens[k]);
                listaAUX = buscaTS(tabelaSims, nomeLabel);
                //printf("AQUI1");
                if(listaAUX == NULL)
                {   
                    //printf(" insere TOKEN[k] = %s\n", nomeLabel );
                    tabelaSims = insereTS( linha, tabelaSims,  linha->Tokens[k], pos, linha->numLinha);
                }
                else
                {
                    //printf(" atualiza TOKEN[k] = %s\n", linha->Tokens[k] );
                    atualizaTS(linha, tabelaSims,  linha->Tokens[k], pos, linha->numLinha);
                }

                //printf("AAA111\n");
                //numSim[0]++;
                //insere(TS* listaTS, int numAparicoes, int *pilhaDePosicoes, char *nome, int valor, int def, int valido)   
                //tabelaSims =  insere( tabelaSims, linha->Tokens[k],posicao, 1,numSim );
                //printf("ABCD3\n");
                //printTabelaSims( tabelaSims,numSimbolos);
                //posicao[0]++;
                
            }
           if(!(verificaSections(linha) || !strcmp("SPACE",linha->Tokens[k] )|| verificaSeDefiniToken(linha->Tokens[k])|| verificaSeMaisOuMenos(linha->Tokens[k]) || !strcmp(linha->Tokens[k],",") || verificaSeNumero(linha->Tokens[k])))
            pos++;   
        }

 // printf("andei = %d\n",pos );
    return  tabelaSims; 

}

int verificaoInicial( infoLinha * linha)
{
    //printf("A\n");
    int i;
    if(linha->numTokens >= 2)
    { 
        if(verificaSections(linha))
        {
            return 0;
        }
        else if (verificaSeDefiniToken(linha->Tokens[0]) )
        {
         //  if(verificaSeInstrucao(linha->Tokens[1]) || verificaSeOpAlocacaoMemoria()) //||  verificaSeDiretiva(linha->Tokens[1]))
           //{
            for ( i = 1; i < linha->numTokens; i++)
            {
                if (verificaSeDefiniToken(linha->Tokens[i]) )
                    return -1;

            }

            //printf("A\n");
            return 1;
           //}
           //else
           //return -1;
        }
        else if(verificaSeInstrucao(linha->Tokens[0]))
        {
           return 0;

        }
    }


    return -1;


}

  
  



    // instrucoes[0] = "ADD"; //1
    // instrucoes[1] = "SUB";// = 2,
    // instrucoes[2] = "MULT";// = 3,
    // instrucoes[3] = "DIV";// = 4,
void AnaliseSintaticaOpAritmetica(infoLinha * linha, int posInicial,TS * tabelaSims)
{
   int i = posInicial;
   int numTokens = linha->numTokens;
   TS *listaAUX;

   if( verificaSeOpAritmetica(  linha->Tokens[posInicial]))
   {
        if( numTokens - i < 2)
        {
            //printf("AnaliseSintaticaOpAritmetica A\n");
            EscreveArgErro(linha->numLinha,2);        
        }
        else if(verificaAritmeticaExtendida( linha))
            EscreveArgErro(linha->numLinha,2);
   }

}



//instrucoes[9] = "LOAD";// = 10,
//instrucoes[10] = "STORE";// = 11,
    
void AnaliseSintaticaOpMemoria(infoLinha * linha, int posInicial,TS * tabelaSims)
{

    int i = posInicial;
   int numTokens = linha->numTokens;
   TS *listaAUX;
  // listaAUX = buscaTS(tabelaSims, linha->Tokens[i+1]);

   if(verificaSeOpMemoria(linha->Tokens[i]))
   {

        if( numTokens - i != 2)
        {
           // printf("AnaliseSintaticaOpMemoria A\n");
            EscreveArgErro(linha->numLinha,2);        
        }
        if(!verificaSeVariavel(linha->Tokens[i+1]))
        {  // printf("AnaliseSintaticaOpMemoria B\n");
            EscreveArgErro(linha->numLinha,2);        
        }

   }

}

    // instrucoes[4] = "JMP";// = 5,
    // instrucoes[5] = "JMPN";// = 6,
    // instrucoes[6] = "JMPP";// = 7,
    // instrucoes[7] = "JMPZ";// = 8,

void AnaliseSintaticaOpPulo(infoLinha * linha, int posInicial,TS * tabelaSims)
{

    int i = posInicial;
   int numTokens = linha->numTokens;
   TS *listaAUX;
   
//listaAUX = buscaTS(tabelaSims, linha->Tokens[i+1]);
   if( verificaSeOpPulo(linha->Tokens[i]))
   {
         if( numTokens - i != 2)
        {
            //printf("AnaliseSintaticaOpPulo A\n");
            EscreveArgErro(linha->numLinha,2);        
        }
        else
        {
            listaAUX = buscaTS(tabelaSims, linha->Tokens[i+1]);
                 

        }
        if(!verificaSeVariavel(linha->Tokens[i+1]))
        {   printf("AnaliseSintaticaOpPulo B\n");
            EscreveArgErro(linha->numLinha,2);        
        }

        

   }



}


    // instrucoes[11] = "INPUT";// = 12,
    // instrucoes[12] = "OUTPUT";// = 13,


void AnaliseSintaticaOpEntradaSaida(infoLinha * linha, int posInicial,TS * tabelaSims)
{
 
    int i = posInicial;
   int numTokens = linha->numTokens;

   if( verificaSeOpEntradaSaida (linha->Tokens[i]))
   {
        if( numTokens - i != 2)
        {
            //printf("AnaliseSintaticaOpEntradaSaida A\n");
            EscreveArgErro(linha->numLinha,2);        
        }

        if(!verificaSeVariavel(linha->Tokens[i+1]))
        {   //printf("AnaliseSintaticaOpEntradaSaida B\n");
            //EscreveArgErro(linha->numLinha,2);        
        }

   }

}

int contaSomaPos(infoLinha * linha)
{
    int numTokens = linha->numTokens;
    int anda = 0;
    int i;
    int flagDEF= 0;

    if(verificaSeDefiniToken(linha->Tokens[0]))
        flagDEF = 1;

//printf("%s ",linha->linha );
   for ( i = flagDEF; i < numTokens; i++)
   {
       
        if(!strcmp(linha->Tokens[i], "SPACE"))
        {
                 if(i+1 <numTokens)
                 {
                    if(verificaSeNumero(linha->Tokens[i+1]))
                    {
                        //printf("BBBB  anda = %d\n", atoi(linha->Tokens[i+1]));
                        return atoi(linha->Tokens[i+1]);
                    }
                 }
                 else
                 return 1;   

        }
        if(!(verificaSeMaisOuMenos(linha->Tokens[i])))
        if(strcmp(linha->Tokens[i], ","))
        if( !strcmp(linha->Tokens[i], "CONST") ||verificaSeVariavel(linha->Tokens[i]) || verificaSeInstrucao(linha->Tokens[i]))
        {
    //        printf("%s\n", linha->Tokens[i]);
           anda++;
        }
        

   }
    



    
//printf(" AAA anda = %d\n", anda );
        return anda;
} 



    //     diretivas[1] = "SPACE";
    // diretivas[2] = "CONST";
    // diretivas[3] = "EQU";
void AnaliseSintaticaOpAlocacaoMemoria(infoLinha * linha, int posInicial,TS * tabelaSims)
{
 
    int i = posInicial;
   int numTokens = linha->numTokens;
   int flagSpaceSemNumero = 0;

 //  printf("pos ini = %d str = %s\n", i, linha->Tokens[i] );
   // if(i+1 >= numTokens)
   // {
   //   flagSpaceSemNumero = 1;

   // }



   //printf(" flagSPACESemNumero = %d AAAAA22222\n", flagSpaceSemNumero );
   //printf("%s Token[posinicial] = %s\n", linha->linha, linha->Tokens[posInicial] );
   if( verificaSeOpAlocacaoMemoria  (linha->Tokens[i]))
   {
        

        if(!strcmp(linha->Tokens[i], "SPACE"))
        {

            if(i +1 < numTokens)
            {

                if(!(verificaSeNumero(linha->Tokens[i+1])))
                {
                    printf("AnaliseSintaticaOpAlocacaoMemoria A \n");
                    EscreveArgErro(linha->numLinha,2);                
                }
            }  
        }
        else
        {

            if(i +1 >= numTokens)
            {

                    printf("AnaliseSintaticaOpAlocacaoMemoria B \n");
                    EscreveArgErro(linha->numLinha,2);                
            }
            else
            {
                if(!(verificaSeNumero(linha->Tokens[i+1])))
                {
                    printf("AnaliseSintaticaOpAlocacaoMemoria C \n");
                    EscreveArgErro(linha->numLinha,2);                
                }



            }

        }
            
   }
   //printf("AAAAA333333\n" );
        

}

/*  instrucoes[8] = "COPY";// = 9,
*/
void AnaliseSintaticaOpCopy(infoLinha * linha, int posInicial,TS * tabelaSims)
{
 
    int i = posInicial;
   int numTokens = linha->numTokens;

   if(  verificaSeOpCopy(linha->Tokens[i]))
   {
        if( numTokens - i == 4)
        {
            if(!( verificaSeVariavel(linha->Tokens[i+1]) && verificaSeVariavel(linha->Tokens[i+3]) && !strcmp(linha->Tokens[i+1], ",")  ))
            {   
               //printf("\n AQUI 1");   
                EscreveArgErro(linha->numLinha,2);        
            }
        }
        else if(numTokens - i == 6)
        {
            if(verificaSeMaisOuMenos(linha->Tokens[i+2]))
            {

                if( !(verificaSeVariavel(linha->Tokens[i+1]) && verificaSeNumero(linha->Tokens[i+3]) && !strcmp(linha->Tokens[i+4], ",") && verificaSeVariavel(linha->Tokens[i+5])))
                {
                    //printf("\n AQUI 2");   
                EscreveArgErro(linha->numLinha,2);        

                }

            }
            else if( verificaSeMaisOuMenos(linha->Tokens[i+4]))
            {
                if(!(verificaSeVariavel(linha->Tokens[i+1]) && !strcmp( linha->Tokens[i+2], ",") && verificaSeVariavel(linha->Tokens[i+3]) && verificaSeNumero(linha->Tokens[i+5])                    ))
                {

                  //      printf("\n AQUI 3");   
                EscreveArgErro(linha->numLinha,2);        


                }


            }
            else
            {   //printf("\n AQUI 4");

                EscreveArgErro(linha->numLinha,2);        
            }

        }
        else if(numTokens - i == 8)
        {

            if( !( verificaSeVariavel( linha->Tokens[i+1]) && verificaSeMaisOuMenos(linha->Tokens[i+2]) && verificaSeNumero(linha->Tokens[i+3]) && !strcmp(linha->Tokens[i+4], ",") && verificaSeVariavel(linha->Tokens[i+5]) && verificaSeMaisOuMenos(linha->Tokens[i+6]) && verificaSeNumero(linha->Tokens[i+7])      ))
            {
              //  printf("\n AQUI 5");

                EscreveArgErro(linha->numLinha,2);        
            }
        }
        else
        {
         //   printf("\n AQUI 6");

                EscreveArgErro(linha->numLinha,2);        
        }

        

   }

}


/*    diretivas[0] = "SECTION";
    diretivas[7] = "DATA";
    diretivas[8] = "TEXT";
*/

void AnaliseSintaticaOpSection(infoLinha * linha, int posInicial,TS * tabelaSims)
{
 
    int i = posInicial;
   int numTokens = linha->numTokens;

   if(  verificaSeSection (linha->Tokens[i]))
   {
        if( numTokens != 2)
        {
            //printf("AnaliseSintaticaOpSection A\n");
            EscreveArgErro(linha->numLinha,2);        
        }
        if(!verificaSeOpTipoSection( linha->Tokens[i+1]))
        {   //printf("AnaliseSintaticaOpSection B\n");
            EscreveArgErro(linha->numLinha,2);        
        }

   }

}

opLinha * insereOpLinha(infoLinha *linha, int posInicial, opLinha * op)
{
    int i;
    opLinha * pilhaAUX = (opLinha *)malloc(sizeof(opLinha));
    pilhaAUX->linha = linha->numLinha;
    pilhaAUX->operacao = (char *)malloc(strlen(linha->Tokens[posInicial])*sizeof(char));
    pilhaAUX->operacao = linha->Tokens[posInicial];
    pilhaAUX->posInicial = posInicial;
    pilhaAUX->numArgs = linha->numTokens - posInicial;
    pilhaAUX->args = (char **)malloc(pilhaAUX->numArgs*sizeof(char *));

    for ( i = posInicial; i < pilhaAUX->numArgs+posInicial; i++)
    {
        pilhaAUX->args[i] = (char*)malloc(strlen(linha->Tokens[i])*sizeof(char));
        pilhaAUX->args[i] = linha->Tokens[i];
    }


    pilhaAUX->opLinhaProx = op;

    return pilhaAUX;    

}



opLinha * AnaliseSintatica(infoLinha * linha, TS * tabelaSims, opLinha * linhas)
{
    int numTokens = linha->numTokens;
    int erro = 1;
    char * string1 = (char *)malloc(sizeof(char *));
    char * string2 = (char *)malloc(sizeof(char *));




//pilhaPos * insereNovaOpLinha()


//printf("str1 = %s, str2 = %s\n", string1, string2 );

    
//printf("teste em %s, numTokens = %d\n", linha->linha, linha->numTokens);
        // if(!(verificaSeInstrucao(linha->Tokens[1]) || !strcmp(linha->Tokens[1], "CONST") || !strcmp(linha->Tokens[1], "EQU"))  )
        // {
        //     EscreveArgErro(linha->numLinha,2);
   if(numTokens == 1)
   {
   if(strcmp(linha->Tokens[0], "STOP") != 0)
   {
    //printf("Erro linha apenas com um Token diferente de STOP\n");
    EscreveArgErro(linha->numLinha,2);
   }
  }
   else 
   { 
      int posInicial = verificaoInicial( linha);

      if(posInicial == -1)
      {
      //  printf("Erro sintatico linha %d : %s\n",linha->numLinha, linha->Tokens[0]);
         EscreveArgErro(linha->numLinha,2);
      }
      else
      {

        linhas = insereOpLinha(linha, posInicial,linhas);    
        AnaliseSintaticaOpMemoria( linha, posInicial, tabelaSims);
        AnaliseSintaticaOpSection(linha, posInicial,tabelaSims);
        AnaliseSintaticaOpAritmetica(linha,posInicial,tabelaSims);
        AnaliseSintaticaOpAlocacaoMemoria(linha, posInicial,tabelaSims);
        AnaliseSintaticaOpCopy(linha, posInicial,tabelaSims);
        AnaliseSintaticaOpPulo(linha, posInicial, tabelaSims);
        AnaliseSintaticaOpEntradaSaida(linha, posInicial, tabelaSims);

        }
    }
            

return linhas;
    
}





















void AnaliseSemanticaOpAritmetica(opLinha * linha, TS * lista,int *  posSections)
{

    int i = linha->posInicial;
    int j;
    int fim = i + linha->numArgs;
    int k = 0;
    TS ** simbolos ;//= (TS**)malloc(sizeof(TS));
    //TS * simbolo2 = (TS*)malloc(sizeof(TS));
    simbolos = (TS **)malloc(2*sizeof(TS *));
    int maisOuMenos = 0;
    int num = 0;

    //printf(" arg = %s, linha = %d\n",linha->args[i], linha->linha );
    
  int teste = verificaSeOpAritmetica(linha->args[i]); 

//printf("AAAQQQQQ teste = %d\n", teste);
  
    if(teste)
    {

        if(posSections[0] < posSections[1])
        {
            if(linha->linha > posSections[0] && linha->linha <posSections[1])
            {
                EscreveArgErro(linha->linha, 3);
                //printf("AQUI 1\n");
            }
        
        }
        else 
        {

            if(linha->linha > posSections[0])
            {
                EscreveArgErro(linha->linha, 3);
                //printf("AQUI 2\n");
            }

        }
    //printf("AQUI3");
            if(linha->numArgs > 2)
            {


                for(j = i; j<fim;j++)
                {
                    if( ! verificaSeMaisOuMenos(linha->args[j]))    
                    {
                        if(verificaSeVariavel(linha->args[j]))
                        {   simbolos[k] = (TS *)malloc(sizeof(TS));
                            simbolos[k] = buscaTS(lista, linha->args[j]);
                            if(simbolos[k] == NULL)
                            {
         //                       printf("Nulo na procura por %s\n", linha->args[j]);
                            }
                            else
                            {
                            //printf("%s\n", simbolos[k]->nome );

                                if(simbolos[k]->def == 0 || simbolos[k]->valido == 0)
                                {
                                    //printf("AQUI 3\n");
                                    EscreveArgErro(linha->linha, 3);
                                }

                            k++;
                            }
                        }
                         else if(verificaSeNumero(linha->args[j]))
                         {
                             num = atoi(linha->args[j]);
                         }
 
                    }
                    else
                    {
                        if(!strcmp(linha->args[j],"+"))
                            maisOuMenos = 1;
                        else if(!strcmp(linha->args[j],"-"))
                            maisOuMenos = -1;

                    }  

                }

            }
           else
            {
                simbolos[0] = (TS *)malloc(sizeof(TS));
                simbolos[0] = buscaTS(lista, linha->args[i+1]);
                
      //          printf("simbolo = %s\n", simbolos[0]->nome );
                if(simbolos[0]->def == 0 || simbolos[0]->valido == 0)
                {
                    //printf("\nlinha = %d arg = %s",linha->linha, linha->args[i+1]);
                    //printf("\nlinha = %d AQUI 4 simbolo[0] nome = %s", linha->linha, simbolos[0]->nome);
                    EscreveArgErro(linha->linha, 3);
                }
                k++;


            }
        
    }
    //printf(" k = %d\n", k);

          if(k == 2)
            {
            


                if(!strcmp(simbolos[0]->tipoDeDefinicao,"CONST") && !strcmp(simbolos[1]->tipoDeDefinicao,"CONST") )
                EscreveArgErro(linha->linha, 3);
                if(!strcmp(simbolos[1]->tipoDeDefinicao,"SPACE") && !strcmp(simbolos[0]->tipoDeDefinicao,"SPACE") )                    
                EscreveArgErro(linha->linha, 3);




             }
            else if(k == 1)
            {
              //  printf("  arg[0] = %s",  simbolos[0]->nome );

                if(maisOuMenos != 0)
                {
                   // printf("  maisOuMenos = %d", maisOuMenos );
                    if(num != 0)
                    {

                        if(strcmp(simbolos[0]->tipoDeDefinicao,"SPACE"))
                        {   //printf("AQUI 5 \n"); 
                            EscreveArgErro(linha->linha, 3);
                        }
                    }

                }
                if(num != 0)
                {

           //         printf("  num = %d", num );

                    if(maisOuMenos == 1)
                    {
                        if(num > simbolos[0]->valorDeDefinicao )
                            EscreveArgErro(linha->linha, 3);
                    }


                }
        //        printf("AQui 1 linha %d\n", linha->linha );

                if( !strcmp(linha->args[i],"DIV"))
                {//printf("AQui 2 linha %d\n", linha->linha );

                    if(!strcmp(simbolos[0]->tipoDeDefinicao,"CONST"))
                        if(simbolos[0]->valorDeDefinicao == 0)
                            EscreveArgErro(linha->linha, 3);   
                }



            }

    


     

//free(simbolos);
 //printf("AQUI10\n");
}



//instrucoes[9] = "LOAD";// = 10,
//instrucoes[10] = "STORE";// = 11,
    
void AnaliseSemanticaOpMemoria(opLinha * linha, TS * lista,int *  posSections)
{

   
   
        int i = linha->posInicial;
        int fim = i + linha->numArgs;
        int j;
        int entrei = 0;
      TS * s ;//= (TS**)malloc(sizeof(TS));
      //printf("AAAA\n");
       s = (TS*)malloc(sizeof(TS));
       //printf("BBBBB\n");
 //       simbolo = NULL;
        //printf("AQUI args = %s\n",linha->args[i] );
    if(verificaSeOpMemoria(linha->args[i]))
    {
        if(posSections[0] < posSections[1])
        {
            if(linha->linha > posSections[0] && linha->linha <posSections[1])
            EscreveArgErro(linha->linha, 3);
        
        }
        else 
        {

            if(linha->linha > posSections[0])
            EscreveArgErro(linha->linha, 3);

        }

       for (j = i; j < fim; j++)
        {
           // printf("ENTREI AQAQQA\n");
            if(verificaSeVariavel(linha->args[j]))
            {
                //printf("arg[%d] = %s\n",j, linha->args[j] );
                s =  buscaTS(lista, linha->args[j]);
             //   printf("ENTREIIIIIIIIIIIIIIIIIIIIIIIIII \n");
                entrei= 1;
                //break;
            }
            
        }

    }
  

     //     printf("s =%s\n",s->nome );
   
         if(entrei)
         {
            if(s->def == 0)
            {
                //printf("AAAAAAAAAAAAAA\n");
             EscreveArgErro(linha->linha, 3);   
            }
            else
            {
                if(!strcmp(linha->args[i],"LOAD"))
                {
                    if(!(!strcmp(s->tipoDeDefinicao,"CONST") || !strcmp(s->tipoDeDefinicao,"SPACE") ))
                        {  // printf("AQUI 1 linha = %d\n", linha->linha);
                        EscreveArgErro(linha->linha, 3);
                        }
                    
                }
                else if(!strcmp(linha->args[i],"STORE"))
                {
                    if(strcmp(s->tipoDeDefinicao,"SPACE") )
                        {  //printf("AQUI 2 linha = %d\n", linha->linha);
                        EscreveArgErro(linha->linha, 3);
                    }
                }   

                
            }
         }
             
     //printf("AQUI3\n");

 
}
                    
    // instrucoes[4] = "JMP";// = 5,
    // instrucoes[5] = "JMPN";// = 6,
    // instrucoes[6] = "JMPP";// = 7,
    // instrucoes[7] = "JMPZ";// = 8,

void AnaliseSemanticaOpPulo(opLinha * linha, TS * lista,int *  posSections)
{

 int i = linha->posInicial;
        int fim = i + linha->numArgs;
        int j;
        int entrei = 0;
      TS * s ;//= (TS**)malloc(sizeof(TS));
      //printf("AAAA\n");
       s = (TS*)malloc(sizeof(TS));
       //printf("BBBBB\n");
 //       simbolo = NULL;
     //   printf("AQUI args = %s\n",linha->args[i] );
       if(verificaSeOpPulo(linha->args[i]))
       {

        if(posSections[0] < posSections[1])
        {
            if(linha->linha > posSections[0] && linha->linha <posSections[1])
            EscreveArgErro(linha->linha, 3);
        
        }
        else 
        {

            if(linha->linha > posSections[0])
            EscreveArgErro(linha->linha, 3);

        }


       for (j = i; j < fim; j++)
        {
           // printf("ENTREI AQAQQA\n");
            if(verificaSeVariavel(linha->args[j]))
            {
          //      printf("arg[%d] = %s\n",j, linha->args[j] );
                s =  buscaTS(lista, linha->args[j]);
       //         printf("ENTREIIIIIIIIIIIIIIIIIIIIIIIIII \n");
                entrei= 1;
            }
            
        }
    }
  

   //       printf("s =%s\n",s->nome );
   
         if(entrei)
         {
            if(s->def == 0)
            {
             EscreveArgErro(linha->linha, 3);   
            }
            else
            {

                if(strcmp(s->tipoDeDefinicao,"LABEL")|| s->valido == 0)       
                    EscreveArgErro(linha->linha, 3);
            }
         }
        


}


    // instrucoes[11] = "INPUT";// = 12,
    // instrucoes[12] = "OUTPUT";// = 13,


void AnaliseSemanticaOpEntradaSaida(opLinha * linha, TS * lista, int *  posSections)
{

 int i = linha->posInicial;
        int fim = i + linha->numArgs;
        int j;
        int entrei = 0;
      TS * s ;//= (TS**)malloc(sizeof(TS));
      //printf("AAAA\n");
       s = (TS*)malloc(sizeof(TS));
       //printf("BBBBB\n");
 //       simbolo = NULL;
   //     printf("AQUI args = %s\n",linha->args[i] );
       if(verificaSeOpEntradaSaida(linha->args[i]))
       {


        if(posSections[0] < posSections[1])
        {
            if(linha->linha > posSections[0] && linha->linha <posSections[1])
            EscreveArgErro(linha->linha, 3);
        
        }
        else 
        {

            if(linha->linha > posSections[0])
            EscreveArgErro(linha->linha, 3);

        }

        
       for (j = i; j < fim; j++)
        {
           // printf("ENTREI AQAQQA\n");
            if(verificaSeVariavel(linha->args[j]))
            {
          //      printf("arg[%d] = %s\n",j, linha->args[j] );
                s =  buscaTS(lista, linha->args[j]);
       //         printf("ENTREIIIIIIIIIIIIIIIIIIIIIIIIII \n");
                entrei= 1;
            }
            
        }
    }
  

   //       printf("s =%s\n",s->nome );
   
         if(entrei)
         {
            if(s->def == 0)
            {
             EscreveArgErro(linha->linha, 3);   
            }
            else
            {

                if(!(!strcmp(s->tipoDeDefinicao,"SPACE")|| !strcmp(s->tipoDeDefinicao,"CONST")|| s->valido == 1))       
                    EscreveArgErro(linha->linha, 3);
            }
         }
 

}
    






    //     diretivas[1] = "SPACE";
    // diretivas[2] = "CONST";
    // diretivas[3] = "EQU";
 void AnaliseSemanticaOpAlocacaoMemoria(opLinha * linha, TS * lista, int *  posSections)
 {
    int i = linha->posInicial;
    int fim = i + linha->numArgs;
     if(verificaSeOpAlocacaoMemoria(linha->args[i]))
     {


        if(posSections[0] < posSections[1])
        {
            if(linha->linha < posSections[0] || linha->linha > posSections[1])
            EscreveArgErro(linha->linha, 3);
        
        }
        else 
        {

            if(linha->linha > posSections[1] && linha->linha < posSections[0] )
            EscreveArgErro(linha->linha, 3);

        }
        // if(secao != 0)
        // {
        //     printf("AAAAAQQQQIIIII\n");
        // EscreveArgErro(linha->linha, 3);
        // }
     }

        

 }

/*  instrucoes[8] = "COPY";// = 9,
*/
void AnaliseSemanticaOpCopy(opLinha * linha, TS * lista, int * posSections)
{


int i = linha->posInicial;
    int j;
    int fim = i + linha->numArgs;
    int k = 0;
    TS ** simbolos ;//= (TS**)malloc(sizeof(TS));
    //TS * simbolo2 = (TS*)malloc(sizeof(TS));
    simbolos = (TS **)malloc(2*sizeof(TS *));
    int maisOuMenos = 0;
    int num = 0;

   // printf(" arg = %s\n",linha->args[i] );
    
  int teste = verificaSeOpCopy(linha->args[i]); 

//printf("AAAQQQQQ teste = %d\n", teste);
  
    if(teste)
    {

        if(posSections[0] < posSections[1])
        {
            if(linha->linha > posSections[0] && linha->linha <posSections[1])
            EscreveArgErro(linha->linha, 3);
        
        }
        else 
        {

            if(linha->linha > posSections[0])
            EscreveArgErro(linha->linha, 3);

        }

  //       printf("AQUI3");
            if(linha->numArgs > 2)
            {


                for(j = i; j<fim;j++)
                {
                    
                        if(verificaSeVariavel(linha->args[j]))
                        {   simbolos[k] = (TS *)malloc(sizeof(TS));
                            simbolos[k] = buscaTS(lista, linha->args[j]);
                            if(simbolos[k] == NULL)
                            {
             //                   printf("Nulo na procura por %s\n", linha->args[j]);
                            }
                            else
                            {
                            //printf("%s\n", simbolos[k]->nome );
                            if(simbolos[k]->def == 0)
                            {    
                                if(simbolos[k]->def == 0 || simbolos[k]->valido == 0)
                                EscreveArgErro(linha->linha, 3);
                            }
                            k++;
                            }
                        }
                         
 
                    
                }  

            }

    }
           
        

          if(k == 2)
            {
            


                if(!strcmp(simbolos[0]->tipoDeDefinicao,"CONST") && !strcmp(simbolos[1]->tipoDeDefinicao,"CONST") )
                EscreveArgErro(linha->linha, 3);
                if(!strcmp(simbolos[0]->tipoDeDefinicao,"CONST") && !strcmp(simbolos[1]->tipoDeDefinicao,"SPACE") )                    
                EscreveArgErro(linha->linha, 3);

                if(!strcmp(simbolos[0]->tipoDeDefinicao,"SPACE") && !strcmp(simbolos[1]->tipoDeDefinicao,"SPACE"))
                {
                    if(simbolos[0]->valorDeDefinicao != simbolos[1]->valorDeDefinicao)
                        EscreveArgErro(linha->linha, 3);
                }

                if(!strcmp(simbolos[0]->tipoDeDefinicao,"LABEL") || !strcmp(simbolos[1]->tipoDeDefinicao,"LABEL"))
                    EscreveArgErro(linha->linha, 3);


             }
           


}



int * procuraSections (opLinha * linha)
{
    opLinha * p;
    p = (opLinha *) malloc(sizeof(opLinha));
    int * pos = (int *)malloc(2*sizeof(int));
   int i = 0;
    pos[0] = -1;
    pos[1] = -1;
    p = linha;
   
    for(p = linha;p!=NULL;p = p->opLinhaProx)
     {
        i = p->posInicial;
        
         if(p->numArgs >= 2)
         {


//          printf("AQUI1111\n" );
             if(!strcmp(p->args[i],"SECTION" ))
             {
//                printf("AQUI22222\n" );

                if(!strcmp(p->args[i+1],"DATA" ))
                {
                   pos[0] = p->linha;
                }
                if(!strcmp(p->args[i+1],"TEXT" ))
                {
                    pos[1] = p->linha;
                }

             }
         }
     }

             return pos;


}    


void analiseSemantica(opLinha * linha, TS * lista)
{
    opLinha * p;
    p = (opLinha *) malloc(sizeof(opLinha));
    int i;
    int secao = -1;
    int acheiSectionText = 0;
    int acheiSectionData = 0;
    int * posSections = (int *)malloc(2*sizeof(int));

    posSections =  procuraSections (linha);

    //printf("pos[0] = data = %d\n", posSections[0]);
    //printf("pos[1] = text = %d\n", posSections[1]);

    if(posSections[0] == -1 || posSections[1] == -1)
        EscreveArgErro(-1, 3);


     for(p = linha;p!=NULL;p = p->opLinhaProx)
     {
//        printf("\nlinha = %d",p->linha );
      
         AnaliseSemanticaOpAlocacaoMemoria(p, lista, posSections);
    AnaliseSemanticaOpAritmetica(p, lista, posSections);
    AnaliseSemanticaOpMemoria(p, lista, posSections);
    AnaliseSemanticaOpPulo(p, lista, posSections);
     AnaliseSemanticaOpCopy(p,lista, posSections);
     AnaliseSemanticaOpEntradaSaida(p,lista,posSections);
  //   printf("AQUI12345\n" );
    }

//    printf("SAIIII\n");



}



