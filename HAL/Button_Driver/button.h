/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 21/10/2021
* Name: external_interrupt.h
* Program/Purpose: button.h which includes all typedef/enums/structures and function
  prototypes used in button.c
==============================================================================
*/

#ifndef BUTTON_H_
#define BUTTON_H_

/*
==============================================================================
* Include gpio.h file
==============================================================================
*/
#include "../../MCAL/Gpio_Driver/gpio.h"

/*
==============================================================================
*                                   TYPES
==============================================================================
*/
typedef enum {
	BUTTON_PULLUP_CONNECTION,
	BUTTON_PULLDOWN_CONNECTION,
} button_connection_t;

typedef struct {
	GPIO_port_number_t port_number;
	GPIO_pin_number_t pin_number;
	button_connection_t button_connection;
	/* In case the target UC has internal resistor modes */
	#ifdef INTERNAL_RESISTOR
	GPIO_internal_resistor_t internal_resistor;
	#endif
} button_t;

/*
==============================================================================
*                                Function Prototypes  
==============================================================================
*/
/* used to initialize all necessary sequence for button */
void BUTTON_init(const button_t * buttonConfig);

/* used to return the state of a button whether it's HIGHT OR LOW */
uint8 BUTTON_getState(const button_t *);

#endif /* BUTTON_H_ */
