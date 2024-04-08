/*
 * MCAL.h
 *
 *  Created on: Sep 6, 2023
 *      Author: Mohamed Abdelmawgoud
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
// Define control pins and data pins
#define LCD_RS PB1  // Register select
#define LCD_RW PB2  // Read/write
#define LCD_EN PB3  // Enable
#define LCD_DATA_PORT PORTA  // Data port for 4-bit mode

// Bitwise operations.
#define SET(REG,bit) REG |= ((1)<<bit)
#define CLEAR(REG,bit) REG &= ~((1)<<bit)
#define TOGGLE(REG,bit) REG ^= ((1)<<bit)
#define GET(REG,bit) ((REG)&((1)<<(bit)))

// Function to send a command to the LCD
void lcd_command(uint8_t  cmd);

// Function to send a data byte to the LCD
void lcd_data(uint8_t  data);

// Function to initialize the LCD
void lcd_init();

// Function to clear the LCD screen
void lcd_clear();

// Function to move the cursor to a specific position
void LCD_GoTO_Row_Colunmn(char Row,char Column);

// Function to display a string on the LCD
void lcd_puts(char *str);



#endif /* LCD_H_ */
