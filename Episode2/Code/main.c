// Felix EP2 ? Giving Felix A Brain
// PIC18F46K22 | MPLAB X | XC8 Compiler
// LEDs on RD0 (Red), RD1 (Green), RD2 (Yellow)
 
#include <xc.h>
 
// CONFIG - tell the chip how to start up
#pragma config FOSC = HSMP      // External crystal, high speed
#pragma config PLLCFG = OFF     // No PLL
#pragma config PRICLKEN = ON    // Primary clock enabled
#pragma config WDTEN = OFF      // Watchdog timer off
#pragma config MCLRE = EXTMCLR  // MCLR pin enabled (matches our pull-up)
#pragma config LVP = OFF        // Low voltage programming off
 
#define _XTAL_FREQ 20000000     // 20MHz crystal ? needed for __delay_ms()

void main(void) {
 
    // Set RD0, RD1, RD2 as outputs(0 = output, 1 = input)
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;

    // Make sure all LEDs start OFF
    LATDbits.LATD0 = 0;
    LATDbits.LATD1 = 0;
    LATDbits.LATD2 = 0;
 
    while (1) {
        // Red on
        LATDbits.LATD0 = 1;
        __delay_ms(500);
        LATDbits.LATD0 = 0;
        
        // Green on
        LATDbits.LATD1 = 1;
        __delay_ms(500);
        LATDbits.LATD1 = 0;
        
        // Yellow on
        LATDbits.LATD2 = 1;
        __delay_ms(500);
        LATDbits.LATD2 = 0;
        
        // All on together
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 1;
        LATDbits.LATD2 = 1;
        __delay_ms(500);
        
        // All off
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 0;
        __delay_ms(500);
    }
}