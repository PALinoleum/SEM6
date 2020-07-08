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
    //Выключение сторожевого таймера
    WDTCTL = WDTPW + WDTHOLD;
    //Инициализация таймеров тактирования
    Init_System_Clock();
    Init_System();

    char i = 0;
    char send_str0[] = "Группа ВТ-31";
    char send_str1[] = "Макаров, Фатеев";
    for(i=0;i<sizeof(send_str0);i++){
        send_str0[i] = LCD_recode(send_str0[i]);
    };
    for(i=0;i<sizeof(send_str1);i++){
          send_str1[i] = LCD_recode(send_str1[i]);
    };

    LCD_init();
    LCD_set_pos(0,0);
    LCD_message(send_str0);
    LCD_set_pos(1,0);
    LCD_message(send_str1);

    /*LCD_init();
    byte character[8] = {0b00011111,0b00011011,0b00011011,0b00011011,0b00010111,0b00011101,0b00010111,0b00011101};
    char i;
    for (i = 0;i<8;i++){
        LCD_WriteCommand(0x40 + i);
        LCD_WriteData(character[i]);
    }
    LCD_set_pos(0,0);
    LCD_WriteData(0);

    byte character1[8] = {0b00011111,0b00010001,0b00010001,0b00011111,0b0001001,0b00010001,0b00010001,0b00010001};
    for (i = 0;i<8;i++){
        LCD_WriteCommand(0x48 + i);
        LCD_WriteData(character1[i]);
    }
    LCD_set_cursor(2);
    LCD_set_pos(1,0);
    LCD_WriteData(1);*/
    while(1){};
}
