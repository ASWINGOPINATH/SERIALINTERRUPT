/*
 * File:   INTERRUPT.c
 * Author: aswin
 *
 * Created on 21 June, 2024, 11:15 AM
 */

// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>
#include "lcd.h"  // Ensure this path is correct

#define delay for(z=0;z<=50000;z++)

unsigned int z;
int a = 0, b = 0, c = 0;

// Use the correct ISR syntax for XC8
void __interrupt() ISR() {
    if (TMR0IF) {
        a++;
        if (a == 42) {  // Approximately 1 second
            cmd(0x80);
            show("Timer 0 interrupt");
            a = 0;
            delay;
        }
        TMR0IF = 0;  // Clear the TMR0 interrupt flag
    }

    if (TMR1IF) {
        b++;
        if (b == 84) {  // Approximately 2 seconds
            cmd(0xC0);
            show("Timer 1 interrupt");
            b = 0;
            delay;
        }
        TMR1IF = 0;  // Clear the TMR1 interrupt flag
    }

    if (TMR2IF) {
        c++;
        if (c == 2025) {  // Approximately 3 seconds
            cmd(0x80);
            show("Timer 2 interrupt");
            c = 0;
            delay;
        }
        TMR2IF = 0;  // Clear the TMR2 interrupt flag
    }
}

void intr_init() {
    INTCON = 0xE0;  // Enable global interrupts, peripheral interrupts, and TMR0 interrupt
    PIE1 = 0x03;    // Enable TMR1 and TMR2 interrupts
}

void timer_init() {
    OPTION_REG = 0b00000111;  // TMR0: Internal clock, rising edge, prescaler 1:256
    T1CON = 0b00000001;       // TMR1: Prescaler 1:1, oscillator off, internal clock, timer on
    T2CON = 0b01111100;       // TMR2: Postscaler 1:16, prescaler 1:1, timer on
}

void main() {
    lcd_init();    // Initialize the LCD
    timer_init();  // Initialize timers
    intr_init();   // Initialize interrupts
    while (1) {
        cmd(0x01);
    }
}
