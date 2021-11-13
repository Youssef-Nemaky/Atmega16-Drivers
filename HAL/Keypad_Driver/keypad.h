/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 12/11/2021
* Name: keypad.h
* Program/Purpose: keypad.h which includes all typedef/enums/structures and function
  prototypes used in keypad.c
==============================================================================
*/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*
==============================================================================
*                              Definitions
==============================================================================
*/
/* Number of Columns */
#define N_COLUMNS 4
/* Number of Rows */
#define N_ROWS  4

/* Use proteus 4x4 keypad or normal 4x4 keypad */
#if (N_COLUMNS == 4)

#define PROTEUS_KEYPAD TRUE /* TRUE OR FALSE VALUE */

#endif

/* Keypad Port ID */
#define KEYPAD_PORT PORTA_ID

/*
==============================================================================
*                       Include gpio.h file
==============================================================================
*/
#include "../../MCAL/Gpio_Driver/gpio.h"


/*
==============================================================================
*                                Function Prototypes  
==============================================================================
*/

uint8 KEYPAD_getPressedKey(void);


#endif /* KEYPAD_H_ */
