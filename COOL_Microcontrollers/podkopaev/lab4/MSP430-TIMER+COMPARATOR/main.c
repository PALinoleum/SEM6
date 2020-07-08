#include <msp430.h> 
#include "stdio.h"
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

void main(void) {
    WDTCTL = WDTPW|WDTHOLD;
    Init_System_Clock();
    Init_System();
    _enable_interrupt();
    LCD_init();
    char message[32];
    unsigned res, last_res = 0;
    while(1){
        res = R22_get_resistance();
        if (res != last_res){
            LCD_clear();
            sprintf (message, "%u", res);
            LCD_message(message);
            last_res = res;
        }
        wait_1ms(100);
    }
}
