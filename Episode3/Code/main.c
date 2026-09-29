// Felix EP3 ? Giving Felix Motion
// PIC18F46K22 | MPLAB X | XC8 Compiler
// LEDs on RD0 (Red), RD1 (Green), RD2 (Yellow)
 
#include <xc.h>
 
// CONFIG ? tell the chip how to start up
#pragma config FOSC = HSMP      // External crystal, high speed
#pragma config PLLCFG = OFF     // No PLL
#pragma config PRICLKEN = ON    // Primary clock enabled
#pragma config WDTEN = OFF      // Watchdog timer off
#pragma config MCLRE = EXTMCLR  // MCLR pin enabled (matches our pull-up)
#pragma config LVP = OFF        // Low voltage programming off
 
#define _XTAL_FREQ 20000000     // 20MHz crystal ? needed for __delay_ms()

// Motor direction pins
#define IN1   LATDbits.LATD4
#define IN2   LATDbits.LATD5

// Status LEDs
#define LED_RED    LATDbits.LATD0
#define LED_GREEN  LATDbits.LATD1
#define LED_YELLOW LATDbits.LATD2

void LED_Set(uint8_t red, uint8_t green, uint8_t yellow) {
    LED_RED    = red;
    LED_GREEN  = green;
    LED_YELLOW = yellow;
}

void PWM_Init(void) {
    TRISCbits.TRISC2 = 0;
    CCP1CON = 0x0F;
    PR2 = 249;                  // 5kHz at 20MHz
    T2CON = 0x04;
}

void PWM_SetDuty(uint8_t duty) {
    CCPR1L = duty >> 2;
    CCP1CONbits.DC1B = duty & 0x03;
}

void Motor_Forward(uint8_t speed) {
    IN1 = 1;
    IN2 = 0;
    PWM_SetDuty(speed);
    LED_Set(0, 1, 0);           // Green
}

void Motor_Reverse(uint8_t speed) {
    IN1 = 0;
    IN2 = 1;
    PWM_SetDuty(speed);
    LED_Set(0, 0, 1);           // Yellow
}

void Motor_Stop(void) {
    IN1 = 0;
    IN2 = 0;
    PWM_SetDuty(0);
    LED_Set(1, 0, 0);           // Red
}
 
void main(void) {
 
    // Direction pins as outputs
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;

    // LED pins as outputs
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;

    PWM_Init();
    Motor_Stop();  
 
    while (1) {
        Motor_Forward(128);
        __delay_ms(2000);

        Motor_Stop();
        __delay_ms(500);

        Motor_Reverse(128);
        __delay_ms(2000);

        Motor_Stop();
        __delay_ms(500);
    }
}