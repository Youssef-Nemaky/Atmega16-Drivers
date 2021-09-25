/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 20/9/2021
* Program/Purpose: 
==============================================================================
*/

#include "timer.h"

/* An array that contatins callback pointers that will be called when timer ticks the required number of ticks */
static void (*timer0_callBackPtr[NUMBER_OF_TIMERS])(void) = NULL_PTR;
/* An array that contatins the number of ticks for each timer */
static uint8 numberOfTicks[NUMBER_OF_TIMERS] = 0;
/* An array that contatins the required number of ticks for each timer
 passed from the user in the configuration structure */
static uint8 requiredNumOfTicks[NUMBER_OF_TIMERS] = 0;

void TIMER0_init(const timer0_config_t * configPtr){
    /* Set the prescaler by clearing the first 3 bits and then ORing with the timer_prescaler */
    TCCR0 = (TCCR0 & 0xF8) | (configPtr->timer_prescaler);
    /* Save the required number of ticks which will be checked in the ISR */
    requiredNumOfTicks[TIMER0_INDEX] = configPtr->ticks;
    /* Set the initial value for the timer */
    TCNT0 = configPtr->timer_initialValue;
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
        if(configPtr->ticks == 0){
            /* Disable timer overflow interrupt */
            CLEAR_BIT(TIMSK, TOIE0);
        } else {
            /* Enable timer overflow interrupt */
            SET_BIT(TIMSK, TOIE0);
        }
        /* Disable timer output compare match interrupt */
        CLEAR_BIT(TIMSK, OCIE0);
        break;   
    case TIMER_CTC_MODE:
        /* Enable force output compare */
        SET_BIT(TCCR0, FOC0);
        /* Set the timer compare value */
        OCR0 = configPtr->timer_compareValue;
        /* 
        Set the timer to work on CTC mode by
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
            CLEAR_BIT(TIMSK, OCIE0);
        } else {
            /* Enable timer output compare match interrupt */
            SET_BIT(TIMSK, OCIE0);
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
            CLEAR_BIT(TIMSK, OCIE0);
        } else {
            /* Enable timer output compare match interrupt */
            SET_BIT(TIMSK, OCIE0);
        }
        /* Disable timer overflow interrupt  */
        CLEAR_BIT(TIMSK, TOIE0);
        break;     
    default:
        break;
    }
}

