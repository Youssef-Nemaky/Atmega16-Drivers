/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 20/9/2021
* Program/Purpose: Timer.h which includes all typedef/enums/structures and function
  prototypes used in Timer.c
==============================================================================
*/
#ifndef TIMER_H_
#define TIMER_H_


#define NUMBER_OF_TIMERS 3
#define NUMBER_OF_TIMERS_WITH_TWO_CHANNELS 1


#define NUMBER_OF_CHANNELS ((NUMBER_OF_TIMERS - NUMBER_OF_TIMERS_WITH_TWO_CHANNELS) + (NUMBER_OF_TIMERS_WITH_TWO_CHANNELS * 2))

#define TIMER0_INDEX 0
#define TIMER1_CHANNEL_A_INDEX 1
#define TIMER1_CHANNEL_B_INDEX 2
#define TIMER2_INDEX 3

/*
==============================================================================
* import micro_config.h, common_macros.h and std_types.h files
==============================================================================
*/
#include "../Important_Header_Files/micro_config.h"
#include "../Important_Header_Files/common_macros.h"
#include "../Important_Header_Files/std_types.h"

/*
==============================================================================
*                                   TYPES
==============================================================================
*/

/*
==============================================================================
*                             General Types 
==============================================================================
*/
typedef enum{
	TIMER_NORMAL_MODE,
	TIMER_CTC_MODE = 2,
	TIMER_PWM_MODE,
} timer_mode_t;


/*
==============================================================================
*                                TIMER 0  
==============================================================================
*/
typedef enum{
	OC0_DISCONNECTED,
	OC0_TOGGLE_ON_COMPARE_MATCH,
	OC0_CLEAR_ON_COMPARE_MATCH,
	OC0_SET_ON_COMPARE_MATCH,
} OC0_pin_mode_t;

typedef enum{
	T0_NO_CLOCK,
	T0_F_CPU_1,
	T0_F_CPU_8,
	T0_F_CPU_64,
	T0_F_CPU_256,
	T0_F_CPU_1024,
	T0_EX_CLK_FALLING_EDGE,
	T0_EX_CLK_RISING_EDGE,
} timer0_prescaler_t;

typedef struct{
	timer_mode_t timerMode;
	timer0_prescaler_t timer_prescaler;
	uint8 timer_initialValue;
	uint8 timer_compareValue; /* OCR0 */
	OC0_pin_mode_t OC0PinMode; /* depends on the mode */
	uint8 ticks;
} timer0_config_t;

/*
==============================================================================
*                                TIMER 1 
==============================================================================
*/
typedef enum{
	T1_NO_CLOCK,
	T1_F_CPU_1,
	T1_F_CPU_8,
	T1_F_CPU_64,
	T1_F_CPU_256,
	T1_F_CPU_1024,
	T1_EX_CLK_FALLING_EDGE,
	T1_EX_CLK_RISING_EDGE,
} timer1_prescaler_t;

typedef enum{
	OC1_DISCONNECTED,
	OC1_TOGGLE_ON_COMPARE_MATCH,
	OC1_CLEAR_ON_COMPARE_MATCH,
	OC1_SET_ON_COMPARE_MATCH,
} OC1_pin_mode_t;

typedef enum{
	CHANNEL_A,
	CHANNEL_B,
} timer1_channel_number_t;


typedef struct{
	timer_mode_t timerMode;
	timer1_prescaler_t timer_prescaler;
	uint16 timer_initialValue;
	uint16 timer_compareValueA;
	uint16 timer_compareValueB;
	OC1_pin_mode_t OC1APinMode;
	OC1_pin_mode_t OC1BPinMode;
	uint8 channelA_ticks;
	uint8 channelB_ticks;
} timer1_config_t;

/*
==============================================================================
*                                TIMER 2 
==============================================================================
*/
typedef enum{
	T2_NO_CLOCK,
	T2_F_CPU_1,
	T2_F_CPU_8,
	T2_F_CPU_32,
	T2_F_CPU_64,
	T2_F_CPU_128,
	T2_F_CPU_256,
	T2_F_CPU_1024,
} timer2_prescaler_t;

typedef enum{
	OC2_DISCONNECTED,
	OC2_TOGGLE_ON_COMPARE_MATCH,
	OC2_CLEAR_ON_COMPARE_MATCH,
	OC2_SET_ON_COMPARE_MATCH,
} OC2_pin_mode_t;

typedef enum{
	INTERNAL_CLOCK, /* AS2 = 0 */
	EXTERNAL_CLOCK, /* AS2 = 1 */
} timer2_clockMode_t;

typedef struct{
	timer_mode_t timerMode;
	timer2_prescaler_t timer_prescaler;
	timer2_clockMode_t clockMode;
	uint8 timer_initialValue;
	uint8 timer_compareValue;
	OC2_pin_mode_t OC2PinMode;
	uint8 ticks;
} timer2_config_t;



/*
==============================================================================
*                                Function Prototypes  
==============================================================================
*/

/*
==============================================================================
*                                TIMER 0  
==============================================================================
*/
void TIMER0_init(const timer0_config_t * configPtr);
void TIMER0_setCallBack(void (*ptrToFunction)(void));
void TIMER0_stop(void);
void TIMER0_deInit(void);
void TIMER0_start(const timer0_config_t * configPtr);
void TIMER0_set_duty(uint8 duty);

/*
==============================================================================
*                                TIMER 1  
==============================================================================
*/
void TIMER1_init(const timer1_config_t * configPtr);
void TIMER1_setCallBack(void (*ptrToFunction)(void));
void TIMER1_channelA_setCallBack(void (*ptrToFunction)(void));
void TIMER1_channelB_setCallBack(void (*ptrToFunction)(void));
void TIMER1_stop(void);
void TIMER1_deInit(void);
void TIMER1_start(const timer1_config_t * configPtr);
void TIMER1_set_duty(uint16 duty, timer1_channel_number_t channelNumber);

/*
==============================================================================
*                                TIMER 2 
==============================================================================
*/
void TIMER2_init(const timer2_config_t * configPtr);
void TIMER2_setCallBack(void (*ptrToFunction)(void));
void TIMER2_stop(void);
void TIMER2_deInit(void);
void TIMER2_start(const timer2_config_t * configPtr);
void TIMER2_set_duty(uint8 duty);
#endif /* TIMER_H_ */
