#include <msp430.h> 
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"

// ��������� �������� � ��������� ������������ �������������� �������������� �������-��������� �������������� ������� �� ����� P6.2.

unsigned result = 0;

void ADC_init(){
    P6SEL |= BIT1;
    ADC12CTL1 = SHP + CSTARTADD_0 + CONSEQ1;
    ADC12MCTL0 = SREF_3 + INCH_1;

    ADC12IE |= BIT1;
    ADC12CTL0 |= ENC;
    ADC12CTL0 |= ADC12ON + ADC12SC;
}

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    _enable_interrupt();
    Init_System_Clock();
    Init_System();
    ADC_init();
    while(1);
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC_interrupt(void){
    ADC12CTL0 &= ~ENC;
    result = ADC12MEM0;     // ��������� ���������
    ADC12CTL0 |= ENC;
}

