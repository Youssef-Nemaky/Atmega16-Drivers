/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 10/10/2021
* Program/Purpose: 
==============================================================================
*/

#include "gpio.h"

/*
==============================================================================
*                            PIN Related Functions  
==============================================================================
*/

/* Setup the direction of a specific pin to be output / input or input with internal
 * pull-up resistor
 * if the port/pin number is not correct, the request is not handled
 */
void GPIO_setPinDirection(GPIO_port_number_t portNumber, GPIO_pin_number_t pinNumber, GPIO_pin_mode_t pinMode){
    /* Check for valid port/pin number */
    if((portNumber >= PORT_NUMS) || (pinNumber >= PINS_PER_PORT)){
        /* There should be some sort of error handling */
        /* Do Nothing */
    } else {
        switch (portNumber)
        {
        case PORTA_ID:
            switch (pinMode)
            {
            case PIN_OUTPUT:
                SET_BIT(DDRA, pinNumber);
                break;
            case PIN_INPUT:
                CLEAR_BIT(DDRA, pinNumber);
                break;
            case PIN_INPUT_INTERNAL_PULLUP:
                CLEAR_BIT(DDRA, pinNumber);
                SET_BIT(PORTA, pinNumber);
                break;
            }
            break;
        case PORTB_ID:
            switch (pinMode)
            {
            case PIN_OUTPUT:
                SET_BIT(DDRB, pinNumber);
                break;
            case PIN_INPUT:
                CLEAR_BIT(DDRB, pinNumber);
                break;
            case PIN_INPUT_INTERNAL_PULLUP:
                CLEAR_BIT(DDRB, pinNumber);
                SET_BIT(PORTB, pinNumber);
                break;
            }
            break;
        case PORTC_ID:
            switch (pinMode)
            {
            case PIN_OUTPUT:
                SET_BIT(DDRC, pinNumber);
                break;
            case PIN_INPUT:
                CLEAR_BIT(DDRC, pinNumber);
                break;
            case PIN_INPUT_INTERNAL_PULLUP:
                CLEAR_BIT(DDRC, pinNumber);
                SET_BIT(PORTC, pinNumber);
                break;
            }
            break;
        case PORTD_ID:
            switch (pinMode)
            {
            case PIN_OUTPUT:
                SET_BIT(DDRD, pinNumber);
                break;
            case PIN_INPUT:
                CLEAR_BIT(DDRD, pinNumber);
                break;
            case PIN_INPUT_INTERNAL_PULLUP:
                CLEAR_BIT(DDRD, pinNumber);
                SET_BIT(PORTD, pinNumber);
                break;
            }
            break;
        }
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
            return IS_BIT_SET(PINA, pinNumber);
            break;
        case PORTB_ID:
            return IS_BIT_SET(PINB, pinNumber);
            break;
        case PORTC_ID:
            return IS_BIT_SET(PINC, pinNumber);
            break;
        case PORTD_ID:
            return IS_BIT_SET(PIND, pinNumber);
            break;
        }
    }
}

/*
==============================================================================
*                            FULL-PORT Related Functions  
==============================================================================
*/
/* Setup the direction of a specific port(FULL port) to be output / input or input with internal
 * pull-up resistor
 * if the port number is not correct, the request is not handled
 */
void GPIO_setPortDirection(GPIO_port_number_t portNumber,GPIO_port_mode_t portMode){
    if(portNumber >= PORT_NUMS){
        /* There should be some sort of error handling */
        /* Do Nothing */
    } else {
        switch (portNumber){
        case PORTA_ID:
            switch (portMode){
            case PORT_OUTPUT:
                DDRA = MAX_NUMBER_U8_BIT;
                break;
            case PORT_INPUT:
                DDRA = MIN_NUMBER_U8_BIT;
                break;
            case PORT_INPUT_INTERNAL_PULLUP:
                DDRA = MIN_NUMBER_U8_BIT;
                PORTA = MAX_NUMBER_U8_BIT;
                break;
            }
            break;

        case PORTB_ID:
            switch (portMode){
            case PORT_OUTPUT:
                DDRB = MAX_NUMBER_U8_BIT;
                break;
            case PORT_INPUT:
                DDRB = MIN_NUMBER_U8_BIT;
                break;
            case PORT_INPUT_INTERNAL_PULLUP:
                DDRB = MIN_NUMBER_U8_BIT;
                PORTB = MAX_NUMBER_U8_BIT;
                break;
            }
            break;

        case PORTC_ID:
            switch (portMode){
            case PORT_OUTPUT:
                DDRC = MAX_NUMBER_U8_BIT;
                break;
            case PORT_INPUT:
                DDRC = MIN_NUMBER_U8_BIT;
                break;
            case PORT_INPUT_INTERNAL_PULLUP:
                DDRC = MIN_NUMBER_U8_BIT;
                PORTC = MAX_NUMBER_U8_BIT;
                break;
            }
            break;

        case PORTD_ID:
            switch (portMode){
            case PORT_OUTPUT:
                DDRD = MAX_NUMBER_U8_BIT;
                break;
            case PORT_INPUT:
                DDRD = MIN_NUMBER_U8_BIT;
                break;
            case PORT_INPUT_INTERNAL_PULLUP:
                DDRD = MIN_NUMBER_U8_BIT;
                PORTD = MAX_NUMBER_U8_BIT;
                break;
            }
            break;
            
        }
    }
}


