/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 16/11/2021
* Name: lcd.h
* Program/Purpose: lcd.h which includes all typedef/enums/structures and function
  prototypes used in lcd.c
==============================================================================
*/

#ifndef LCD_H_
#define LCD_H_

/*
==============================================================================
*                       Include gpio.h file
==============================================================================
*/
#include "../../MCAL/Gpio_Driver/gpio.h"

/*
==============================================================================
*                              Definitions
==============================================================================
*/
#define LCD_EIGHT_BIT_MODE 0
#define LCD_FOUR_BIT_MODE 1

/**** Settings To Change ****/
/* LCD MODE */
/* Choose between LCD_EIGHT_BIT_MODE or LCD_FOUR_BIT_MODE */
#define LCD_MODE LCD_EIGHT_BIT_MODE

/* LCD PORT */
#define LCD_PORT PORTA_ID

#if (LCD_MODE == LCD_FOUR_BIT_MODE)
#define LCD_PORT_HALF GPIO_FIRST_HALF
#endif
/******************* LCD COMMANDS *******************/

#define LCD_CMD_CLEAR_DISP                   (0x01)
#define LCD_CMD_RETURN_HOME                  (0x02)
#define LCD_CMD_DISP_OFF_CURSOR_OFF          (0x08)
#define LCD_CMD_DISP_OFF_CURSOR_ON           (0x0A)
#define LCD_CMD_DISP_ON_CURSOR_OFF           (0xOC)
#define LCD_CMD_DISP_ON_CURSOR_ON            (0x0F)
#define LCD_CMD_DISP_ON_CURSOR_BLINK         (0x0E)
#define LCD_CMD_TWO_LINES_MODE               (0x38)
#define LCD_CMD_FIRST_LINE_ADDRESS           (0x80)
#define LCD_CMD_SECOND_LINE_ADDRESS          (0xC0)
#define LCD_CMD_THRID_LINE_ADDRESS           (0x90)
#define LCD_CMD_FOURTH_LINE_ADDRESS          (0xD0)


/*
==============================================================================
*                                Function Prototypes  
==============================================================================
*/
/* DOCUMENTATION NEEDED */
void LCD_init();
void LCD_sendCommand(uint8 cmd);
void LCD_displayCharacter(uint8 characterToDisplay);
void LCD_displayString(uint8 * stringToDisplay);
void LCD_goToRowColumn(uint8 row, uint8 column);
void LCD_displayStringRowColumn(uint8 stringToDisplay, uint8 row, uint8 column);
void LCD_clearScreen();
void LCD_intgerToString(sint32);

#endif
