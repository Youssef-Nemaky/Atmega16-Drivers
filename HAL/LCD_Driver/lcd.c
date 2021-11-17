/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 16/11/2021
* Name: lcd.c 
==============================================================================
*/

#include "lcd.h"


/*
==============================================================================
*                                LCD Macros  
==============================================================================
*/
#ifndef GET_HIGH_NIBBLE
#define GET_HIGH_NIBBLE(VAR) ((VAR & 0xF0)>>4)
#endif

#ifndef GET_LOW_NIBBLE
#define GET_LOW_NIBBLE(VAR) ((VAR & 0x0F))
#endif

/*
==============================================================================
*                          Static Function Prototypes  
==============================================================================
*/
static void LCD_writingSequence(uint8 a_option);

/*
==============================================================================
*                                  Functions  
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
void LCD_init(){

    /* Set the port direction for LCD and init the LCD */

    /* Set control pins to be output */
    GPIO_setPinDirection(LCD_CMD_PORT, LCD_RS, PIN_OUTPUT);
    GPIO_setPinDirection(LCD_CMD_PORT, LCD_RW, PIN_OUTPUT);
    GPIO_setPinDirection(LCD_CMD_PORT, LCD_EN, PIN_OUTPUT);


    #if (LCD_MODE == LCD_FOUR_BIT_MODE)
    GPIO_setHalfPortDirection(LCD_DATA_PORT, PORT_OUTPUT, LCD_PORT_HALF);
    LCD_sendCommand(LCD_CMD_RETURN_HOME);
    LCD_sendCommand(LCD_CMD_TWO_LINES_4_BIT_MODE);

    #else
    GPIO_setPortDirection(LCD_DATA_PORT, PORT_OUTPUT);
    LCD_sendCommand(LCD_CMD_TWO_LINES_8_BIT_MODE);

    #endif

    LCD_sendCommand(LCD_CMD_DISP_ON_CURSOR_OFF);

    LCD_clearScreen();
    LCD_displayString("LCD Initialized!");
    _delay_ms(500);
    LCD_clearScreen();
}

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
void LCD_sendCommand(uint8 a_cmd){
    #if (LCD_MODE == LCD_FOUR_BIT_MODE)
    GPIO_writeHalfPort(LCD_DATA_PORT, GET_HIGH_NIBBLE(a_cmd), LCD_PORT_HALF);
    LCD_writingSequence(LCD_SENDING_COMMAND);
    
    GPIO_writeHalfPort(LCD_DATA_PORT, GET_LOW_NIBBLE(a_cmd), LCD_PORT_HALF);
    LCD_writingSequence(LCD_SENDING_COMMAND);

    #elif (LCD_MODE == LCD_EIGHT_BIT_MODE)
    GPIO_writePort(LCD_DATA_PORT, a_cmd);
    LCD_writingSequence(LCD_SENDING_COMMAND);
    #endif
}


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
void LCD_displayCharacter(uint8 a_characterToDisplay){
    #if (LCD_MODE == LCD_FOUR_BIT_MODE)
    GPIO_writeHalfPort(LCD_DATA_PORT, GET_HIGH_NIBBLE(a_characterToDisplay), LCD_PORT_HALF);
    LCD_writingSequence(LCD_SENDING_DATA);

    GPIO_writeHalfPort(LCD_DATA_PORT, GET_LOW_NIBBLE(a_characterToDisplay), LCD_PORT_HALF);
    LCD_writingSequence(LCD_SENDING_DATA);
    #elif (LCD_MODE == LCD_EIGHT_BIT_MODE)
    GPIO_writePort(LCD_DATA_PORT, a_characterToDisplay);
    LCD_writingSequence(LCD_SENDING_DATA);
    #endif    
}

/*
==============================================================================
*                               Static Functions  
==============================================================================
*/

/*
==============================================================================
* [Function Name]: LCD_writingSequence
* [Description]: Used to initiaite the writing sequence of the LCD to send either
*               a command or a character. 
* [Args]:
*   [in]: uint8 : option: either choose between sending a command or a character.
*   [out]: none
*   [in/out]: none
* [Returns]: none
==============================================================================
*/
static void LCD_writingSequence(uint8 a_option){
    /* Check whether you are sending a command or data */
    if(a_option == LCD_SENDING_COMMAND){
        /* Make RS -> LOW to select command register */
        GPIO_writePin(LCD_CMD_PORT, LCD_RS, LOW);
    } else {
        /* Make RS -> HIGH to select data register */
        GPIO_writePin(LCD_CMD_PORT, LCD_RS, HIGH);
    }
    /* Make RW -> LOW to select writing to the LCD */
    GPIO_writePin(LCD_CMD_PORT, LCD_RW, LOW);
    
    /* A high to low pulse on enable pin */
    GPIO_writePin(LCD_CMD_PORT, LCD_EN, HIGH);
    _delay_ms(1); /* A delay of 1 ms */
    GPIO_writePin(LCD_CMD_PORT, LCD_EN, LOW);
    _delay_ms(2); /* A delay of 2 ms */
}