/* Write the logical value into a specific port if the port number is not correct,
 * the request is not handled
 */
void GPIO_writePort(GPIO_port_number_t portNumber, uint8 portValue){
    if(portNumber >= PORT_NUMS){
        /* There should be some sort of error handling */
        /* Do Nothing */
    } else {
        switch (portNumber)
        {
        case PORTA_ID:
            PORTA = portValue;    
            break;
        
        case PORTB_ID:
            PORTB = portValue;    
            break;

        case PORTC_ID:
            PORTC = portValue;    
            break;

        case PORTD_ID:
            PORTD = portValue;    
            break;

        }
    }
}


/* Read the logical value from a specific port
 * if the port number is not correct, the function will return 0
 */
uint8 GPIO_readPort(GPIO_port_number_t portNumber){
    if(portNumber >= PORT_NUMS){
        return LOW;
    } else {
        switch (portNumber)
        {
        case PORTA_ID:
            return PINA;
            break;
        
        case PORTB_ID:
            return PINB;
            break;
        
        case PORTC_ID:
            return PINC;
            break;
        
        case PORTD_ID:
            return PIND;
            break;
            
        }
    }
}


/*
==============================================================================
*                           HALF-PORT Related Functions  
==============================================================================
*/

/* Setup the direction of a specific port(HALF port) to be output / input or input with internal
 * pull-up resistor
 * if the port number is not correct, the request is not handled 
 */
void GPIO_setHalfPortDirection(GPIO_port_number_t portNumber, GPIO_port_mode_t portMode, GPIO_half_port_number_t portHalf){
    if( (portNumber >= PORT_NUMS) || (portHalf >= HALFS_PER_PORT) ){
        /* Some sort of error handling */
        /* Do Nothing! */
    } else {
        switch (portNumber){
        case PORTA_ID:
            switch (portMode){
            case PORT_OUTPUT:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRA |= 0x0F;
                    break;
                case GPIO_SECOND_HALF:
                    DDRA |= 0xF0;
                    break;
                }
                break;
            case PORT_INPUT:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRA &= 0xF0;
                    break;
                case GPIO_SECOND_HALF:
                    DDRA &= 0x0F;
                    break;
                }
                break;
            case PORT_INPUT_INTERNAL_PULLUP:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRA &= 0xF0;
                    PORTA |= 0x0F;
                    break;
                case GPIO_SECOND_HALF:
                    DDRA &= 0x0F;
                    PORTA |= 0xF0;
                    break;
                }
                break;
            }
            break;

        case PORTB_ID:
            switch (portMode){
            case PORT_OUTPUT:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRB |= 0x0F;
                    break;
                case GPIO_SECOND_HALF:
                    DDRB |= 0xF0;
                    break;
                }
                break;
            case PORT_INPUT:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRB &= 0xF0;
                    break;
                case GPIO_SECOND_HALF:
                    DDRB &= 0x0F;
                    break;
                }
                break;
            case PORT_INPUT_INTERNAL_PULLUP:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRB &= 0xF0;
                    PORTB |= 0x0F;
                    break;
                case GPIO_SECOND_HALF:
                    DDRB &= 0x0F;
                    PORTB |= 0xF0;
                    break;
                }
                break;
            }
            break;

        case PORTC_ID:
            switch (portMode){
            case PORT_OUTPUT:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRC |= 0x0F;
                    break;
                case GPIO_SECOND_HALF:
                    DDRC |= 0xF0;
                    break;
                }
                break;
            case PORT_INPUT:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRC &= 0xF0;
                    break;
                case GPIO_SECOND_HALF:
                    DDRC &= 0x0F;
                    break;
                }
                break;
            case PORT_INPUT_INTERNAL_PULLUP:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRC &= 0xF0;
                    PORTC |= 0x0F;
                    break;
                case GPIO_SECOND_HALF:
                    DDRC &= 0x0F;
                    PORTC |= 0xF0;
                    break;
                }
                break;
            }
            break;

        case PORTD_ID:
            switch (portMode){
            case PORT_OUTPUT:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRD |= 0x0F;
                    break;
                case GPIO_SECOND_HALF:
                    DDRD |= 0xF0;
                    break;
                }
                break;
            case PORT_INPUT:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRD &= 0xF0;
                    break;
                case GPIO_SECOND_HALF:
                    DDRD &= 0x0F;
                    break;
                }
                break;
            case PORT_INPUT_INTERNAL_PULLUP:
                switch (portHalf){
                case GPIO_FIRST_HALF:
                    DDRD &= 0xF0;
                    PORTD |= 0x0F;
                    break;
                case GPIO_SECOND_HALF:
                    DDRD &= 0x0F;
                    PORTD |= 0xF0;
                    break;
                }
                break;
            }
            break;
        }
    }
}

