/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 15/10/2021
* Name: external_interrupt.c 
==============================================================================
*/

#include "external_interrupt.h"
#include "../Gpio_Driver/gpio.h"

/*
==============================================================================
*                                  Callback Pointers
==============================================================================
*/
/* External Interrupt 0 callback pointer */
static void (*g_ext_int_0_callBackPtr)(void) = NULL_PTR;

/* External Interrupt 1 callback pointer */
static void (*g_ext_int_1_callBackPtr)(void) = NULL_PTR;

/* External Interrupt 2 callback pointer */
static void (*g_ext_int_2_callBackPtr)(void) = NULL_PTR;


/* Set up the required external interrupt mode and enable it
 * Note: only rising and falling edge modes are avaliable for external interrupt 2
 */
void EX_INT_enable(external_interrupt_number_t externalInterruptNumber, external_interrupt_mode_t externalInterruptMode){
    switch (externalInterruptNumber)
    {
    case EXTERNAL_INTERRUPT_0_ID:
        /* Check if internal pull up is enabled or not */
        if(externalInterruptMode == EXT_INT_FALLING_EDGE_TRIGGER_INTERNAL_PULL_UP){
            /* Make interrupt pin input with internal pull up resistor enabled */
            GPIO_setPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT_INTERNAL_PULLUP);
            /* reset it to normal falling mode after setting the pin direction */
            externalInterruptMode = EXT_INT_FALLING_EDGE_TRIGGER;
        } else {
            /* Make interrupt pin input */
            GPIO_setPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT);
        }
        
        /* Set the working mode for the external interrupt 0 by setting the right interrupt sense control bits */
        MCUCR = (MCUCR & 0xFC) | externalInterruptMode;
        /* Enable external interrupt 0 request */
        SET_BIT(GICR, INT0);
        break;
    case EXTERNAL_INTERRUPT_1_ID:
        /* Check if internal pull up is enabled or not */
        if(externalInterruptMode == EXT_INT_FALLING_EDGE_TRIGGER_INTERNAL_PULL_UP){
            /* Make interrupt pin input with internal pull up resistor enabled */
            GPIO_setPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT_INTERNAL_PULLUP);
            /* reset it to normal falling mode after setting the pin direction */
            externalInterruptMode = EXT_INT_FALLING_EDGE_TRIGGER;
        } else {
            /* Make interrupt pin input */
            GPIO_setPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT);
        }

        /* Set the working mode for the external interrupt 1 */
        MCUCR = (MCUCR & 0xF3) | (externalInterruptMode << 2);
        /* Enable external interrupt 1 request */
        SET_BIT(GICR, INT1);
        break;
    case EXTERNAL_INTERRUPT_2_ID:
        /* Error Checking */
        /* Only valid options for external interrupt 2 are: rising and falling edge level triggers */
        if ((externalInterruptMode == EXT_INT_LVL_CHANGE_TRIGGER) || (externalInterruptMode == EXT_INT_LOW_LVL_TRIGGER)){
            /* Some sort of error handling */
            /* Do Nothing! */
        }
        else {
            /* Check if internal pull up is enabled or not */
            if (externalInterruptMode == EXT_INT_FALLING_EDGE_TRIGGER_INTERNAL_PULL_UP){
                /* Make interrupt pin input with internal pull up resistor enabled */
                GPIO_setPinDirection(PORTB_ID, PIN2_ID, PIN_INPUT_INTERNAL_PULLUP);
                /* reset it to normal falling mode after setting the pin direction */
                externalInterruptMode = EXT_INT_FALLING_EDGE_TRIGGER;
            }
            else{
                /* Make interrupt pin input */
                GPIO_setPinDirection(PORTB_ID, PIN2_ID, PIN_INPUT);
            }

            /* Set the working mode for the external interrupt 2 */
            if (externalInterruptMode == EXT_INT_FALLING_EDGE_TRIGGER){
                CLEAR_BIT(MCUCSR, ISC2);
            }
            else{
                SET_BIT(MCUCSR, ISC2);
            }
            /* Enable external interrupt 2 request */
            SET_BIT(GICR, INT2);
        }
        break;
    }
}

/* Disable the required external interrupt by de-initing its registers */
void EX_INT_disable(external_interrupt_number_t externalInterruptNumber){
    switch (externalInterruptNumber)
    {
    case EXTERNAL_INTERRUPT_0_ID:
        /* reset interrupt sense control bits for external interrupt 0 */
        MCUCR &= 0xFC;
        /* Clear external interrupt request enable bit */
        CLEAR_BIT(GICR, INT0);
        break;

    case EXTERNAL_INTERRUPT_1_ID:
        /* reset interrupt sense control bits for external interrupt 1 */
        MCUCR &= 0xF3;
        /* Clear external interrupt request enable bit */
        CLEAR_BIT(GICR, INT1);
        break;
    
    case EXTERNAL_INTERRUPT_2_ID:
        /* reset interrupt sense control bit for external interrupt 2 */
        CLEAR_BIT(MCUCSR, ISC2);        
        /* Clear external interrupt request enable bit */
        CLEAR_BIT(GICR, INT2);
        break;
    }
}

void EX_INT_setCallBack(void (*callBackPtr)(void), external_interrupt_number_t ex_interrupt_num){
    if(ex_interrupt_num >= EXTERNAL_INTERRUPTS_NUMS){
        /* Some sort of error handling */
        /* Do Nothing! */
    } else {
        switch (ex_interrupt_num)
        {
        case EXTERNAL_INTERRUPT_0_ID:
            g_ext_int_0_callBackPtr = callBackPtr;
            break;
        case EXTERNAL_INTERRUPT_1_ID:
            g_ext_int_1_callBackPtr = callBackPtr;
            break;
        case EXTERNAL_INTERRUPT_2_ID:
            g_ext_int_2_callBackPtr = callBackPtr;
            break;
        }
    }
}

/*
==============================================================================
*                             External Interrupts ISRs
==============================================================================
*/

/* External Interrupt 0 ISR */
ISR(INT0_vect){
    if(g_ext_int_0_callBackPtr != NULL_PTR){
        (*g_ext_int_0_callBackPtr)();
    }
}

/* External Interrupt 1 ISR */
ISR(INT1_vect){
    if(g_ext_int_1_callBackPtr != NULL_PTR){
        (*g_ext_int_1_callBackPtr)();
    }
}

/* External Interrupt 2 ISR */
ISR(INT2_vect){
    if(g_ext_int_2_callBackPtr != NULL_PTR){
        (*g_ext_int_2_callBackPtr)();
    }
}