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
* 								   Types
==============================================================================
*/

typedef enum{
	TIMER_NORMAL_MODE,
	TIMER_CTC_MODE = 2,
	TIMER_PWM_MODE,
} timer_mode_t;

typedef enum{
	OC0_DISCONNECTED,
	OC0_TOGGLE_ON_COMPARE_MATCH,
	OC0_CLEAR_ON_COMPARE_MATCH,
	OC0_SET_ON_COMPARE_MATCH,
} OC0_pin_mode_t;

/* maybe delete me */
typedef enum{
	PWM_NON_INVERTING_MODE,
	PWM_INTERTING_MODE,
} PWM_MODE_t;

typedef enum{
	NO_CLOCK,
	F_CPU_1,
	F_CPU_8,
	F_CPU_64,
	F_CPU_256,
	F_CPU_1024,
	EX_CLK_FALLING_EDGE,
	EX_CLK_RISING_EDGE,
} timer0_prescaler_t;

typedef struct{
	timer_mode_t timerMode;
	timer0_prescaler_t timer_prescaler;
	OC0_pin_mode_t OC0PinMode; /* depends on the mode */
	uint8 ticks;
} timer0_config;

/*
==============================================================================
* 							Function Prototypes
==============================================================================
*/
void TIMER0_init(const timer0_config * configPtr);
void TIMER0_setCallBack(void (*ptrToFunction)(void));
void TIMER0_stop(void);
void TIMER0_deInit(void);
void TIMER0_start(const timer0_config * configPtr);
#endif /* TIMER_H_ */
