#include <stdio.h>
<<<<<<< HEAD
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
=======
>>>>>>> dd45038043933b22af22f9f773a2f078940e860b

#define NUM_REGS 5
unsigned regs[ NUM_REGS ];

<<<<<<< HEAD
unsigned program[] = { 0x68400141, 0x68400144 , 0x98000000};
=======
unsigned program[] = { 0x68600141, 0x68600142 , 0x98000000};
>>>>>>> dd45038043933b22af22f9f773a2f078940e860b

/* program counter */
int pc = 0;

<<<<<<< HEAD
/* Fichier de sorti */
FILE * fichier_sortie;

=======
>>>>>>> dd45038043933b22af22f9f773a2f078940e860b
/* fetch the next word from the program */
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

/* decode a word */

void decode( int instr )
{
  operation = (instr & 0xF8000000) >> 27;
  reg1     = (instr & 0x7C00000 ) >>  22;
  reg2     = (instr & 0x1F  );
  o     = (instr & 0x1FFFE0   ) >> 5; 
  flagInt      = (instr & 0x200000  ) >> 21;
}

/* the VM runs until this flag becomes 0 */
int running = 1;

/* evaluate the last decoded instruction */
void eval()
{
  switch( operation )
    {
    case 0:
      /* nop */
<<<<<<< HEAD
      fprintf(fichier_sortie, "nop\n" );
      break;
    case 1:
      /* add */
      fprintf(fichier_sortie,"add\n");
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
      fprintf(fichier_sortie,"sub\n");
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
      fprintf(fichier_sortie,"mult\n");
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
      fprintf(fichier_sortie,"div\n");
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
      fprintf(fichier_sortie,"and\n");

=======
      printf( "nop\n" );
      break;
    case 1:
      /* add */
      printf("add\n");
      regs[reg2] = regs[reg1]+o;
      break;
    case 2:
      /* sub */
      printf("sub\n");
      regs[reg2] = regs[reg1]-o;
      break;
    case 3:
      /* mult */
      printf("mult\n");
      regs[reg2] = regs[reg1]*o;
      break;
    case 4:
      /* div */
      printf("div\n");
      regs[reg2] = regs[reg1]/o;
      break;
    case 5:
      /* and */
      printf("and\n");
>>>>>>> dd45038043933b22af22f9f773a2f078940e860b
      regs[reg2] = regs[reg1]&o;
      break;
    case 6:
      /* or */
<<<<<<< HEAD
      fprintf(fichier_sortie,"or\n");
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
      fprintf(fichier_sortie,"xor\n");
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
      fprintf(fichier_sortie,"shl\n");
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
      fprintf(fichier_sortie,"shr\n");
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
      fprintf(fichier_sortie,"slt\n");
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
      fprintf(fichier_sortie,"sle\n");
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
      fprintf(fichier_sortie,"seq\n");
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
      fprintf(fichier_sortie, "load r%d a r%d + #%d\n", reg2, reg1, o );
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
      fprintf(fichier_sortie,"store\n");
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
      fprintf(fichier_sortie,"jmp\n");
      regs[reg2]=pc+1;
      pc = o;
      break;
    case 16:
      /* braz */
      fprintf(fichier_sortie,"braz\n");
      if(reg2==0)
	{
	  pc = o;
	}
      break;
    case 17:
      /* branz */
      fprintf(fichier_sortie,"branz\n");
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
=======
      printf("or\n");
      regs[reg2] = regs[reg1]+o;
      break;
    case 7:
      /* xor */
      printf("xor\n");
      break;
    case 8:
      /* shl */
      printf("shl\n");
      break;
    case 9:
      /* shr */
      printf("shr\n");
      break;
    case 10:
      /* slt */
      printf("slt\n");
      break;
    case 11:
      /* sle */
      printf("sle\n");
      break;
    case 12:
      /* seq */
      printf("seq\n");
      break;
    case 13:
      /* load */
      printf( "load r%d a r%d + #%d\n", reg2, reg1, o );
      regs[reg2] = regs[reg1]+o;
      break;
    case 14:
      /* store */
      printf("store\n");
      break;
    case 15:
      /* jmp */
      printf("jmp\n");
      break;
    case 16:
      /* braz */
      printf("braz\n");
      break;
    case 17:
      /* branz */
      printf("branz\n");
      break;
    case 18:
      /* scall */
      printf("scall\n");
      break;
    case 19:
      /* stop */
      printf("Stop\n");
      running = 0;
      break;
    default:
      printf("error!!\n");
>>>>>>> dd45038043933b22af22f9f773a2f078940e860b
      break;
    }
}

/* display all registers as 4-digit hexadecimal words */
void showRegs()
{
  int i;
<<<<<<< HEAD
  fprintf(fichier_sortie, "regs = " );
  for( i=0; i<NUM_REGS; i++ )
    fprintf(fichier_sortie, "%08X ", regs[ i ] );
  fprintf(fichier_sortie, "\n" );
=======
  printf( "regs = " );
  for( i=0; i<NUM_REGS; i++ )
    printf( "%08X ", regs[ i ] );
  printf( "\n" );
>>>>>>> dd45038043933b22af22f9f773a2f078940e860b
}

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

<<<<<<< HEAD
void afficher(char file_output[50])
{
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


int main( int argc, char * argv[] )
{
  int opt;
  char file_input[50] = "test";
  char file_output[50] = "toto";
  
  while((opt = getopt(argc,argv,"i:o:h"))!= -1)
    {
      switch(opt)
	{
	case 'i':
	  strcpy(file_input,optarg);
	  break;
	case 'o':
	  strcpy(file_output,optarg);
	  break;
	case '?':
	  return 0;
	  break;
	case 'h':
	  system("cat help");
	  return 0;
	  break;
	}
    }
  fichier_sortie = fopen(file_output,"w");
  system("cat bonjour");
  run();
  fclose(fichier_sortie);
  afficher(file_output);
=======
int main( int argc, const char * argv[] )
{
  run();
>>>>>>> dd45038043933b22af22f9f773a2f078940e860b
  return 0;
}
