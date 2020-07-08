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
    float hum, last_hum = 0;
    while(1){
        hum = HIH_get_hum();
        if (hum != last_hum){
            LCD_clear();
            sprintf (message, "%5.3f", hum);
            LCD_message(message);
            last_hum = hum;
        }
        wait_1ms(100);
    }
}
