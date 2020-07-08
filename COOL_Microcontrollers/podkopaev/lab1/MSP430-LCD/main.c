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
    Init_System_Clock();
    Init_System();
    WDTCTL = WDTPW + WDTHOLD;
    LCD_init();

    LCD_message(" ��-31 ��������� ����� ");


    LCD_WriteCommand(0x40);
    LCD_WriteData(0b000011111);

    LCD_WriteCommand(0x41);
    LCD_WriteData(0b000010001);

    LCD_WriteCommand(0x42);
    LCD_WriteData(0b00010001);

    LCD_WriteCommand(0x43);
    LCD_WriteData(0b00000100);

    LCD_WriteCommand(0x44);
    LCD_WriteData(0b00001010);

    LCD_WriteCommand(0x45);
    LCD_WriteData(0b00010001);

    LCD_WriteCommand(0x46);
    LCD_WriteData(0b00001110);

    LCD_WriteCommand(0x47);
    LCD_WriteData(0b00010001);

    LCD_set_pos(0,0);
    LCD_WriteByte(0,1);


    while(1){
    }
}
