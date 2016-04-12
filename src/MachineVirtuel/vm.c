#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "interpret.h"

/* Nombre de registre admissible*/
#define NUM_REGS 5
/* Registre */
unsigned regs[ NUM_REGS ];
/* Contient les instructions */
unsigned program[10000];
/* program counter */
int pc = 0;
/* Fichier de sorti */
FILE * fichier_sortie;
/* the VM runs until this flag becomes 0 */
int running = 1;


/* fetch la nouvelle instruction 
   output: l'intruction suivante en hexa
*/
int fetch()
{
  return program[ pc++ ];
}

/* instruction fields */
int operation = 0;
int reg1     = 0;
int reg2     = 0;
int o     = 0;
int flagInt      = 0;

/* decode un mot 
   input: instr - l'instruction en hexa a decoder
*/
void decode( int instr )
{
  operation = (instr & 0xF8000000) >> 27;
  reg1     = (instr & 0x7C00000 ) >>  22;
  reg2     = (instr & 0x1F  );
  o     = (instr & 0x1FFFE0   ) >> 5; 
  flagInt      = (instr & 0x200000  ) >> 21;
}

/* evaluate la derniere instruction */
void eval()
{
  switch( operation )
    {
    case 0:
      /* nop */
      fprintf(fichier_sortie, "nop\n" );
      break;
    case 1:
      /* add */
      fprintf(fichier_sortie,"add(r%d,r%d,%d)\n", reg1, reg2, o);
      if(flagInt==1)
	{
	  regs[reg2] = regs[reg1]+regs[o];
	}
      else
	{
	  regs[reg2] = regs[reg1]+o;
	}
      break;
    case 2:
      /* sub */
      fprintf(fichier_sortie,"sub(r%d,r%d,%d)\n", reg1, reg2, o);
      if(flagInt==1)
	{
	  regs[reg2] = regs[reg1]-regs[o];
	}
      else
	{
	  regs[reg2] = regs[reg1]-o;
	}
      break;
    case 3:
      /* mult */
      fprintf(fichier_sortie,"mult(r%d,r%d,%d)\n", reg1, reg2, o);
      if(flagInt==1)
	{
	  regs[reg2] = regs[reg1]*regs[o];
	}
      else
	{
	  regs[reg2] = regs[reg1]*o;
	}
      break;
    case 4:
      /* div */
      fprintf(fichier_sortie,"div(r%d,r%d,%d)\n", reg1, reg2, o);
      if(flagInt==1)
	{
	  regs[reg2] = regs[reg1]/regs[o];
	}
      else
	{
	  regs[reg2] = regs[reg1]/o;
	}
      break;
    case 5:
      /* and */
      fprintf(fichier_sortie,"and(r%d,r%d,%d)\n", reg1, reg2, o);
      regs[reg2] = regs[reg1]&o;
      break;
    case 6:
      /* or */
      fprintf(fichier_sortie,"or(r%d,r%d,%d)\n", reg1, reg2, o);
      if(flagInt==1)
	{
	  regs[reg2] = regs[reg1]|regs[o];
	}
      else
	{
	  regs[reg2] = regs[reg1]|o;
	}
      break;
    case 7:
      /* xor */
      fprintf(fichier_sortie,"xor(r%d,r%d,%d)\n", reg1, reg2, o);
      if(flagInt==1)
	{
	  regs[reg2] = regs[reg1]^regs[o];
	}
      else
	{
	  regs[reg2] = regs[reg1]^o;
	}
      break;
    case 8:
      /* shl */
      fprintf(fichier_sortie,"shl(r%d,r%d,%d)\n", reg1, reg2, o);
      if(flagInt==1)
	{
	  regs[reg2] = regs[reg1]<<regs[o];
	}
      else
	{
	  regs[reg2] = regs[reg1]<<o;
	}
      break;
    case 9:
      /* shr */
      fprintf(fichier_sortie,"shr(r%d,r%d,%d)\n", reg1, reg2, o);
      if(flagInt==1)
	{
	  regs[reg2] = regs[reg1]>>regs[o];
	}
      else
	{
	  regs[reg2] = regs[reg1]>>o;
	}
      break;
    case 10:
      /* slt */
      fprintf(fichier_sortie,"slt(r%d,r%d,%d)\n", reg1, reg2, o);
      if (regs[reg1]<o && flagInt==0)
	{
	  regs[reg2] = 1;
	}
      else if(flagInt==1 && regs[reg1]<regs[o])
	{
	  regs[reg2] = 1;
	}
      else
	{
	  regs[reg2] = 0;
	}
      break;
    case 11:
      /* sle */
      fprintf(fichier_sortie,"sle(r%d,r%d,%d)\n", reg1, reg2, o);
      if (flagInt==0 &&regs[reg1]<=o)
	{
	  regs[reg2] = 1;
	}
      else if(flagInt==1 && regs[reg1]<=regs[o])
	{
	  regs[reg2] = 1;
	}
      else
	{
	  regs[reg2] = 0;
	}
      break;
    case 12:
      /* seq */
      fprintf(fichier_sortie,"seq(r%d,r%d,%d)\n", reg1, reg2, o);
      if (flagInt==0 && regs[reg1]==o)
	{
	  regs[reg2] = 1;
	}
      else if(flagInt==1 && regs[reg1]==regs[o])
	{
	  regs[reg2] = 1;
	}
      else
	{
	  regs[reg2] = 0;
	}
      break;
    case 13:
      /* load */
      fprintf(fichier_sortie, "load(r%d,r%d,%d)\n", reg1, reg2, o);
      if(flagInt==1)
	{
	  regs[reg2] = regs[reg1]+regs[o];
	}
      else
	{
	  regs[reg2] = regs[reg1]+o;
	}
      break;
    case 14:
      /* store */
      fprintf(fichier_sortie,"store(r%d,r%d,%d)\n", reg1, reg2, o);
      if(reg1+o<5)
	{
	  regs[reg1+o] = regs[reg2];
	}
      else
	{
	  fprintf(fichier_sortie,"error\n");
	}
      
      break;
    case 15:
      /* jmp */
      fprintf(fichier_sortie,"jmp(%d)\n",o);
      //      regs[reg2]=pc+1;
      pc = o;
      break;
    case 16:
      /* braz */
      fprintf(fichier_sortie,"braz(r%d,%d)\n",reg1,o);
      if(regs[reg1]==0)
	{
	  pc = o;
	}
      break;
    case 17:
      /* branz */
      fprintf(fichier_sortie,"branz(r%d,%d)\n",reg2,o);
      if(reg2!=0)
	{
	  pc = o;
	}
      break;
    case 18:
      /* scall */
      fprintf(fichier_sortie,"scall\n");
      
      break;
    case 19:
      /* stop */
      fprintf(fichier_sortie,"Stop\n");
      running = 0;
      break;
    default:
      fprintf(fichier_sortie,"error!!\n");
      break;
    }
}

