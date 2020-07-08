#include <msp430.h>
#include "sysfunc.h"

void Init_System(){
	P1DIR |= (nSS + nWR_nRST + MCU_SEL_0 + MCU_SEL_1);
	DB_DIR = 0x00; 
}

void Init_System_Clock(){
	volatile byte i;
	BCSCTL1 &= ~XT2OFF;                       
	do{
		IFG1 &= ~OFIFG;                       
		for (i = 0xFF; i > 0; i--);           
	}
	while ((IFG1 & OFIFG));                   
	BCSCTL2 |= SELM_2 | SELS;                 
}

void wait_1ms(word cnt){
  for (wait_i = 0; wait_i < cnt; wait_i++)
    for (wait_j = 0; wait_j < 1000; wait_j++);
}

void wait_1mks(word cnt){
  for (wait_i = 0; wait_i < cnt; wait_i++);
}
