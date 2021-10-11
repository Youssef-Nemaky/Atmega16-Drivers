/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 10/10/2021
* Program/Purpose: 
==============================================================================
*/

#include "gpio.h"

/* Setup the direction of a specific pin to be output / input or input with internal
 * pull-up resistor
 * if the port/pin number is not correct, the request is not handled
 */
void GPIO_setPinDirection(GPIO_port_number_t portNumber, GPIO_pin_number_t pinNumber, GPIO_pin_config_t pinConfig){
    /* Check for valid port/pin number */
    if((portNumber >= PORT_NUMS) || (pinNumber >= PINS_PER_PORT)){
        /* There should be some sort of error handling */
        /* Do Nothing */
    } else {
        switch (portNumber)
        {
        case PORTA_ID:
            switch (pinConfig)
            {
            case PIN_OUTPUT:
                CLEAR_BIT(DDRA, pinNumber);
                break;
            case PIN_INPUT:
                SET_BIT(DDRA, pinNumber);
                break;
            case PIN_INPUT_INTERNAL_PULLUP:
                SET_BIT(PORTA, pinNumber);
                break;
            }
            break;
        case PORTB_ID:
            switch (pinConfig)
            {
            case PIN_OUTPUT:
                CLEAR_BIT(DDRB, pinNumber);
                break;
            case PIN_INPUT:
                SET_BIT(DDRB, pinNumber);
                break;
            case PIN_INPUT_INTERNAL_PULLUP:
                SET_BIT(PORTB, pinNumber);
                break;
            }
            break;
        case PORTC_ID:
            switch (pinConfig)
            {
            case PIN_OUTPUT:
                CLEAR_BIT(DDRC, pinNumber);
                break;
            case PIN_INPUT:
                SET_BIT(DDRC, pinNumber);
                break;
            case PIN_INPUT_INTERNAL_PULLUP:
                SET_BIT(PORTC, pinNumber);
                break;
            }
            break;
        case PORTD_ID:
            switch (pinConfig)
            {
            case PIN_OUTPUT:
                CLEAR_BIT(DDRD, pinNumber);
                break;
            case PIN_INPUT:
                SET_BIT(DDRD, pinNumber);
                break;
            case PIN_INPUT_INTERNAL_PULLUP:
                SET_BIT(PORTD, pinNumber);
                break;
            }
            break;
    }
}


/* Write the logical value into a specific pin if the port/pin number is not correct,
 * the request is not handled
 */
void GPIO_writePin(GPIO_port_number_t portNumber, GPIO_pin_number_t pinNumber, uint8 pinValue){
    if((portNumber >= PORT_NUMS) || (pinNumber >= PINS_PER_PORT)){
        /* There should be some sort of error handling */
        /* Do Nothing */
    } else {
        switch (portNumber){
        case PORTA_ID:
            if(pinValue){
                SET_BIT(PORTA, pinNumber);
            } else {
                CLEAR_BIT(PORTA, pinNumber);
            }
            break;
        case PORTB_ID:
            if(pinValue){
                SET_BIT(PORTB, pinNumber);
            } else {
                CLEAR_BIT(PORTB, pinNumber);
            }
            break;
        case PORTC_ID:
            if(pinValue){
                SET_BIT(PORTC, pinNumber);
            } else {
                CLEAR_BIT(PORTC, pinNumber);
            }
            break;
        case PORTD_ID:
            if(pinValue){
                SET_BIT(PORTD, pinNumber);
            } else {
                CLEAR_BIT(PORTD, pinNumber);
            }
            break;
        }
    }
}


/* Read the logical value from a specific pin
 * if the port/pin number is not correct, the function will return logic LOW
 */
uint8 GPIO_readPin(GPIO_port_number_t portNumber, GPIO_pin_number_t pinNumber){
    if((portNumber >= PORT_NUMS) || (pinNumber >= PINS_PER_PORT)){
        return LOW;
    } else {
        switch (portNumber){
        case PORTA_ID:
            return bit_is_set(PORTA, pinNumber);
            break;
        case PORTB_ID:
            return bit_is_set(PORTB, pinNumber);
            break;
        case PORTC_ID:
            return bit_is_set(PORTC, pinNumber);
            break;
        case PORTD_ID:
            return bit_is_set(PORTD, pinNumber);
            break;
        }
    }
}