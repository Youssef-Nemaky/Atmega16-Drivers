/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 20/9/2021
* Program/Purpose: 
==============================================================================
*/

#include "timer.h"

/* Callback pointer for timer0 that will be called when timer ticks reaches the required number of ticks */
static void (*timer0_callBackPtr)(void) = NULL_PTR;

/* Callback pointer for timer1 channel A that will be called when timer ticks reaches the required number of ticks */
static void (*timer1_channelA_callBackPtr)(void) = NULL_PTR;

/* Callback pointer for timer1 channel B that will be called when timer ticks reaches the required number of ticks */
static void (*timer1_channelB_callBackPtr)(void) = NULL_PTR;

/* Callback pointer for timer2 that will be called when timer ticks reaches the required number of ticks */
static void (*timer2_callBackPtr)(void) = NULL_PTR;

/* An array that contatins the number of ticks for each timer */
static volatile uint8 numberOfTicks[NUMBER_OF_CHANNELS] = {0};
/* An array that contatins the required number of ticks for each timer
 passed from the user in the configuration structure */
static volatile uint8 requiredNumOfTicks[NUMBER_OF_CHANNELS] = {0};


/*
==============================================================================
*                             TIMER 0 Functions 
==============================================================================
*/
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
        /* Disable force output compare */
        CLEAR_BIT(TCCR0,FOC0);
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
    timer0_callBackPtr = ptrToFunction;
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
    TCCR0 = (TCCR0 & 0xF8) | T0_NO_CLOCK;
}

void TIMER0_set_duty_cycle(uint8 duty){
    OCR0 = duty;
}

