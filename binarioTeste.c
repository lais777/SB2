#include <stdio.h>
#include <stdlib.h>
#include <string.h>







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

	Grupos = (int *)malloc((numGrupos+1)*sizeof(int));
	Grupos[0] = numGrupos;
	numGrupos = 1;

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

	printf("numGrupos = %d\n",numGrupos );
	for(i = 0;i < numGrupos;i++)
	{
		printf("\nGrupo[%d] = %d", i, Grupos[i]);
	}
	return Grupos;
}


int main()
{
    int *a;
	char * x = "11 21 00 11 00";

	a =  converteBinario(x);

	//printf("x = %b", x);
	return 0;


}