/* Permet d afficher tous les registres en hexa */
void showRegs()
{
  int i;
  for( i=0; i<NUM_REGS; i++ )
    fprintf(fichier_sortie, "%08X ", regs[ i ] );
  fprintf(fichier_sortie, "\n" );
}

/* Permet de lancer l'execution du programme */
void run()
{
  while( running )
    {
      showRegs();
      int instr = fetch();
      decode( instr );
      eval();
    }
  showRegs();
}

/* Permet de gerer la sorti du programme 
   input: file_output - la sortie du programme
          e           - indique s il faut enregistrer l etat des registre dans .config
*/
void afficher(char file_output[50], int e)
{
  if(e==1)
    {
      fichier_sortie = fopen(".config","w");
      showRegs();
      fclose(fichier_sortie);
    }
  if(strcmp(file_output,"toto")==0)
    {
      system("cat toto;rm toto");
    }
  else
    {
      printf("Sortie enregistrer dans %s\n", file_output);
    }
  
  return ;
}

/* Permet de charger l etat des registre */
void load()
{
  FILE * config = fopen(".config","r");
  int i=0;
  char mot[50];
  char mot2[50];
  
  while(fgets(mot,9,config)!=NULL)
    {
      sprintf(mot2,"0x%s",mot);
      sscanf(mot2,"%X",&regs[i]);
      i++;
      fgets(mot,2,config);      
    }
  fclose(config);
  return;
}


int main( int argc, char * argv[] )
{
  int opt;
  char file_input[50] = "facto.txt";
  char file_output[50] = "toto";
  clock_t t1,t2;
  long clk_tck = CLOCKS_PER_SEC;
  int enregistrer = 0;
    
  while((opt = getopt(argc,argv,"i:o:leh"))!= -1)
    {
      switch(opt)
	{
	case 'i':
	  strcpy(file_input,optarg);
	  break;
	case 'o':
	  strcpy(file_output,optarg);
	  break;
	case 'l':
	  load();
	  break;
	case '?':
	  return 0;
	  break;
	case 'e':
	  enregistrer = 1;
	  break;
	case 'h':
	  system("cat .help");
	  return 0;
	  break;
	}
    }
  fichier_sortie = fopen(file_output,"w");
  system("cat .bonjour");
  createCode(file_input,program);
  t1 = clock();
  run();
  t2 = clock();
  fprintf(fichier_sortie,"\n\n-------------------------------------------\n \
Temps ecoulé par instruction: %lf s\n-------------------------------------------\n"\
	  ,(double)(t2-t1)/(double)(clk_tck*(pc)));
  fclose(fichier_sortie);
  afficher(file_output, enregistrer);
  return 0;
}