/*
==============================================================================
*                             TIMER 1 Functions 
==============================================================================
*/
void TIMER1_init(const timer1_config_t * configPtr){
    /* Set the prescaler by clearing the first 3 bits and then ORing with the timer_prescaler */
    TCCR1B = (TCCR1B & 0xF8) | (configPtr->timer_prescaler);
    /*EDIT THE COMMENT*/
    /* Save the required number of ticks which will be checked in the ISR */
    requiredNumOfTicks[TIMER1_CHANNEL_A_INDEX] = configPtr->channelA_ticks;
    requiredNumOfTicks[TIMER1_CHANNEL_B_INDEX] = configPtr->channelB_ticks;

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
        if(configPtr->channelA_ticks == 0){
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
            Disconnect OC1A by
            1) Clearing COM1A0
            2) Clearing COM1A1
            */
            CLEAR_BIT(TCCR1A, COM1A0);
            CLEAR_BIT(TCCR1A, COM1A1);
            break;
        case OC1_TOGGLE_ON_COMPARE_MATCH:
            /*
            Toggle OC1A on compare match by
            1) Making OC1A (PD5) pin output
            2) Setting COM1A0
            3) Clearing COM1A1
            */
            DDRD |= (1<<PD5);
            SET_BIT(TCCR1A, COM1A0);
            CLEAR_BIT(TCCR1A, COM1A1);
            break;
        case OC1_CLEAR_ON_COMPARE_MATCH:
            /*
            Clear OC1A on compare match by
            1) Making OC1A (PD5) pin output
            2) Clearing COM1A0
            3) Setting  COM1A1
            */
            DDRD |= (1<<PD5);
            CLEAR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
            break;
        case OC1_SET_ON_COMPARE_MATCH:
            /*
            Set OC1A on compare match by
            1) Making OC1A (PD5) pin output
            2) Setting COM1A0
            3) Setting COM1A1
            */
            DDRD |= (1<<PD5);
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
            break;
        default:
            break;
        }

        /* Configure OC1B pin */
        switch (configPtr->OC1BPinMode)
        {
        case OC1_DISCONNECTED:
            /* 
            Disconnect OC1B by
            1) Clearing COM1B0
            2) Clearing COM1B1
            */
            CLEAR_BIT(TCCR1A, COM1B0);
            CLEAR_BIT(TCCR1A, COM1B1);
            break;
        case OC1_TOGGLE_ON_COMPARE_MATCH:
            /*
            Toggle OC1B on compare match by
            1) Making OC1B (PD4) pin output
            2) Setting COM1B0
            3) Clearing COM1B1
            */
            DDRD |= (1<<PD4);
            SET_BIT(TCCR1A, COM1B0);
            CLEAR_BIT(TCCR1A, COM1B1);
            break;
        case OC1_CLEAR_ON_COMPARE_MATCH:
            /*
            Clear OC1B on compare match by
            1) Making OC1B (PD4) pin output
            2) Clearing COM1B0
            3) Setting  COM1B1
            */
            DDRD |= (1<<PD4);
            CLEAR_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
            break;
        case OC1_SET_ON_COMPARE_MATCH:
            /*
            Set OC1B on compare match by
            1) Making OC1A (PD4) pin output
            2) Setting COM1B0
            3) Setting COM1B1
            */
            DDRD |= (1<<PD4);
            SET_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
            break;
        default:
            break;
        }

        /* Disable timer output compare match for channel A interrupt in case that ticks are zero */
        if (configPtr->channelA_ticks == 0){
            /* Disable timer output compare match for channel A interrupt */
            CLEAR_BIT(TIMSK, OCIE1A);
        } else {
            /* Enable timer output compare match for channel A interrupt */
            SET_BIT(TIMSK, OCIE1A);
        }

        /* Disable timer output compare match for channel B interrupt in case that ticks are zero */
        if (configPtr->channelB_ticks == 0){
            /* Disable timer output compare match for channel B interrupt */
            CLEAR_BIT(TIMSK, OCIE1B);
        } else {
            /* Enable timer output compare match for channel B interrupt */
            SET_BIT(TIMSK, OCIE1B);
        }

        /* Disable timer overflow interrupt  */
        CLEAR_BIT(TIMSK, TOIE1);

        /* Disable input capture unit interrupt */
        CLEAR_BIT(TIMSK, TICIE1);

        break;
    case TIMER_PWM_MODE:
        /* Disable force output compare for channel A */
        CLEAR_BIT(TCCR1A, FOC1A);
        /* Disable force output compare for channel B */
        CLEAR_BIT(TCCR1A, FOC1B);
        
        /* Set the timer compare value for channel A */
        OCR1A = configPtr->timer_compareValueA;
        /* Set the timer compare value for channel B */
        OCR1B = configPtr->timer_compareValueB;
        /* 
        Set the timer to work on fast PWM mode by
        1) Setting WGM10
        2) Setting WGM11
        3) Setting WGM12
        4) Setting WGM13
        */
        SET_BIT(TCCR1A,WGM10);
        SET_BIT(TCCR1A,WGM11);
        SET_BIT(TCCR1B,WGM12);
        SET_BIT(TCCR1B,WGM13);

        /* Configure OC1A pin */
        switch (configPtr->OC1APinMode)
        {
        case OC1_DISCONNECTED:
            /* 
            Disconnect OC1A by
            1) Clearing COM1A0
            2) Clearing COM1A1
            */
            CLEAR_BIT(TCCR1A, COM1A0);
            CLEAR_BIT(TCCR1A, COM1A1);
            break;
        case OC1_TOGGLE_ON_COMPARE_MATCH:
            /* 
            Toggle OC1A on compare match  by
            1) Setting COM1A0
            2) Clearing COM1A1
            */
            SET_BIT(TCCR1A, COM1A0);
            CLEAR_BIT(TCCR1A, COM1A1);
            break;
        case OC1_CLEAR_ON_COMPARE_MATCH:
            /*
            Clear OC1A on compare match (Non-Inverting Mode) by
            1) Making OC1A (PD5) pin output
            2) Clearing COM1A0
            3) Setting  COM1A1
            */
            DDRD |= (1<<PD5);
            CLEAR_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
            break;
        case OC1_SET_ON_COMPARE_MATCH:
            /*
            Set OC1A on compare match (Inverting Mode) by
            1) Making OC1A (PD5) pin output
            2) Setting COM1A0
            3) Setting COM1A1
            */
            DDRD |= (1<<PD5);
            SET_BIT(TCCR1A, COM1A0);
            SET_BIT(TCCR1A, COM1A1);
            break;
        default:
            break;
        }

        /* Configure OC1B pin */
        switch (configPtr->OC1BPinMode)
        {
        case OC1_DISCONNECTED:
            /* 
            Disconnect OC1B by
            1) Clearing COM1B0
            2) Clearing COM1B1
            */
            CLEAR_BIT(TCCR1A, COM1B0);
            CLEAR_BIT(TCCR1A, COM1B1);
            break;
        case OC1_CLEAR_ON_COMPARE_MATCH:
            /*
            Clear OC1B on compare match (Non-Inverting Mode) by
            1) Making OC1B (PD4) pin output
            2) Clearing COM1B0
            3) Setting  COM1B1
            */
            DDRD |= (1<<PD4);
            CLEAR_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
            break;
        case OC1_SET_ON_COMPARE_MATCH:
            /*
            Set OC1B on compare match (Inverting Mode) by
            1) Making OC1B (PD4) pin output
            2) Setting COM1B0
            3) Setting COM1B1
            */
            DDRD |= (1<<PD4);
            SET_BIT(TCCR1A, COM1B0);
            SET_BIT(TCCR1A, COM1B1);
            break;
        default:
            break;
        }

        /* Disable timer output compare match for channel A interrupt in case that ticks are zero */
        if (configPtr->channelA_ticks == 0){
            /* Disable timer output compare match for channel A interrupt */
            CLEAR_BIT(TIMSK, OCIE1A);
        } else {
            /* Enable timer output compare match for channel A interrupt */
            SET_BIT(TIMSK, OCIE1A);
        }

        /* Disable timer output compare match for channel B interrupt in case that ticks are zero */
        if (configPtr->channelB_ticks == 0){
            /* Disable timer output compare match for channel B interrupt */
            CLEAR_BIT(TIMSK, OCIE1B);
        } else {
            /* Enable timer output compare match for channel B interrupt */
            SET_BIT(TIMSK, OCIE1B);
        }

        /* Disable timer overflow interrupt  */
        CLEAR_BIT(TIMSK, TOIE1);

        /* Disable input capture unit interrupt */
        CLEAR_BIT(TIMSK, TICIE1);

        break;     
    default:
        break;
    }
}

