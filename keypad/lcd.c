/*
 * lcd.c
 *
 *  Created on: Sep 6, 2023
 *      Author: Mohamed Abdelmawgoud
 */
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

void lcd_command(uint8_t cmd) {

    PORTB &= ~(1 << LCD_RS);       // RS = 0 for command
    PORTB &= ~(1 << LCD_RW);       // RW = 0 for write
    PORTB |= (1 << LCD_EN);        // Enable LCD
    _delay_ms(1);
    LCD_DATA_PORT = (cmd & 0xF0);  // Send the higher nibble
    _delay_ms(1);
    PORTB &= ~(1 << LCD_EN);       // Disable LCD

    _delay_ms(2);  // Delay for command execution

    PORTB |= (1 << LCD_EN);              // Enable LCD
    _delay_ms(1);
    LCD_DATA_PORT = ((cmd << 4) & 0xF0);  // Send the lower nibble

    PORTB &= ~(1 << LCD_EN);             // Disable LCD

    _delay_ms(2);  // Delay for command execution
}

// Function to send a data byte to the LCD
void lcd_data(uint8_t data) {
    PORTB |= (1 << LCD_RS);        // RS = 1 for data
    PORTB &= ~(1 << LCD_RW);       // RW = 0 for write
    PORTB |= (1 << LCD_EN);        // Enable LCD
    _delay_ms(1);
    LCD_DATA_PORT = (data & 0xF0);  // Send the higher nibble
    _delay_ms(1);
    PORTB &= ~(1 << LCD_EN);       // Disable LCD

    _delay_ms(2);  // Delay for data write

    PORTB |= (1 << LCD_EN);              // Enable LCD
    _delay_ms(1);
    LCD_DATA_PORT = ((data << 4) & 0xF0);  // Send the lower nibble
    _delay_ms(1);
    PORTB &= ~(1 << LCD_EN);             // Disable LCD
    _delay_ms(2);  // Delay for data write
}

// Function to initialize the LCD
void lcd_init() {
    // Initialize control pins as outputs
    DDRB |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN);

    // Initialize data pins as outputs
    DDRA |= 0xF0;

    // Wait for the LCD to power up (at least 15ms)
    _delay_ms(15);

    // Function Set: 4-bit mode, 2 lines, 5x8 font size
    lcd_command(0x28);

    // Display On/Off Control: Display on, Cursor off, Blink off
    lcd_command(0x0C);

    // Clear the display and return home
    lcd_command(0x01);
    _delay_ms(2);

    // Entry Mode Set: Increment cursor position, No display shift
    lcd_command(0x06);
}

// Function to clear the LCD screen
void lcd_clear() {
    lcd_command(0x01);  // Clear display
    _delay_ms(2);
}

// Function to move the cursor to a specific position
void LCD_GoTO_Row_Colunmn(char Row,char Column)
{
	unsigned char address=0;

	switch (Row)
	{
	case 0:address =(Column);break;
	case 1:address =(Column+0x40);break;
	}
	lcd_command(address|(0x80));   // load address counter by 0x80 (|or) load address of start
}
// Function to display a string on the LCD
void lcd_puts(char *str) {

	while(*str != '\0')
	{
		lcd_data(*str);
		str++ ;

	}
}
