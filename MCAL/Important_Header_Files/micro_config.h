/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 21/9/2021
* File: micro_config.h
* Description: A file that contains microcontroller settings like F_CPU and includes
  libraries used for that microcontroller
==============================================================================
*/
#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

/* */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif /* MICRO_CONFIG_H_ */
