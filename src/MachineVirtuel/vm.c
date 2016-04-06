#include <stdio.h>

#define NUM_REGS 5
unsigned regs[ NUM_REGS ];

unsigned program[] = { 0x68600141, 0x68600142 , 0x98000000};

/* program counter */
int pc = 0;

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
      regs[reg2] = regs[reg1]&o;
      break;
    case 6:
      /* or */
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
      break;
    }
}

/* display all registers as 4-digit hexadecimal words */
void showRegs()
{
  int i;
  printf( "regs = " );
  for( i=0; i<NUM_REGS; i++ )
    printf( "%08X ", regs[ i ] );
  printf( "\n" );
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

int main( int argc, const char * argv[] )
{
  run();
  return 0;
}
