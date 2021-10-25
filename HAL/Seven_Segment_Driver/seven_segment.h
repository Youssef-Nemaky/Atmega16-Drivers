/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 25/10/2021
* Name: seven_segment.h
* Program/Purpose: seven_segment.h which includes all typedef/enums/structures and function
  prototypes used in seven_segment.c
==============================================================================
*/

/*
==============================================================================
*                            Include Files
==============================================================================
*/

#include "../../MCAL/Gpio_Driver/gpio.h"

/*
==============================================================================
*                                   TYPES
==============================================================================
*/

typedef struct{
    GPIO_port_number_t portNumber;
    GPIO_half_port_number_t portHalf;
} SEVENSEGMENT_config_t;


