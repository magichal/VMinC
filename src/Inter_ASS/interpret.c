#include "interpret.h"

char * bin (unsigned long int i)
{
    static char buffer [1+sizeof (unsigned long int)*8] = { 0 };
    char *p=buffer-1+sizeof (unsigned long int)*8;
    do { *--p = '0' + (i & 1); i >>= 1; } while (i);
    return p;
}



void createCode (const char *filepath,unsigned Commande[1000]){ 
	
	
	Tableau *tab = malloc(sizeof(Tableau));
	Tableau *courant = malloc(sizeof(Tableau));
	
		
	AnalyseText(filepath, tab);
	int i=0;
	courant=tab;
	
	AnalyseLexique(tab,Commande);
	int j=0;
	
	
	while(Commande[j]!=0x98000000){
	printf("Binaire : %s\n",bin(Commande[j]));
	j++;
	}
	printf("Binaire : %s\n",bin(Commande[j]));
	
}
/*
void main(){

	unsigned Commande[10000];
	createCode("braz.txt",Commande);
	return;


}
*/
