#include <msp430.h>
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

void main(void)
{
    _enable_interrupt();
    WDTCTL = WDTPW + WDTHOLD;
    Init_System_Clock();
    Init_System();
    Init_I2C();
    int f = 0;
    char k_stop = '0', KEYS_last;
    while(f!=1)
    {
        KEYS_last = KEYS_scannow();
        if ((KEYS_last == '*') && (k_stop == '#')) f = 1;
        if ((KEYS_last == '#' )&& (k_stop == '*') )f = 1;
        k_stop = KEYS_last;
        if (KEYS_last == '9') LED_set(1);
        if (KEYS_last == '0') LED_set(2);
        if (KEYS_last == '1') LED_set(3);
        wait_1ms(50);
        LED_reset(1);
        LED_reset(2);
        LED_reset(3);
    }
    LED_reset(1);
    LED_reset(2);
    LED_reset(3);
}
