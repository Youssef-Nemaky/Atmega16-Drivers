/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 25/10/2021
* Name: seven_segment.c 
==============================================================================
*/

/*
==============================================================================
*                            Include Files
==============================================================================
*/
#include "seven_segment.h"

/*
==============================================================================
*                                 Functions  
==============================================================================
*/

/* 
 * Setup the pins for the seven segment display   
 * if the port number or portHalf are not correct, the request is not handled
 */
void SEVENSEGMENT_init(const SEVENSEGMENT_config_t * configPtr){
    /* Call GPIO init function to set the half of the port direction */
    GPIO_setHalfPortDirection(configPtr->portNumber, PORT_OUTPUT, configPtr->portHalf);
}

/* 
 * Display a number to the seven-segment 
 * seven segment uses 4 pins -> 4 bits -> max value: 2^4 - 1 = 0xF (15) 
 */
void SEVENSEGMENT_displayNumber(const SEVENSEGMENT_config_t * configPtr, uint8 numToDisplay){
    GPIO_writeHalfPort(configPtr->portNumber, numToDisplay, configPtr->portHalf);
}