/* Write the logical value into a specific port (HALF of the port) if the port number is not correct,
 * the request is not handled
 */
void GPIO_writeHalfPort(GPIO_port_number_t portNumber, uint8 portValue, GPIO_half_port_number_t portHalf){
    if((portNumber >= PORT_NUMS) || (portHalf >= HALFS_PER_PORT)){
        /* Some sort of error handling */
        /* Do Nothing! */
    } else {
        switch (portNumber)
        {
        case PORTA_ID:
            switch (portHalf)
            {
            case GPIO_FIRST_HALF:
                PORTA = (PORTA & 0xF0) | (portValue & 0x0F);
                break;
            case GPIO_SECOND_HALF:
                PORTA = (PORTA & 0x0F) | ( (portValue & 0x0F)<<4 );
                break;
            }
            break;
        case PORTB_ID:
            switch (portHalf)
            {
            case GPIO_FIRST_HALF:
                PORTB = (PORTB & 0xF0) | (portValue & 0x0F);
                break;
            case GPIO_SECOND_HALF:
                PORTB = (PORTB & 0x0F) | ( (portValue & 0x0F)<<4 );
                break;
            }
            break;
        case PORTC_ID:
            switch (portHalf)
            {
            case GPIO_FIRST_HALF:
                PORTC = (PORTC & 0xF0) | (portValue & 0x0F);
                break;
            case GPIO_SECOND_HALF:
                PORTC = (PORTC & 0x0F) | ( (portValue & 0x0F)<<4 );
                break;
            }
            break;
        case PORTD_ID:
            switch (portHalf)
            {
            case GPIO_FIRST_HALF:
                PORTD = (PORTD & 0xF0) | (portValue & 0x0F);
                break;
            case GPIO_SECOND_HALF:
                PORTD = (PORTD & 0x0F) | ( (portValue & 0x0F)<<4 );
                break;
            }
            break;
        }
    }
}

/* Read the logical value from a specific port(HALF port)
 * if the port number is not correct, the function will return 0
 */
uint8 GPIO_readHalfPort(GPIO_port_number_t portNumber, GPIO_half_port_number_t portHalf){
    if((portNumber >= PORT_NUMS) || (portHalf >= HALFS_PER_PORT)){
        return LOW;
    } else {
        switch (portNumber)
        {
        case PORTA_ID:
            switch (portHalf)
            {
            case GPIO_FIRST_HALF:
                return (PINA & 0x0F);
                break;
            case GPIO_SECOND_HALF:
                return ((PINA & 0xF0)>>4);
                break;
            }
            break;
        case PORTB_ID:
            switch (portHalf)
            {
            case GPIO_FIRST_HALF:
                return (PINB & 0x0F);
                break;
            case GPIO_SECOND_HALF:
                return ((PINB & 0xF0)>>4);
                break;
            }
            break;
        case PORTC_ID:
            switch (portHalf)
            {
            case GPIO_FIRST_HALF:
                return (PINC & 0x0F);
                break;
            case GPIO_SECOND_HALF:
                return ((PINC & 0xF0)>>4);
                break;
            }
            break;
        case PORTD_ID:
            switch (portHalf)
            {
            case GPIO_FIRST_HALF:
                return (PIND & 0x0F);
                break;
            case GPIO_SECOND_HALF:
                return ((PIND & 0xF0)>>4);
                break;
            }
            break;
        }
    }
}
