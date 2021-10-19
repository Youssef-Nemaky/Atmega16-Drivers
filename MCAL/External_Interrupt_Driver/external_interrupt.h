/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 15/10/2021
* Name: external_interrupt.h
* Program/Purpose: external_interrupt.h which includes all typedef/enums/structures and function
  prototypes used in external_interrupt.c
==============================================================================
*/

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

/*
==============================================================================
* import micro_config.h, common_macros.h and std_types.h files
==============================================================================
*/
#include "../Important_Header_Files/micro_config.h"
#include "../Important_Header_Files/common_macros.h"
#include "../Important_Header_Files/std_types.h"
#include "../Gpio_Driver/gpio.h"

/*
==============================================================================
*                                   Definitions
==============================================================================
*/

#define EXTERNAL_INTERRUPT_0_ID 0
#define EXTERNAL_INTERRUPT_1_ID 1
#define EXTERNAL_INTERRUPT_2_ID 2

/*
==============================================================================
*                                   TYPES
==============================================================================
*/
typedef enum {
  EXT_INT_LOW_LVL_TRIGGER,
  EXT_INT_LVL_CHANGE_TRIGGER,
  EXT_INT_FALLING_EDGE_TRIGGER,
  EXT_INT_RISING_EDGE_TRIGGER,
  EXT_INT_FALLING_EDGE_TRIGGER_INTERNAL_PULL_UP,
} external_interrupt_mode_t;

/*
==============================================================================
*                                   Function Prototypes
==============================================================================
*/

/* Set up the required external interrupt mode and enable it
 * Note: only rising and falling edge modes are avaliable for external interrupt 2
 */
void EX_INT_enable(uint8 externalInterruptNumber, external_interrupt_mode_t externalInterruptMode);

/* Disable the required external interrupt by de-initing its registers */
void EX_INT_disable(uint8 externalInterruptNumber);

#endif /* EXTERNAL_INTERRUPT_H_ */
