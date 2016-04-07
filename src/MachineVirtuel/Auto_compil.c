#include "interpret.h"

FILE * logfichier;

void resetBuffer(char *buffer,int cpt){
	
	int i;
	for(i=0;i<=cpt;i++){
		buffer[i]='\0';
	}


}

int seekop(char * word){

	char OPCODWDS[21][6]={"nop","add","sub","mult","div","and","or","xor","shl","shr","slt","sle","seq","load","store","jmp","braz","branz","scall","stop","_"};
	int i=0;
	for(i=0;i<=20;i++){
		if(strcmp(word,OPCODWDS[i])==0){
			return i;
		}
	}
	return 0;	
}

int seekreg(char * word){

	char REGTBL[6][3]={"NAN","r1","r2","r3","r4","r5"};
	int i=0;
	
	for(i=0;i<=6;i++){
		if(strcmp(word,REGTBL[i])==0){
			return i;
		}
	}
	return -1;	
}

void splitInstruct(Tableau * tab,char * INSTRUCTCODE){

	char sep=',';
	char *temp1=malloc(1000*sizeof(char));
	int i=0;
	
	while(*INSTRUCTCODE!='\0'){
		
		if( * INSTRUCTCODE!=sep ){
		
			temp1[i]=(char) * INSTRUCTCODE;
			i++;
			INSTRUCTCODE++;
		
		}
		else{
			if(strcmp(temp1,"")!=0){
			
					strcpy(tab->mot,temp1); 
					resetBuffer(temp1,i);
					tab->suivant = malloc(sizeof(Tableau));
					tab = tab->suivant;
					i=0;
					
			}
			
			INSTRUCTCODE++;
		
		}
		
		if(* INSTRUCTCODE=='\0'){
			strcpy(tab->mot,temp1);
		}
	}

}
void createInstruc(char * mot, unsigned *breg1, unsigned * breg2, unsigned *boo, unsigned *bparam){
	
	Tableau *temptab = malloc(sizeof(Tableau));
	splitInstruct(temptab,mot);
	int tempint=0;
	*breg1=0;
	*breg2=0;
	*boo=0;
	*bparam=0;
	int r=0;
	
	fprintf(logfichier,"Arg1 : %s\n",temptab->mot);
				
				r=seekreg(temptab->mot);
				switch(r){
					
					case 0:
						* breg1=0b00000<<22;
			logfichier = fopen("logfichier.txt","w");			break;
					
					case 1:
						* breg1=0b00001<<22;
						break;
					case 2:
						* breg1=0b00010<<22;
						break;
					case 3:
						* breg1=0b00011<<22;
						break;
					case 4:
						* breg1=0b00100<<22;
						break;
					case 5:
						* breg1=0b00101<<22;
						break;
				}
				
				fprintf(logfichier,"breg1 :%08X\n",* breg1);
				
				temptab=temptab->suivant;
				fprintf(logfichier,"Arg2 : %s\n",temptab->mot);
				r=seekreg(temptab->mot);
				
				if(r==-1){
					*boo=0<<21;
				}
				else{
					*boo=1<<21;
				}
		
				fprintf(logfichier,"o : %08X\n",*boo);
				
				if(*boo==0){
					tempint=atoi(temptab->mot);
					*bparam=tempint<<5;	
				}
				
				else{
				
				r=seekreg(temptab->mot);
					switch(r){
					
						case 0:
							* bparam=0b00000<<5;
							break;
					
						case 1:
							* bparam=0b00001<<5;
							break;
						case 2:
							* bparam=0b00010<<5;
							break;
						case 3:
							* bparam=0b00011<<5;
							break;
						case 4:
							* bparam=0b00100<<5;
							break;
						case 5:
							* bparam=0b00101<<5;
							break;
					}
				
				}
				
				fprintf(logfichier,"bparam : %08X\n",*bparam);
				temptab=temptab->suivant;
				fprintf(logfichier,"Arg3 : %s\n",temptab->mot);
				r=seekreg(temptab->mot);
				switch(r){
					
					case 0:
						* breg2=0b00000;
						break;
					
					case 1:
						* breg2=0b00001;
						break;
					case 2:
						* breg2=0b00010;
						break;
					case 3:
						* breg2=0b00011;
						break;
					case 4:
						* breg2=0b00100;
						break;
					case 5:
						* breg2=0b00101;
						break;
				}
				
				fprintf(logfichier,"breg2 : %08X\n",* breg2);
}
	

