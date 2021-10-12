/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 10/10/2021
* Program/Purpose: gpio.h which includes all typedef/enums/structures and function
  prototypes used in gpio.c
==============================================================================
*/

#ifndef GPIO_H_
#define GPIO_H_

/*
==============================================================================
* import micro_config.h, common_macros.h and std_types.h files
==============================================================================
*/
#include "../Important_Header_Files/micro_config.h"
#include "../Important_Header_Files/common_macros.h"
#include "../Important_Header_Files/std_types.h"

/*
==============================================================================
*                                   Definitions
==============================================================================
*/

#define PORT_NUMS 4
#define PINS_PER_PORT 8

/*
==============================================================================
*                                   TYPES
==============================================================================
*/

typedef enum{
    PORTA_ID, 
    PORTB_ID,
    PORTC_ID,
    PORTD_ID,
} GPIO_port_number_t;

typedef enum{
    PIN0_ID,
    PIN1_ID,
    PIN2_ID,
    PIN3_ID,
    PIN4_ID,
    PIN5_ID,
    PIN6_ID,
    PIN7_ID,
} GPIO_pin_number_t;

typedef enum{
    PIN_OUTPUT,
    PIN_INPUT,
    PIN_INPUT_INTERNAL_PULLUP,
} GPIO_pin_config_t;

typedef enum{
    PORT_OUTPUT,
    PORT_INPUT,
    PORT_INPUT_INTERNAL_PULLUP,
} GPIO_port_config_t;


/*
==============================================================================
*                                Function Prototypes  
==============================================================================
*/

/* Setup the direction of a specific pin to be output / input or input with internal
 * pull-up resistor
 * if the port/pin number is not correct, the request is not handled
 */
void GPIO_setPinDirection(GPIO_port_number_t, GPIO_pin_number_t, GPIO_pin_config_t);

/* Write the logical value into a specific pin if the port/pin number is not correct,
 * the request is not handled
 */
void GPIO_writePin(GPIO_port_number_t, GPIO_pin_number_t, uint8 pinValue);

/* Read the logical value from a specific pin
 * if the port/pin number is not correct, the function will return 0
 */
uint8 GPIO_readPin(GPIO_port_number_t, GPIO_pin_number_t);

/* Setup the direction of a specific port(FULL port) to be output / input or input with internal
 * pull-up resistor
 * if the port number is not correct, the request is not handled
 */
void GPIO_setPortDirection(GPIO_port_number_t,GPIO_port_config_t);

/* Write the logical value into a specific port if the port number is not correct,
 * the request is not handled
 */
void GPIO_writePort(GPIO_port_number_t, uint8 portValue);

#endif /* GPIO_H_ */
