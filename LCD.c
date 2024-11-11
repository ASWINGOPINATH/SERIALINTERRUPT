/*
 * File:   LCD.c
 * Author: aswin
 *
 * Created on 21 June, 2024, 11:25 AM
 */


// lcd.c
#include <xc.h>
#include "lcd.h"

void lcd_init(void) {
    // Initialization sequence for the LCD
    // Replace with the actual initialization code for your LCD
    TRISD = 0x00;  // Set PORTD as output
    cmd(0x38);     // Function set: 8-bit, 2 lines, 5x7 dots
    cmd(0x0C);     // Display on, Cursor off
    cmd(0x01);     // Clear display
    cmd(0x06);     // Entry mode, auto increment with no shift
}

void cmd(unsigned char cmd) {
    // Send command to LCD
    // Replace with the actual code to send a command to your LCD
    PORTD = cmd;
    RD2 = 0;  // RS = 0 for command
    RD3 = 1;  // Enable pulse
    __delay_ms(2);
    RD3 = 0;
}

void show(const char *s) {
    // Display a string on the LCD
    // Replace with the actual code to display a string on your LCD
    while (*s) {
        PORTD = *s++;
        RD2 = 1;  // RS = 1 for data
        RD3 = 1;  // Enable pulse
        __delay_ms(2);
        RD3 = 0;
    }
}
