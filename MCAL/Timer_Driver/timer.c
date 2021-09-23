/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 20/9/2021
* Program/Purpose: 
==============================================================================
*/

#include "timer.h"

/* Callback pointer that will be called when timer ticks the required number of ticks */
static void (*timer0_callBackPtr)(void) = NULL_PTR;
/* A variable that counts the number of ticks for the timer */
static uint8 numberOfTicks = 0;
/* A variable that contatins the required number of ticks passed from the user in the configuration structure */
static uint8 requiredNumOfTicks = 0;

void TIMER0_init(const timer0_config * configPtr){
    /* Set the prescaler by clearing the first 3 bits and then ORing with the timer_prescaler */
    TCCR0 = (TCCR0 & 0xF8) | (configPtr->timer_prescaler);
    /* Save the required number of ticks which will be checked in the ISR */
    requiredNumOfTicks = configPtr->tick;
    /* Configure the timer mode */
    switch (configPtr->timerMode){
    case TIMER_NORMAL_MODE:
        /* Enable force output compare */
        SET_BIT(TCCR0,FOC0);
        /* 
        Set the timer to work on normal mode(overflow) by
        1) Clearing WGM00
        2) Clearing WGM01
        */
        CLEAR_BIT(TCCR0,WGM00);
        CLEAR_BIT(TCCR0,WGM01);
        /* 
        Disconnect OC0 pin as the timer is working in overflow mode by
        1) Clearing COM00
        2) Clearing COM01
        */
        CLEAR_BIT(TCCR0,COM00);
        CLEAR_BIT(TCCR0,COM01);
        /* Disable overflow interrupt in case that ticks are zero */
        if(configPtr->ticks != 0){
            /* Enable Timer overflow interrupt */
            SET_BIT(TIMSK, TOIE0);
        } else {
            CLEAR_BIT(TIMSK, TOIE0);
        }
        /* Disable Timer output compare match match interrupt */
        CLEAR_BIT(TIMSK, OCIE0);
        break;   
    case TIMER_CTC_MODE:
        /* Enable force output compare */
        SET_BIT(TCCR0, FOC0);
        /* 
        Set the timer to work on normal mode(overflow) by
        1) Clearing WGM00
        2) Setting WGM01
        */
        CLEAR_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0,WGM01);

        /* Configure OC0 pin */
        switch (configPtr->OC0PinMode)
        {
        case OC0_DISCONNECTED:
            /* 
            Disconnect OC0 by
            1) Clearing COM00
            2) Clearing COM01
            */
            CLEAR_BIT(TCCR0, COM00);
            CLEAR_BIT(TCCR0, COM01);
            break;
        case OC0_TOGGLE_ON_COMPARE_MATCH:
            /*
            Toggle OC0 on compare match by
            1) Making OC0 (PB3) pin output
            2) Setting COM00
            3) Clearing COM01
            */
            DDRB |= (1<<PB3);
            SET_BIT(TCCR0, COM00);
            CLEAR_BIT(TCCR0, COM01);
            break;
        case OC0_CLEAR_ON_COMPARE_MATCH:
            /*
            Clear OC0 on compare match by
            1) Making OC0 (PB3) pin output
            2) Clearing COM00
            3) Setting  COM01
            */
            DDRB |= (1<<PB3);
            CLEAR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
            break;
        case OC0_SET_ON_COMPARE_MATCH:
            /*
            Set OC0 on compare match by
            1) Making OC0 (PB3) pin output
            2) Setting COM00
            3) Setting COM01
            */
            DDRB |= (1<<PB3);
            SET_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
            break;
        default:
            break;
        }
        /* Disable timer output compare match interrupt in case that ticks are zero */
        if (configPtr->ticks == 0){
            /* Disable timer output compare match interrupt */
            SET_BIT(TIMSK, OCIE0);
        } else {
            /* Enable timer output compare match interrupt */
            CLEAR_BIT(TIMSK, OCIE0);
        }
        /* Disable timer overflow interrupt  */
        CLEAR_BIT(TIMSK, TOIE0);
        break;
    case TIMER_PWM_MODE:
        /* Enable force output compare */
        SET_BIT(TCCR0,FOC0);
        /* 
        Set the timer to work on fast PWM mode by
        1) Setting WGM00
        2) Setting WGM01
        */
        SET_BIT(TCCR0,WGM00);
        SET_BIT(TCCR0,WGM01);
        /* Configure OC0 pin */
        switch (configPtr->OC0PinMode)
        {
        case OC0_DISCONNECTED:
            /* 
            Disconnect OC0 by
            1) Clearing COM00
            2) Clearing COM01
            */
            CLEAR_BIT(TCCR0, COM00);
            CLEAR_BIT(TCCR0, COM01);
            break;
        case OC0_CLEAR_ON_COMPARE_MATCH:
            /*
            Clear OC0 on compare match (Non-Inverting Mode) by
            1) Making OC0 (PB3) pin output
            2) Clearing COM00
            3) Setting  COM01
            */
            DDRB |= (1<<PB3);
            CLEAR_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
            break;
        case OC0_SET_ON_COMPARE_MATCH:
            /*
            Set OC0 on compare match (Inverting Mode) by
            1) Making OC0 (PB3) pin output
            2) Setting COM00
            3) Setting COM01
            */
            DDRB |= (1<<PB3);
            SET_BIT(TCCR0, COM00);
            SET_BIT(TCCR0, COM01);
            break;
        default:
            break;
        }
        /* Disable timer output compare match interrupt in case that ticks are zero */
        if (configPtr->ticks == 0){
            /* Disable timer output compare match interrupt */
            SET_BIT(TIMSK, OCIE0);
        } else {
            /* Enable timer output compare match interrupt */
            CLEAR_BIT(TIMSK, OCIE0);
        }
        /* Disable timer overflow interrupt  */
        CLEAR_BIT(TIMSK, TOIE0);
        break;     
    default:
        break;
    }
}


void TIMER0_setCallBack(void (*ptrToFunction)(void)){
    timer0_callBackPtr = ptrToFunction;
}


void TIMER0_deInit(void){
    TCCR0 = 0;
    CLEAR_BIT(TIMSK, TOIE0);
    CLEAR_BIT(TIMSK, OCIE0);
}

void TIMER0_start(const timer0_config * configPtr){
    TCCR0 = (TCCR0 & 0xF8) | (configPtr->timer_prescaler);
}

void TIMER0_stop(void){
    TCCR0 = (TCCR0 & 0xF8) | NO_CLOCK;
}

ISR(TIMER0_OVF_vect){
    numberOfTicks++;
    if(numberOfTicks == requiredNumOfTicks){
        numberOfTicks = 0;
        if(timer0_callBackPtr != NULL_PTR){
            (*timer0_callBackPtr)();
        }
    }
}

ISR(TIMER0_COMP_vect){
    numberOfTicks++;
    if(numberOfTicks == requiredNumOfTicks){
        numberOfTicks = 0;
        if(timer0_callBackPtr != NULL_PTR){
            (*timer0_callBackPtr)();
        }
    }
}