void TIMER1_setCallBack(void (*ptrToFunction)(void)){
    timer1_channelA_callBackPtr = ptrToFunction;
}

void TIMER1_channelA_setCallBack(void (*ptrToFunction)(void)){
    timer1_channelA_callBackPtr = ptrToFunction;
}

void TIMER1_channelB_setCallBack(void (*ptrToFunction)(void)){
    timer1_channelB_callBackPtr = ptrToFunction;
}

void TIMER1_deInit(void){
    /* Reset Counter Register */
    TCNT1 = 0;
    /* Reset Output Compare Registers */
    OCR1A = 0;
    OCR1B = 0;
    /* Reset Timer Control Registers */
    TCCR1A = 0;
    TCCR1B = 0;
    /* Disable Timer Interrupts */
    CLEAR_BIT(TIMSK, TOIE1); /* Overflow Interrupt */
    CLEAR_BIT(TIMSK, OCIE1A); /* Output Compare Interrupt for Channel A */
    CLEAR_BIT(TIMSK, OCIE1B); /* Output Compare Interrupt  for Channel B */
    CLEAR_BIT(TIMSK, TICIE1); /* Input Capture Interrupt */
}

void TIMER1_start(const timer1_config_t * configPtr){
    TCCR1B = (TCCR1B & 0xF8) | (configPtr->timer_prescaler);
}

void TIMER1_stop(void){
    TCCR1B = (TCCR1B & 0xF8) | T1_NO_CLOCK;
}

void TIMER1_set_duty(uint16 duty, timer1_channel_number_t channelNumber){
    switch (channelNumber)
    {
    case CHANNEL_A:
        OCR1A = duty;
        break;
    case CHANNEL_B:
        OCR1B = duty;
    default:
        break;
    }
}

