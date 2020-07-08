#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    Init_System_Clock();
    Init_System();

    UART_init(2, 7, 1, 0, 0);

    char i;

    while(1){
        for(i = 10; i < 60; i++){
                UART_sendbyte(i);
            }
        UART_off();
    }

}
