#include "interpret.h"

char analyse(const char * filepath){
	
	printf("Ouverture de : %s\n",filepath);
	FILE * file=NULL;
	char temp;
	char Tableau[1000][1000];
	file =fopen(filepath,"r");
	
	if (file!=NULL)
	{
		printf("Fichier trouve, traitement en cours\n");
		printf("\n");
		while(temp!=EOF)
		{
			temp=fgetc(file);
			printf("%c",temp);
		}
		
		fclose(file);
		return Tableau;
	}
	else
	{
		printf("Fichier introuvable\n");
		return Tableau; 
	} 
	
}
