#include <msp430.h> 
#include "system_define.h"
#include "system_variable.h"
#include "function_prototype.h"
#include "main.h"
#include "keys.h"

#define KEYS_i2c_addr 0x73
/*
 * main.c
 */
char state = 0;
char key_press = 0;
char _key = 0;
int delay = 0;

void Custom_Speed_Init_I2C(){
    P3SEL |= 0x0A;           // Р’С‹Р±РѕСЂ Р°Р»СЊС‚РµСЂРЅР°С‚РёРІРЅРѕР№ С„СѓРЅРєС†РёРё РґР»СЏ Р»РёРЅРёР№ РїРѕСЂС‚Р° P3
                            // РІ СЂРµР¶РёРјРµ I2C SDA->P3.1, SCL->P3.3
    U0CTL |= I2C + SYNC;     // Р’С‹Р±СЂР°С‚СЊ СЂРµР¶РёРј I2C РґР»СЏ USART0
    U0CTL &= ~I2CEN;         // Р’С‹РєР»СЋС‡РёС‚СЊ РјРѕРґСѓР»СЊ I2C
    // РљРѕРЅС„РёРіСѓСЂР°С†РёСЏ РјРѕРґСѓР»СЏ I2C
    I2CTCTL=I2CSSEL_2;      // SMCLK
    // РЅСѓР¶РЅРѕ СѓСЃС‚Р°РЅРѕРІРёС‚СЊ 60000 Р“С† 
    //(psc+1)(sclh+1) = 133.333333333
    I2CPSC = 0; //РїСЂРµРґРµР»РёС‚РµР»СЊ С‚Р°РєС‚РѕРІРѕР№ С‡Р°СЃС‚РѕС‚С‹ 
    I2CSCLH = 133;         // High period of SCL
    I2CSCLL = 133;         // Low period of SCL
    U0CTL |= I2CEN;         // Р’РєР»СЋС‡РёС‚СЊ РјРѕРґСѓР»СЊ I2C
    // С„РѕСЂРјРёСЂРѕРІР°РЅРёРµ СЃС‚СЂРѕР±Р° СЃР±СЂРѕСЃР° I2C-СЂРµРіРёСЃС‚СЂРѕРІ PCA9538 - RST_RG1->P3.1 Рё RST_RG2->P3.2
    P3DIR |= 0x05;            // РїРµСЂРµРєР»СЋС‡Р°РµРј СЌС‚Рё РЅРѕР¶РєРё РїРѕСЂС‚Р° РЅР° РІС‹РІРѕРґ,
    P3SEL &= ~0x05;           //   РІС‹Р±РёСЂР°РµРј С„СѓРЅРєС†РёСЋ РІРІРѕРґР°-РІС‹РІРѕРґР° РґР»СЏ РЅРёС…
    P3OUT &= ~0x05;           //   Рё С„РѕСЂРјРёСЂСѓРµРј СЃС‚СЂРѕР± СЃР±СЂРѕСЃР° РЅР° 1 РјСЃ
    wait_1ms(1);
    P3OUT |= 0x05;
};

void reset_keyboard(){
    I2C_WriteByte(0x03,0x0F,KEYS_i2c_addr);
    I2C_WriteByte(0x01,0x0F,KEYS_i2c_addr);
};

void set_keyboard(){
    I2C_WriteByte(0x03,0x0F,KEYS_i2c_addr);
    I2C_WriteByte(0x01,0xFF,KEYS_i2c_addr);
};

void scan_key(){
    key_press = 0;
    key = KEYS_scannow();
            switch(_key){
                case '1':
                    delay-=15;
                    break;
                case '2':
                    delay+=15;
                    break;
                case '0':
                    LED_clear();
                    state = 1;
                    break;
                case '*':
                    LED_clear();
                    state = 0;
                    break;
                case '#':
                    LED_clear();
                    state = 2;
                    break;
            }
            reset_keyboard();
};

#pragma vector=PORT1_VECTOR
__interrupt void keyboard_interrupt(void)
{
    key_press = 1;
    P1IFG &= ~BIT7;
};

void main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    Custom_Speed_Init_I2C();
    P1IE |= BIT7;
    P1IFG &= !BIT7;
    P1IES |= BIT7;
    __enable_interrupt();

    Init_I2C();
    LED_clear();
    reset_keyboard();
    while(1){
        if(key_press){
            scan_key();
        }
        switch(state){
            case 0:
                LED_fx1(delay);
                break;
            case 1:
                LED_fx2(delay);
                break;
            case 2:
                break;
        };
    };
}