void TIMER1_init(const timer1_config_t * configPtr){
    /* Set the prescaler by clearing the first 3 bits and then ORing with the timer_prescaler */
    TCCR1B = (TCCR1B & 0xF8) | (configPtr->timer_prescaler);
    /* Save the required number of ticks which will be checked in the ISR */
    requiredNumOfTicks[TIMER1_INDEX] = configPtr->ticks;
    /* Set the initial value for the timer */
    TCNT1 = configPtr->timer_initialValue;
    /* Configure the timer mode */
    switch (configPtr->timerMode){
    case TIMER_NORMAL_MODE:
        /* Enable force output compare for channel A */
        SET_BIT(TCCR1A, FOC1A);
        /* Enable force output compare for channel B */
        SET_BIT(TCCR1A, FOC1B);
        /* 
        Set the timer to work on normal mode(overflow) by
        1) Clearing WGM10
        2) Clearing WGM11
        3) Clearing WGM12
        4) Clearing WGM13
        */
        CLEAR_BIT(TCCR1A,WGM10);
        CLEAR_BIT(TCCR1A,WGM11);
        CLEAR_BIT(TCCR1B,WGM12);
        CLEAR_BIT(TCCR1B,WGM13);
        /* 
        Disconnect OC1A pin as the timer is working in overflow mode by
        1) Clearing COM1A0
        2) Clearing COM1A1
        */
        CLEAR_BIT(TCCR1A,COM1A0);
        CLEAR_BIT(TCCR1A,COM1A1);
        
        /* 
        Disconnect OC1B pin as the timer is working in overflow mode by
        1) Clearing COM1B0
        2) Clearing COM1B1
        */
        CLEAR_BIT(TCCR1A,COM1B0);
        CLEAR_BIT(TCCR1A,COM1B1);

        /* Disable overflow interrupt in case that ticks are zero */
        if(configPtr->ticks == 0){
            /* Disable timer overflow interrupt */
            CLEAR_BIT(TIMSK, TOIE1);
        } else {
            /* Enable timer overflow interrupt */
            SET_BIT(TIMSK, TOIE1);
        }
        /* Disable timer output compare match interrupt for channel A */
        CLEAR_BIT(TIMSK, OCIE1A);

        /* Disable timer output compare match interrupt for channel B */
        CLEAR_BIT(TIMSK, OCIE1B);

        /* Disable input capture unit interrupt */
        CLEAR_BIT(TIMSK, TICIE1);
        break;   
    case TIMER_CTC_MODE:
        /* Enable force output compare for channel A */
        SET_BIT(TCCR1A, FOC1A);
        /* Enable force output compare for channel B */
        SET_BIT(TCCR1A, FOC1B);

        /* Set the timer compare value for channel A */
        OCR1A = configPtr->timer_compareValueA;
        /* Set the timer compare value for channel B */
        OCR1B = configPtr->timer_compareValueB;
        /* 
        Set the timer to work on CTC mode by
        1) Clearing WGM10
        2) Clearing WGM11
        3) Setting  WGM12
        4) Clearing WGM13
        */
        CLEAR_BIT(TCCR1A, WGM10);
        CLEAR_BIT(TCCR1A, WGM11);
        SET_BIT(TCCR1B,WGM12);
        CLEAR_BIT(TCCR1B, WGM13);

        /* Configure OC1A pin */
        switch (configPtr->OC1APinMode)
        {
        case OC1_DISCONNECTED:
            /* 
            Disconnect OC1 by
            1) Clearing COM1A0
            2) Clearing COM1A1
            */
            CLEAR_BIT(TCCR1A, COM1A0);
            CLEAR_BIT(TCCR1A, COM1A1);
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
            CLEAR_BIT(TIMSK, OCIE0);
        } else {
            /* Enable timer output compare match interrupt */
            SET_BIT(TIMSK, OCIE0);
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
            CLEAR_BIT(TIMSK, OCIE0);
        } else {
            /* Enable timer output compare match interrupt */
            SET_BIT(TIMSK, OCIE0);
        }
        /* Disable timer overflow interrupt  */
        CLEAR_BIT(TIMSK, TOIE0);
        break;     
    default:
        break;
    }
}

void TIMER0_setCallBack(void (*ptrToFunction)(void)){
    timer0_callBackPtr[TIMER0_INDEX] = ptrToFunction;
}


void TIMER0_deInit(void){
    TCCR0 = 0;
    CLEAR_BIT(TIMSK, TOIE0);
    CLEAR_BIT(TIMSK, OCIE0);
}

void TIMER0_start(const timer0_config_t * configPtr){
    TCCR0 = (TCCR0 & 0xF8) | (configPtr->timer_prescaler);
}

void TIMER0_stop(void){
    TCCR0 = (TCCR0 & 0xF8) | NO_CLOCK;
}

ISR(TIMER0_OVF_vect){
    numberOfTicks[TIMER0_INDEX]++;
    if(numberOfTicks[TIMER0_INDEX] == requiredNumOfTicks[TIMER0_INDEX]){
        numberOfTicks[TIMER0_INDEX] = 0;
        if(timer0_callBackPtr != NULL_PTR){
            (*timer0_callBackPtr)();
        }
    }
}

ISR(TIMER0_COMP_vect){
    numberOfTicks[TIMER0_INDEX]++;
    if(numberOfTicks[TIMER0_INDEX] == requiredNumOfTicks[TIMER0_INDEX]){
        numberOfTicks[TIMER0_INDEX] = 0;
        if(timer0_callBackPtr != NULL_PTR){
            (*timer0_callBackPtr)();
        }
    }
}
