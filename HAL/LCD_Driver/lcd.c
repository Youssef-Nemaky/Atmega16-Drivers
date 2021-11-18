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
void LCD_displayString(const uint8 * a_stringToDisplay){
    uint8 counter = 0; 
    while(a_stringToDisplay[counter] != '\0'){
        LCD_displayCharacter(a_stringToDisplay[counter]);
        counter++;
    }
}

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
void LCD_displayStringRowColumn(const uint8 * a_stringToDisplay, uint8 a_row, uint8 a_column){
    LCD_goToRowColumn(a_row, a_column);
    LCD_displayString(a_stringToDisplay);
}

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
void LCD_goToRowColumn(uint8 a_row, uint8 a_column){
    uint8 cmdToSend;
    switch (a_row){
    case 0:
        cmdToSend = LCD_CMD_FIRST_LINE_ADDRESS + a_column;
        break;
    case 1:
        cmdToSend = LCD_CMD_SECOND_LINE_ADDRESS + a_column;
        break;
    case 2:
        cmdToSend = LCD_CMD_THRID_LINE_ADDRESS + a_column;
        break;
    case 3:
        cmdToSend = LCD_CMD_FOURTH_LINE_ADDRESS + a_column;
        break;
    }
    LCD_sendCommand(cmdToSend);
}

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
void LCD_clearScreen(){
    LCD_sendCommand(LCD_CMD_CLEAR_DISP);
}

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
void LCD_displayInteger(sint32 a_numberToDisplay){
    /* Why 12?
     * The largest number in a signed number of 32 bits is 2,147,483,647 = 10 numbers
     * and the lowest number is -2,147,483,648 -> 10 numbers + 1 for the sign = 11 numbers
     * and if we add the string terminator we have 12 number(buffer size)     
     */
    uint8 buffer[12];

    uint8 counter = 0, i = 0;

    if(a_numberToDisplay == 0){
        /* display zero on the LCD */
        LCD_displayCharacter('0');
        /* Exit from the function by returning */
        return;
    } else if(a_numberToDisplay < 0){
        /* in case of negative number */
        
        /* Add the sign to the buffer */
        buffer[counter++] = '-';
        /* Make the number positive */
        a_numberToDisplay = -a_numberToDisplay;

        /* start i at 1 to leave the sign at reversing the number */
        i = 1;
    } 

    while(a_numberToDisplay != 0){
        /* Add the last digit in the number to the buffer */
        buffer[counter++] = (a_numberToDisplay % 10) + '0';

        /* Update the number after dividing by 10 */
        a_numberToDisplay /= 10;
    }

    /* Add the string terminator \0 to the buffer */
    buffer[counter--] = '\0';

    /* Now we need to reverse the number */
    for(;i < counter; i++, counter--){
        buffer[i] = buffer[i] ^ buffer[counter]; 
        buffer[counter] = buffer[i] ^ buffer[counter]; 
        buffer[i] = buffer[i] ^ buffer[counter]; 
    }
    /* Display the number */
    LCD_displayString(buffer);
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