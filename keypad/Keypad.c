/*
 * Keypad.c
 *
 *  Created on: Oct 23, 2016
 *      Author: ESLAM SAID
 */

#include "Keypad.h"

/* * * *c1  c2 c3
 * row1  1  2  3
 * row2  4  5  6
 * row3  7  8  9
 */

/*Keypad initialization*/
void Keypad_init(void)
 {
	/*configure Keypad columns as outputs others as inputs*/
	KEYPAD_PORT_DIR=0xF0;   //DDRA=0xf0

	/*Pull up resistors for all rows*/
	SET_BIT(KEYPAD_PORT_OUT,FIRST_ROW);
	SET_BIT(KEYPAD_PORT_OUT,SECOND_ROW);
	SET_BIT(KEYPAD_PORT_OUT,THIRD_ROW);
	SET_BIT(KEYPAD_PORT_OUT,FOURTH_ROW);

	SET_BIT(KEYPAD_PORT_OUT,FIRST_COL);
	SET_BIT(KEYPAD_PORT_OUT,SECOND_COL);
	SET_BIT(KEYPAD_PORT_OUT,THIRD_COL);
	SET_BIT(KEYPAD_PORT_OUT,FOURTH_COL);

 }
/*Scanning any pressed key */
uint8 Keypad_get_pressed_key(void)
{
	uint8 KeyPressed='q';

	/*First column */
	_delay_ms(5);

	CLEAR_BIT(KEYPAD_PORT_OUT,FIRST_COL);
	SET_BIT(KEYPAD_PORT_OUT,SECOND_COL);
	SET_BIT(KEYPAD_PORT_OUT,THIRD_COL);
	SET_BIT(KEYPAD_PORT_OUT,FOURTH_COL);
	_delay_ms(5); //Configuration Stability

	if(BIT_CLEARED(KEYPAD_PORT_IN,FIRST_ROW)){KeyPressed='1';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,SECOND_ROW)){KeyPressed='4';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,THIRD_ROW)){KeyPressed='7';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,FOURTH_ROW)){KeyPressed='\0';}

	/*Second column */
	SET_BIT(KEYPAD_PORT_OUT,FIRST_COL);
	CLEAR_BIT(KEYPAD_PORT_OUT,SECOND_COL);
	SET_BIT(KEYPAD_PORT_OUT,THIRD_COL);
	SET_BIT(KEYPAD_PORT_OUT,FOURTH_COL);

	_delay_ms(5);

	if(BIT_CLEARED(KEYPAD_PORT_IN,FIRST_ROW)){KeyPressed='2';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,SECOND_ROW)){KeyPressed='5';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,THIRD_ROW)){KeyPressed='8';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,FOURTH_ROW)){KeyPressed='0';}

	/*Third column */
	SET_BIT(KEYPAD_PORT_OUT,FIRST_COL);
	SET_BIT(KEYPAD_PORT_OUT,SECOND_COL);
	CLEAR_BIT(KEYPAD_PORT_OUT,THIRD_COL);
	SET_BIT(KEYPAD_PORT_OUT,FOURTH_COL);


	_delay_ms(5);

	if(BIT_CLEARED(KEYPAD_PORT_IN,FIRST_ROW)){KeyPressed='3';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,SECOND_ROW)){KeyPressed='6';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,THIRD_ROW)){KeyPressed='9';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,FOURTH_ROW)){KeyPressed='#';}

	/*Fourth column */
	SET_BIT(KEYPAD_PORT_OUT,FIRST_COL);
	SET_BIT(KEYPAD_PORT_OUT,SECOND_COL);
	SET_BIT(KEYPAD_PORT_OUT,THIRD_COL);
	CLEAR_BIT(KEYPAD_PORT_OUT,FOURTH_COL);

	_delay_ms(5);

	if(BIT_CLEARED(KEYPAD_PORT_IN,FIRST_ROW)){KeyPressed='+';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,SECOND_ROW)){KeyPressed='-';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,THIRD_ROW)){KeyPressed='*';}
	else if(BIT_CLEARED(KEYPAD_PORT_IN,FOURTH_ROW)){KeyPressed='/';}



return KeyPressed;
}