void AnalyseText(const char * filepath, Tableau *tab){
	logfichier = fopen("logfichier.txt","a");
	fprintf(logfichier,"Ouverture de : %s\n",filepath);
	FILE * file=NULL;
	
	char temp;
	char *temp1=malloc(1000*sizeof(char));
	int i=0;
	
	file =fopen(filepath,"r");
	
	if (file!=NULL) 
	{
		fprintf(logfichier,"Fichier trouve, traitement en cours\n");
		fprintf(logfichier,"\n");
		fprintf(logfichier,"Instructions lues : \n");
		fprintf(logfichier,"\n");
		
		temp=fgetc(file);
		
		while(temp!=EOF)
		{
			fprintf(logfichier,"%c",temp);
			
			if(temp!=' ' && temp!='\n' && temp!='	' && temp!='\r' && temp!='\0' ){
			
				temp1[i]= (char) temp;
				i++;
				temp=fgetc(file);
				
			}
			else{
				
				if(strcmp(temp1,"")!=0){
				
					strcpy(tab->mot,temp1); 
					resetBuffer(temp1,i);
					tab->suivant = malloc(sizeof(Tableau));
					tab = tab->suivant;
					i=0;
					
				}
				temp=fgetc(file);
			}
			
		}
		fclose(file);
	}
	else
	{
		fprintf(logfichier,"Fichier introuvable\n");
	} 
	fprintf(logfichier,"\n");
	fprintf(logfichier,"Fin instructions. \n");
	fprintf(logfichier,"\n");
	fclose(logfichier);	
}

