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




#endif /* GPIO_H_ */
