/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 21/10/2021
* Name: external_interrupt.c 
==============================================================================
*/

#include "button.h"

/* used to initialize all necessary sequence for button */
void BUTTON_init(const button_config_t * buttonConfig){
    if(buttonConfig->internal_resistor != GPIO_INTERNAL_RESISTOR_DISABLED){
        GPIO_setPinDirection(buttonConfig->port_number, buttonConfig->pin_number, PIN_INPUT_INTERNAL_PULLUP);
    } else {
        GPIO_setPinDirection(buttonConfig->port_number, buttonConfig->pin_number, PIN_INPUT);
    }
}


/* used to return the state of a button whether it's HIGHT OR LOW */
uint8 BUTTON_getState(const button_config_t * buttonConfig){
    /* Always -HIGH for pressed
     *        -LOW for not pressed 
     */
    if(buttonConfig->button_connection == BUTTON_PULLDOWN_CONNECTION){
        /* When the button is pressed, the uc should read HIGH */
        if(GPIO_readPin(buttonConfig->port_number, buttonConfig->pin_number)){
            return HIGH;
        } else {
            /* the button is not pressed */
            return LOW;
        }
    } else {
        /* PULL-UP Configuration */
        /* When the button is pressed, the uc should read LOW */
        if(GPIO_readPin(buttonConfig->port_number, buttonConfig->pin_number) == 0){
            return HIGH;
        } else {
            /* the button is not pressed */
            return LOW;
        }
    }
}
