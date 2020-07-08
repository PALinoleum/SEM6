#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"


#define COUNT_OF_NUMBERS 50
// speed = 0 - 38400, 1 - 57600, 2 - 115200 - скорость обмена
// databits = 7, 8 - длина символа
// stopbits = 1, 2 - кол-во передаваемых стоповых бит
// parity = 0 - без контроля четности, 1 - контроль четности, нечетый, 2 - четный
// iface = 0 - USB, 1 - оптика
void main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    Init_System_Clock();
    UART_init(7,1,0,0);
    UART_message("Ready to transmit\n");

    int i;
    char numbers[COUNT_OF_NUMBERS];
    for(i = 0;i<COUNT_OF_NUMBERS;i++){
        numbers[i] = UART_getbyte();
        UART_sendbyte(numbers[i]);
    }
    while(1);
}
