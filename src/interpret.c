#include "interpret.h"

FILE * logfichier;


char * bin (unsigned long int i)
{
    static char buffer [1+sizeof (unsigned long int)*8] = { 0 };
    char *p=buffer-1+sizeof (unsigned long int)*8;
    do { *--p = '0' + (i & 1); i >>= 1; } while (i);
    return p;
}



void createCode (const char *filepath,unsigned Commande[1000]){ 
	system("rm logfichier.txt 2> /dev/null");
	
	
	Tableau *tab = malloc(sizeof(Tableau));
		
	AnalyseText(filepath, tab);
	
	AnalyseLexique(tab,Commande);
	int j=0;
	
	logfichier = fopen("logfichier.txt","a");
	while(Commande[j]!=0x98000000){
	fprintf(logfichier,"Binaire : %s\n",bin(Commande[j]));
	j++;
	}
	fprintf(logfichier,"Binaire : %s\n",bin(Commande[j]));
	fclose(logfichier);
	
}
