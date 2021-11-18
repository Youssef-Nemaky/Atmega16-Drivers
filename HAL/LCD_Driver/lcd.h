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

/*
==============================================================================
* [Function Name]: LCD_init
* [Description]: Used to initialize the LCD by setting the right port direction.
* [Args]:
*   [in]: none
*   [out]: none
*   [in/out]: none
* [Returns]: none
==============================================================================
*/
void LCD_init();

/*
==============================================================================
* [Function Name]: LCD_sendCommand
* [Description]: Used to send a command to the LCD.
*                (EX: 0x02 which is clearscreen)
* [Args]:
*   [in]: uint8: cmd the command you want to send to the LCD.
*   [out]: none
*   [in/out]: none
* [Returns]: none
==============================================================================
*/
void LCD_sendCommand(uint8 a_cmd);

/*
==============================================================================
* [Function Name]: LCD_displayCharacter
* [Description]: Used to display a character on the LCD.
* [Args]:
*   [in]: uint8: chracterToDisplay: The character you want to display on the LCD.
*   [out]: none
*   [in/out]: none
* [Returns]: none
==============================================================================
*/
void LCD_displayCharacter(uint8 a_characterToDisplay);

/*
==============================================================================
* [Function Name]: LCD_displayString
* [Description]: Used to display a string on the LCD.
* [Args]:
*   [in]: const uint8 *: stringToDisplay: A pointer to constant data pointing to 
*         the string you want to display on the LCD.
*   [out]: none
*   [in/out]: none
* [Returns]: none
==============================================================================
*/
void LCD_displayString(const uint8 * a_stringToDisplay);

/*
==============================================================================
* [Function Name]: LCD_goTowRowColumn
* [Description]: Used to go to a specific location (row,column) on the LCD.
* [Args]:
*   [in1]: uint8: row: the row you want to jump to.
*   [in2]: uint8: column: the column you want to jump to.
*   [out]: none
*   [in/out]: none
* [Returns]: none
==============================================================================
*/
void LCD_goToRowColumn(uint8 a_row, uint8 a_column);

/*
==============================================================================
* [Function Name]: LCD_displayStringRowColumn
* [Description]: Used to display string on the LCD on a specific row and column
*                SMALL NOTE: counting start at 0 (EX: first row is at 0 index)
* [Args]:
*   [in1]: const uint8 *: stringToDisplay: A pointer to constant data pointing to 
*         the string you want to display on the LCD.
*   [in2]: uint8: row: the row at which the string will be displayed
*   [in3]: uint8: column: the column at which the string will start being displayed.
*   [out]: none
*   [in/out]: none
* [Returns]: none
==============================================================================
*/
void LCD_displayStringRowColumn(const uint8 * a_stringToDisplay, uint8 a_row, uint8 a_column);

/*
==============================================================================
* [Function Name]: LCD_clearScreen
* [Description]: Used to clear the LCD screen.
* [Args]:
*   [in]: none
*   [out]: none
*   [in/out]: none
* [Returns]: none
==============================================================================
*/
void LCD_clearScreen();

/*
==============================================================================
* [Function Name]: LCD_displayInteger
* [Description]: Used to display an integer on the LCD screen.
* [Args]:
*   [in]: sint32 a_numberToDisplay: the number you want to display on the LCD.
*   [out]: none
*   [in/out]: none
* [Returns]: none
==============================================================================
*/
void LCD_displayInteger(sint32 a_numberToDisplay);

#endif
