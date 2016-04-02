#include "interpret.h"


/* void separate(char * output[],char * input){
		
	char temp[15]; 
	int i=0;
	int j=0;
	char separator=' ';
	
	while(input!='\0'){
		
		if(input!=separator){
		
			* temp[i]=*input;
			*input++;
			i++;
		}
		else{
			sprintf(* output[j],*temp);
			*input++;
		}
	
	
	}
} */

char analyse(const char * filepath){
	
	printf("Ouverture de : %s\n",filepath);
	FILE * file=NULL;
	
	char temp;
	char *temp1=malloc(1000*sizeof(char));
	char separator=' ';
	char Tableau[1000][1000];
	int i=0;
	
	file =fopen(filepath,"r");
	
	if (file!=NULL)
	{
		printf("Fichier trouve, traitement en cours\n");
		printf("\n");
		
		while(temp!=EOF)
		{
			printf("%c\n",temp);
			if(temp!=separator & temp!='\n' & temp!='	'){
				temp1[i]=temp;
				i++;
				temp=fgetc(file);
				
			}
			else{
				i=0;
				printf("Need to separate : %s\n",temp1);
				temp=fgetc(file);
			}
			
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
