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
#define HALFS_PER_PORT 2
#define INTERNAL_RESISTOR 1
/*
==============================================================================
*                                   TYPES
==============================================================================
*/

typedef enum{
    GPIO_FIRST_HALF,
    GPIO_SECOND_HALF,
} GPIO_half_port_number_t;

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
} GPIO_pin_mode_t;

typedef enum{
    PORT_OUTPUT,
    PORT_INPUT,
    PORT_INPUT_INTERNAL_PULLUP,
} GPIO_port_mode_t;

typedef enum{
    GPIO_INTERNAL_RESISTOR_DISABLED,
    GPIO_INTERNAL_PULLUP_ENABLED,
} GPIO_internal_resistor_t;

/*
==============================================================================
*                                Function Prototypes  
==============================================================================
*/

/*
==============================================================================
*                                PIN Related Functions  
==============================================================================
*/

/* Setup the direction of a specific pin to be output / input or input with internal
 * pull-up resistor
 * if the port/pin number is not correct, the request is not handled
 */
void GPIO_setPinDirection(GPIO_port_number_t portNumber, GPIO_pin_number_t pinNumber, GPIO_pin_mode_t pinConfig);

/* Write the logical value into a specific pin if the port/pin number is not correct,
 * the request is not handled
 */
void GPIO_writePin(GPIO_port_number_t portNumber, GPIO_pin_number_t pinNumber, uint8 pinValue);

/* Read the logical value from a specific pin
 * if the port/pin number is not correct, the function will return 0
 */
uint8 GPIO_readPin(GPIO_port_number_t porNumber, GPIO_pin_number_t pinNumber);

/*
==============================================================================
*                            FULL-PORT Related Functions  
==============================================================================
*/

/* Setup the direction of a specific port(FULL port) to be output / input or input with internal
 * pull-up resistor
 * if the port number is not correct, the request is not handled
 */
void GPIO_setPortDirection(GPIO_port_number_t portNumber, GPIO_port_mode_t portConfig);

/* Write the logical value into a specific port if the port number is not correct,
 * the request is not handled
 */
void GPIO_writePort(GPIO_port_number_t pornNumber, uint8 portValue);

/* Read the logical value from a specific port
 * if the port number is not correct, the function will return 0
 */
uint8 GPIO_readPort(GPIO_port_number_t portNumber);

/*
==============================================================================
*                            HALF-PORT Related Functions  
==============================================================================
*/
/* HALF PORT NOTICE: 
 * in ATMega16 the port consists of 8 pins meaning that half of the port is 4 pins. 
 * The first 4 pins could be distinguished by first half and the second 4 pins could
 * be distinguished by second half.
 */


/* Setup the direction of a specific port(HALF port) to be output / input or input with internal
 * pull-up resistor
 * if the port number is not correct, the request is not handled 
 */
void GPIO_setHalfPortDirection(GPIO_port_number_t portNumber, GPIO_port_mode_t portConfig, GPIO_half_port_number_t portHalf);

/* Write the logical value into a specific port (HALF of the port) if the port number is not correct,
 * the request is not handled
 */
void GPIO_writeHalfPort(GPIO_port_number_t portNumber, uint8 portValue, GPIO_half_port_number_t portHalf);

/* Read the logical value from a specific port(HALF port)
 * if the port number is not correct, the function will return 0
 */
uint8 GPIO_readHalfPort(GPIO_port_number_t portNumber, GPIO_half_port_number_t portHalf);


#endif /* GPIO_H_ */
