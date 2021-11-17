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

#define LCD_SENDING_COMMAND 0
#define LCD_SENDING_DATA 1

/**** Start of Settings To Change ****/

/* LCD MODE */
/* Choose between LCD_EIGHT_BIT_MODE or LCD_FOUR_BIT_MODE */
#define LCD_MODE LCD_FOUR_BIT_MODE

#if (LCD_MODE == LCD_FOUR_BIT_MODE)
/* Select which half the LCD is connected to
 * Choose between 
 * 1) GPIO_FIRST_HALF
 * or
 * 2) GPIO_SECOND_HALF
 */
#define LCD_PORT_HALF GPIO_SECOND_HALF
#endif

/* LCD Data Port */
#define LCD_DATA_PORT PORTA_ID
/* LCD Control Pins Port */
#define LCD_CMD_PORT  PORTB_ID
/* LCD Control Pins */
#define LCD_RS PB0
#define LCD_RW PB1
#define LCD_EN PB2


/**** End of Settings To Change ****/


/******************* LCD COMMANDS *******************/

#define LCD_CMD_CLEAR_DISP                   (0x01)
#define LCD_CMD_RETURN_HOME                  (0x02)
#define LCD_CMD_DISP_OFF_CURSOR_OFF          (0x08)
#define LCD_CMD_DISP_OFF_CURSOR_ON           (0x0A)
#define LCD_CMD_DISP_ON_CURSOR_OFF           (0x0C)
#define LCD_CMD_DISP_ON_CURSOR_ON            (0x0F)
#define LCD_CMD_DISP_ON_CURSOR_BLINK         (0x0E)
#define LCD_CMD_TWO_LINES_8_BIT_MODE         (0x38)
#define LCD_CMD_TWO_LINES_4_BIT_MODE         (0x28)
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
void LCD_sendCommand(uint8 a_cmd);
void LCD_displayCharacter(uint8 a_characterToDisplay);
void LCD_displayString(const uint8 * a_stringToDisplay);
void LCD_goToRowColumn(uint8 a_row, uint8 a_column);
void LCD_displayStringRowColumn(const uint8 * a_stringToDisplay, uint8 a_row, uint8 a_column);
void LCD_clearScreen();
void LCD_intgerToString(sint32 a_numberToString);

#endif
