/*
 * Keypad.h
 *
 *  Created on: Oct 23, 2016
 *      Author: ESLAM SAID
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO.h"
#include "PLATFORM_TYPES.h"
#include <avr/io.h>
#include <util/delay.h>

/*Wiring diagram*/

/* * * *c1  c2 c3 c4
 * row1  1  2  3  A
 * row2  4  5  6  B
 * row3  7  8  9  C
 * row4  *  0  #  D
 */

#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC

#define FIRST_ROW  (0)
#define SECOND_ROW (1)
#define THIRD_ROW  (2)
#define FOURTH_ROW (3)
#define FIRST_COL  (4)
#define SECOND_COL (5)
#define THIRD_COL  (6)
#define FOURTH_COL (7)

void  Keypad_init(void);
uint8 Keypad_get_pressed_key(void);
int Keypad_get_pressed_int(void);


#endif /* KEYPAD_H_ */