void AnalyseLexique(Tableau * tab,unsigned Commande[10000]){
	logfichier = fopen("logfichier.txt","a");
	int OPCODTBL[20]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13};
	int i=0;
	int reversi=0;
	int r=0;
	
	Tableau *temptab = malloc(sizeof(Tableau));
	Tableau *courant = malloc(sizeof(Tableau));
	char tempchar[20];
	int operand;
	int tempint;
	
	unsigned bopcode=0;
	unsigned *breg1=malloc(5*sizeof(unsigned));
	unsigned *boo=malloc(sizeof(unsigned));
	unsigned *bparam=malloc(16*sizeof(unsigned));
	unsigned *breg2=malloc(5*sizeof(unsigned));
	unsigned INSTRUC;
	
	fprintf(logfichier,"Debut de generation des instructions binaire\n");
	courant=tab;
	
	while(tab->suivant!=NULL){
	
		operand=seekop(tab->mot);
		
		switch (operand){
			
			/* nop */	
			case 0: ;
			
				bopcode=0b00000<<27;
				
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code nop : %s\n",tab->mot);
				
				* breg1=0b00000<<22;
				*boo=0<<21;
				* bparam=0b00000<<5;
				* breg2=0b00000;
				
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;  
				Commande[i]=INSTRUC;
				i++;
				break;
			/* add */
			case 1: ;
			
				bopcode=0b00001<<27;
				
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/*sub*/
			case 2: 
				bopcode=0b00010<<27;
				
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/*mult*/
			case 3: 
				bopcode=0b00011<<27;
				
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* div */
			case 4:
			
				bopcode=0b00100<<27;
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* and */
			case 5:
			
				bopcode=0b00101<<27;
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* or */
			case 6:
				bopcode=0b00110<<27;
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* xor */
			case 7:
				bopcode=0b00111<<27;
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* shl */
			case 8:
				bopcode=0b01000<<27;
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* shr */
			case 9:
				bopcode=0b01001<<27;
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;	
				break;
			/* slt */
			case 10:
				bopcode=0b01010<<27;
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* sle */
			case 11:
				
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				bopcode=0b01011<<27;
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* seq */
			case 12:
				
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				bopcode=0b01100<<27;
				tab=tab->suivant;
			
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* load */
			case 13: ;
			
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				bopcode=0b01101<<27;	
				tab=tab->suivant;
				
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* store */
			case 14:
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				bopcode=0b01110<<27;
				tab=tab->suivant;
				
				createInstruc(tab->mot,breg1,breg2,boo,bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				   
				Commande[i]=INSTRUC;
				i++;
				break;
			/* jmp */
			case 15: ;
			
				Tableau *tempcourant = malloc(sizeof(Tableau));
				tempcourant=courant;
				reversi=0;
				
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				bopcode=0b01111<<27;
				
				tab=tab->suivant;
				
				fprintf(logfichier,"Arg 1 : %s\n",tab->mot);
				
				while(strcmp(tempcourant->mot,tab->mot)!=0){
					tempcourant=tempcourant->suivant->suivant;
					reversi++;
				}
				
				* breg1=0b00000<<22;
				*boo=0<<21;
				* bparam=reversi<<5;
				* breg2=0b00000;
				
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				Commande[i]=INSTRUC;
				i++;
				break;
			/* braz */
			case 16: ;
			
				Tableau *tempcourant1 = malloc(sizeof(Tableau));
				Tableau * var=malloc(sizeof(Tableau));
				reversi=0;
				
				tempcourant1=courant;
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				bopcode=0b10000<<27;
				tab=tab->suivant;
				
				splitInstruct(var,tab->mot);
				
				fprintf(logfichier,"Arg1 : %s\n",var->mot);
				r=seekreg(var->mot);
				*breg1=r<<22;
				fprintf(logfichier,"breg1 : %08X\n",*breg1);
				*boo=0<<21;
				*breg2=0;
				
				var=var->suivant;
				fprintf(logfichier,"Arg2 : %s\n",var->mot);
				
				while(strcmp(tempcourant1->mot,var->mot)!=0){
					tempcourant1=tempcourant1->suivant->suivant;
					reversi++;
				}
				
				* bparam=reversi<<5;
				fprintf(logfichier,"bparam : %08X\n",*bparam);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				Commande[i]=INSTRUC;
				i++;
				
				break;
			/* branz */
			case 17: ;
				Tableau *tempcourant2 = malloc(sizeof(Tableau));
				Tableau * var2=malloc(sizeof(Tableau));
				reversi=0;
				
				tempcourant2=courant;
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				bopcode=0b10001<<27;
				tab=tab->suivant;
				
				splitInstruct(var2,tab->mot);
				
				fprintf(logfichier,"Arg1 : %s\n",var2->mot);
				r=seekreg(var2->mot);
				*breg1=r<<22;
				fprintf(logfichier,"breg1 : %08X\n",*breg1);
				*boo=0<<21;
				*breg2=0;
				
				var2=var2->suivant;
				fprintf(logfichier,"Arg2 : %s\n",var2->mot);
				
				while(strcmp(tempcourant2->mot,var2->mot)!=0){
					tempcourant2=tempcourant2->suivant->suivant;
					reversi++;
				}
				
				* bparam=reversi<<5;
				fprintf(logfichier,"bparam : %08X\n",*breg1);
				INSTRUC= bopcode | *breg1 | *boo | *bparam | *breg2;
				Commande[i]=INSTRUC;
				i++;
				break;
			/* scall */
			case 18:
				bopcode=0b10010;
				fprintf(logfichier,"error scall not implemented\n");
				break;
			/* stop */
			case 19:
				fprintf(logfichier,"\n");
				fprintf(logfichier,"Code : %s\n",tab->mot);
				
				bopcode=0b10011;
				INSTRUC=0b10011000000000000000000000000000;
				Commande[i]=INSTRUC;
				i++;
				break;
			
			default :
				 break;
		}
		tab=tab->suivant;
	}
	fprintf(logfichier,"\n");	
	fprintf(logfichier,"Instructions machine générées, pas d'erreurs\n");
	fprintf(logfichier,"\n");
	fclose(logfichier);
}

