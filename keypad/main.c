/*
 * main.c
 *
 *  Created on: Sep 8, 2023
 *      Author: Mohamed Abdelmawgoud
 */
#include "Keypad.h"
#include "lcd.h"
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>

//Global variable


double calculate(char operator,int operand1,int operand2)
{
	switch(operator)
	{
	case '+' : return (double)(operand1+operand2) ;break ;
	case '-' : return (double)(operand1-operand2); break ;
	case '*' : return (double)(operand1*operand2); break ;
	case '/' : return (double)(operand1/operand2); break ;
	default: return 0;
	}

}

/*void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);

        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}*/

int main()
{
	lcd_init();
	Keypad_init();

	int value1 = 0 ;

	int value2 = 0;

	char operator[2]  ;
	operator[1] = '\0';
	float res = 0 ;
	char input[50] ;

	LCD_GoTO_Row_Colunmn(0,0);
	lcd_puts("Welcome to");
	LCD_GoTO_Row_Colunmn(1,0);
	lcd_puts("Calculator :)");
	_delay_ms(6000);

	lcd_clear();
	LCD_GoTO_Row_Colunmn(0,0);
	lcd_puts("Enter operand1");
	LCD_GoTO_Row_Colunmn(1,0);
	lcd_puts("followed by *");
	_delay_ms(6000);

	lcd_clear();
	LCD_GoTO_Row_Colunmn(0,0);
	lcd_puts("then operator");
	_delay_ms(6000);

	lcd_clear();
	LCD_GoTO_Row_Colunmn(0,0);
	lcd_puts("then operand2");
	LCD_GoTO_Row_Colunmn(1,0);
	lcd_puts("followed by *");
	_delay_ms(6000);


	lcd_clear();
	LCD_GoTO_Row_Colunmn(0,0);
	lcd_puts("Press # to clear");
	_delay_ms(6000);
	lcd_clear();
	while(1)
	{
		LCD_GoTO_Row_Colunmn(0,0);
		lcd_puts("Start now! :)");
		uint8 key = 'q' ;
		uint8 op1 = 'q' ;
		uint8 op2  = 'q';
		int want_clear = 0 ;
		int count = 2 ; // counts the number of cells taken by operand1.
		do{
			op1 = Keypad_get_pressed_key();
			if(op1 == '#')
			{
				lcd_clear();
				want_clear = 1 ;
				break ;
			}
		}while(op1 == 'q');
		if(want_clear)
		{
			continue;
		}
		LCD_GoTO_Row_Colunmn(1,0);
		lcd_puts(itoa(op1-48,input,10));
		_delay_ms(500);

		value1 = (int)(op1-48);
		while(key != '\0')
		{
			key = Keypad_get_pressed_key() ;
			if(key == '\0')
			{
				break ;
			}
			if(key == '#')
			{
				lcd_clear();
				want_clear = 1 ;
				break ;
			}

			value1 = (key == 'q')?(value1):(value1*10+ (key-48));
			if(key != 'q'){
				count++;
				LCD_GoTO_Row_Colunmn(1,0);
				lcd_puts(itoa(value1,input,10));
				_delay_ms(500);
			}

		}
		if(want_clear)
		{
			continue;
		}

		_delay_ms(500);
		do{
			operator[0] = Keypad_get_pressed_key();
			if(operator[0] == '#')
			{
				lcd_clear();
				want_clear = 1 ;
				break ;
			}
		}while(operator[0] == 'q');
		if(want_clear)
		{
			continue;
		}
		lcd_puts(operator);
		_delay_ms(500);


		do{
			op2 = Keypad_get_pressed_key();
			if(op2 == '#')
			{
				lcd_clear();
				want_clear = 1 ;
				break ;
			}
		}while(op2 == 'q');
		if(want_clear)
		{
			continue;
		}

		LCD_GoTO_Row_Colunmn(1,count);
		lcd_puts(itoa(op2-48,input,10));
		_delay_ms(500);

		key = 'q';
		value2 = (int)(op2-48);
		while(key != '\0')
		{
			key = Keypad_get_pressed_key() ;
			if(key == '\0')
			{
				break ;
			}

			if(key == '#')
			{
				lcd_clear();
				want_clear = 1 ;
				break ;
			}

			value2 = (key == 'q')?(value2):(value2*10+ (key-48));
			if(key != 'q'){
				LCD_GoTO_Row_Colunmn(1,count);
				lcd_puts(itoa(value2,input,10));
				_delay_ms(500);
			}

		}

		if(want_clear)
		{
			continue;
		}

		lcd_puts(" = ");

		res = calculate(operator[0],value1,value2);
		itoa(res,input,10);
		lcd_puts(input);
		_delay_ms(500);

	}

	return 0 ;
}