/*
==============================================================================
*                             TIMER 2 Functions 
==============================================================================
*/
void TIMER2_init(const timer2_config_t * configPtr){
    /* According to the datasheet */
    /* Warning: When switching between asynchronous and synchronous clocking of
    Timer/Counter2, the Timer Registers TCNT2, OCR2, and TCCR2 might be corrupted. A
    safe procedure for switching clock source is:
    1. Disable the Timer/Counter2 interrupts by clearing OCIE2 and TOIE2.
    2. Select clock source by setting AS2 as appropriate.
    3. Write new values to TCNT2, OCR2, and TCCR2.
    4. To switch to asynchronous operation: Wait for TCN2UB, OCR2UB, and TCR2UB.
    5. Clear the Timer/Counter2 Interrupt Flags.
    6. Enable interrupts, if needed. */

    /* Disable Timer/Counter2 interrupts */
    CLEAR_BIT(TIMSK, TOIE2); /* Disable Timer2 overflow interrupt */
    CLEAR_BIT(TIMSK, OCIE2); /* Disable Timer2 output compare match interrupt */
    
    /* Select Clock Source */
    ASSR = (ASSR & 0xF7) | ((configPtr->clockMode)<<AS2);

    /* Write new values to TCNT2, OCR2 and TCCR2 */
    
    /* Set the prescaler by clearing the first 3 bits and then ORing with the timer_prescaler */
    TCCR2 = (TCCR2 & 0xF8) | (configPtr->timer_prescaler);

    /* Save the required number of ticks which will be checked in the ISR */
    requiredNumOfTicks[TIMER2_INDEX] = configPtr->ticks;

    /* Set the initial value for the timer */
    TCNT2 = configPtr->timer_initialValue;

    /* Configure the timer mode */
    switch (configPtr->timerMode)
    {
    case TIMER_NORMAL_MODE:
        /* Enable force output compare */
        SET_BIT(TCCR2, FOC2);
        /* 
            Set the timer to work on normal mode(overflow) by
            1) Clearing WGM20
            2) Clearing WGM21
            */
        CLEAR_BIT(TCCR2, WGM20);
        CLEAR_BIT(TCCR2, WGM21);
        /* 
            Disconnect OC2 pin as the timer is working in overflow mode by
            1) Clearing COM20
            2) Clearing COM21
            */
        CLEAR_BIT(TCCR2, COM20);
        CLEAR_BIT(TCCR2, COM21);

        break;
    case TIMER_CTC_MODE:
        /* Enable force output compare */
        SET_BIT(TCCR2, FOC2);
        /* Set the timer compare value */
        OCR2 = configPtr->timer_compareValue;
        /* 
            Set the timer to work on CTC mode by
            1) Clearing WGM20
            2) Setting WGM21
            */
        CLEAR_BIT(TCCR2, WGM20);
        SET_BIT(TCCR2, WGM21);

        /* Configure OC2 pin */
        switch (configPtr->OC2PinMode)
        {
        case OC2_DISCONNECTED:
            /* 
                Disconnect OC2 by
                1) Clearing COM20
                2) Clearing COM21
                */
            CLEAR_BIT(TCCR2, COM20);
            CLEAR_BIT(TCCR2, COM21);
            break;
        case OC2_TOGGLE_ON_COMPARE_MATCH:
            /*
                Toggle OC2 on compare match by
                1) Making OC2 (PD7) pin output
                2) Setting COM20
                3) Clearing COM21
                */
            DDRD |= (1 << PD7);
            SET_BIT(TCCR2, COM20);
            CLEAR_BIT(TCCR2, COM21);
            break;
        case OC2_CLEAR_ON_COMPARE_MATCH:
            /*
                Clear OC2 on compare match by
                1) Making OC2 (PD7) pin output
                2) Clearing COM20
                3) Setting  COM21
                */
            DDRD |= (1 << PD7);
            CLEAR_BIT(TCCR2, COM20);
            SET_BIT(TCCR2, COM21);
            break;
        case OC2_SET_ON_COMPARE_MATCH:
            /*
                Set OC2 on compare match by
                1) Making OC2 (PD7) pin output
                2) Setting COM20
                3) Setting COM21
                */
            DDRD |= (1 << PD7);
            SET_BIT(TCCR2, COM20);
            SET_BIT(TCCR2, COM21);
            break;
        default:
            break;
        }
        break;
    case TIMER_PWM_MODE:
        /* Disable force output compare */
        CLEAR_BIT(TCCR2, FOC2);
        /* 
            Set the timer to work on fast PWM mode by
            1) Setting WGM20
            2) Setting WGM21
            */
        SET_BIT(TCCR2, WGM20);
        SET_BIT(TCCR2, WGM21);
        /* Configure OC2 pin */
        switch (configPtr->OC2PinMode)
        {
        case OC2_DISCONNECTED:
            /* 
            Disconnect OC2 by
            1) Clearing COM20
            2) Clearing COM21
            */
            CLEAR_BIT(TCCR2, COM20);
            CLEAR_BIT(TCCR2, COM21);
            break;
        case OC2_CLEAR_ON_COMPARE_MATCH:
            /*
            Clear OC2 on compare match (Non-Inverting Mode) by
            1) Making OC2 (PD7) pin output
            2) Clearing COM20
            3) Setting  COM21
            */
            DDRD |= (1 << PD7);
            CLEAR_BIT(TCCR2, COM20);
            SET_BIT(TCCR2, COM21);
            break;
        case OC2_SET_ON_COMPARE_MATCH:
            /*
            Set OC2 on compare match (Inverting Mode) by
            1) Making OC2 (PD7) pin output
            2) Setting COM20
            3) Setting COM21
            */
            DDRD |= (1 << PD7);
            SET_BIT(TCCR2, COM20);
            SET_BIT(TCCR2, COM21);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    /* Wait for TCN2UB, OCR2UB, and TCR2UB */
    while(ASSR & ( (1<<TCN2UB) | (1<<OCR2UB) | (1<<TCR2UB) ) );

    /* Clear the Timer/Counter2 Interrupt Flags */
    /* Clear output compare flag by setting OCF2 */
    SET_BIT(TIFR, OCF2);
    /* Clear timer/counter2 overflow flag */
    SET_BIT(TIFR, TOV2);

    /* Enable interrupts */
    switch (configPtr->timerMode)
    {
    case TIMER_NORMAL_MODE:
        /* Disable overflow interrupt in case that ticks are zero */
        if(configPtr->ticks == 0){
            CLEAR_BIT(TIMSK, TOIE2);
        } else {
            SET_BIT(TIMSK, TOIE2);
        }

        /* Disable timer output compare match interrupt */
        CLEAR_BIT(TIMSK, OCIE2);
        break;
    case TIMER_CTC_MODE:
        /* Disable timer output compare match interrupt in case ticks are zero */
        if(configPtr->ticks == 0 ){
            CLEAR_BIT(TIMSK, OCIE2);
        } else {
            SET_BIT(TIMSK, OCIE2);
        }

        /* Disable overflow interrupt */
        CLEAR_BIT(TIMSK, TOV2);
        break;
    case TIMER_PWM_MODE:
        /* Disable timer output compare match interrupt in case that ticks are zero */
        if(configPtr->ticks == 0){
            CLEAR_BIT(TIMSK, OCIE2);
        } else {
            CLEAR_BIT(TIMSK, OCIE2);
        }

        /* Disable timer overflow interrupt */
        CLEAR_BIT(TIMSK, TOIE2);
        break;
    default:
        break;
    }
}

void TIMER2_setCallBack(void (*ptrToFunction)(void)){
    timer2_callBackPtr = ptrToFunction;
}

void TIMER2_deInit(void){
    TCCR2 = 0;
    CLEAR_BIT(TIMSK, TOIE2);
    CLEAR_BIT(TIMSK, OCIE2);
}

void TIMER2_start(const timer2_config_t * configPtr){
    TCCR2 = (TCCR2 & 0xF8) | (configPtr->timer_prescaler);
}

void TIMER2_stop(void){
    TCCR2 = (TCCR2 & 0xF8) | T2_NO_CLOCK;
}

void TIMER2_set_duty_cycle(uint8 duty){
    OCR2 = duty;
}

/*
==============================================================================
*                             ISR Functions 
==============================================================================
*/

/*
==============================================================================
*                             TIMER 0 ISRs 
==============================================================================
*/
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

/*
==============================================================================
*                             TIMER 1 ISRs 
==============================================================================
*/
ISR(TIMER1_OVF_vect){
    numberOfTicks[TIMER1_CHANNEL_A_INDEX]++;
    if(numberOfTicks[TIMER1_CHANNEL_A_INDEX] == requiredNumOfTicks[TIMER1_CHANNEL_A_INDEX]){
        numberOfTicks[TIMER1_CHANNEL_A_INDEX] = 0;
        if(timer1_channelA_callBackPtr != NULL_PTR){
            (*timer1_channelA_callBackPtr)();
        }
    }
}

ISR(TIMER1_COMPA_vect){
    numberOfTicks[TIMER1_CHANNEL_A_INDEX]++;
    if(numberOfTicks[TIMER1_CHANNEL_A_INDEX] == requiredNumOfTicks[TIMER1_CHANNEL_A_INDEX]){
        numberOfTicks[TIMER1_CHANNEL_A_INDEX] = 0;
        if(timer1_channelA_callBackPtr != NULL_PTR){
            (*timer1_channelA_callBackPtr)();
        }
    }
}

ISR(TIMER1_COMPB_vect){
    numberOfTicks[TIMER1_CHANNEL_B_INDEX]++;
    if(numberOfTicks[TIMER1_CHANNEL_B_INDEX] == requiredNumOfTicks[TIMER1_CHANNEL_B_INDEX]){
        numberOfTicks[TIMER1_CHANNEL_B_INDEX] = 0;
        if(timer1_channelB_callBackPtr != NULL_PTR){
            (*timer1_channelB_callBackPtr)();
        }
    }
}

/*
==============================================================================
*                             TIMER 2 ISRs 
==============================================================================
*/
ISR(TIMER2_OVF_vect){
    numberOfTicks[TIMER2_INDEX]++;
    if(numberOfTicks[TIMER2_INDEX] == requiredNumOfTicks[TIMER2_INDEX]){
        numberOfTicks[TIMER2_INDEX] = 0;
        if(timer2_callBackPtr != NULL_PTR){
            (*timer2_callBackPtr)();
        }
    }
}

ISR(TIMER2_COMP_vect){
    numberOfTicks[TIMER2_INDEX]++;
    if(numberOfTicks[TIMER2_INDEX] == requiredNumOfTicks[TIMER2_INDEX]){
        numberOfTicks[TIMER2_INDEX] = 0;
        if(timer2_callBackPtr != NULL_PTR){
            (*timer2_callBackPtr)();
        }
    }
}

