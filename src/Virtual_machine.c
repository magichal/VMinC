#include <stdio.h>
#include "opcode.h"

#define NUM_REGS 5
#define NUM_BITS 32

void showRegs(){
	
	int i;
	prinf(" Etat des registres : ");
	for(i=0;i<NUM_REGS;i++)
		printf("%04X",reg[i]);
		printf("\n");
	}
	


int main(int argc, const char * argv[] ){

	unsigned regs[ NUM_REGS ];
	unsigned program[]={0xff,0xA3}; /* Premiere etape */
	
	run(hexa);
	showreg();
	
	return 0;
	
	}
