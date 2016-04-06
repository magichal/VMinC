#include "interpret.h"

void affichebin(unsigned n)
{
	unsigned bit = 0 ;
	unsigned mask = 1 ;
	int i;
	for (i=0 ; i < 32 ; ++i)
	{
		bit = (n & mask) >> i ;
		printf("%d", bit) ;
		mask <<= 1 ;
	}
}

char * bin (unsigned long int i)
{
    static char buffer [1+sizeof (unsigned long int)*8] = { 0 };
    char *p=buffer-1+sizeof (unsigned long int)*8;
    do { *--p = '0' + (i & 1); i >>= 1; } while (i);
    return p;
}



int main (int argc, char * argv[]){ 
	
	
	Tableau *tab = malloc(sizeof(Tableau));
	Tableau *courant = malloc(sizeof(Tableau));
	unsigned Commande[1000];
	
		
	AnalyseText("load.txt", tab);//&Tableau);
	int i=0;
	courant=tab;
	
	while((courant->suivant)!=NULL){
	printf("%s\n",courant->mot);
	courant=courant->suivant;
	i++;
	}
	
	AnalyseLexique(tab,Commande);
	int j=0;
	while(Commande[j]!=0){
	printf("%s\n",bin(Commande[j]));
	j++;
	}
	printf("\n");
	printf("%08X\n",Commande[0]);
	
	
	return 0;
}
