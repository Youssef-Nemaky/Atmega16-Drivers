/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 21/10/2021
* Name: external_interrupt.c 
==============================================================================
*/

#include "button.h"

/* used to initialize all necessary sequence for button */
void BUTTON_init(const button_t * buttonConfig){
    if(buttonConfig->internal_resistor != GPIO_INTERNAL_RESISTOR_DISABLED){
        GPIO_setPinDirection(buttonConfig->port_number, buttonConfig->pin_number, PIN_INPUT_INTERNAL_PULLUP);
    } else {
        GPIO_setPinDirection(buttonConfig->port_number, buttonConfig->pin_number, PIN_INPUT);
    }
}

