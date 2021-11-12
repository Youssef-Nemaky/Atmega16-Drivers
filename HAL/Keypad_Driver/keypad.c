/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 12/11/2021
* Name: keypad.c 
==============================================================================
*/

#include "keypad.h"

/*
==============================================================================
* [Function Name]: KEYPAD_getPressedKey
* [Description]: Used to check which key is pressed on the keypad and return it
* [Args]:
*   [in]: none
*   [out]: none
*   [in/out]: none
* [Returns]: uint8 indicating which key is pressed
==============================================================================
*/
uint8 KEYPAD_getPressedKey(void){
    uint8 rowsCounter = 0, columnsCounter = 0;
    /* loop until you find a pressed key */
    while(1){
        for(columnsCounter = 0; columnsCounter < N_COLUMNS; columnsCounter++){
            GPIO_setPortDirection(KEYPAD_PORT, PORT_INPUT);
            GPIO_setPinDirection(KEYPAD_PORT, columnsCounter, PIN_OUTPUT);
            GPIO_writePort(KEYPAD_PORT, 0x0F);
            for(rowsCounter = 0; rowsCounter < N_ROWS; rowsCounter++){
                if(!GPIO_readPin(KEYPAD_PORT, rowsCounter)){
                    #if (N_COLUMNS == 4)
                    return KEYPAD_4x4_adjustSwitchNumber((rowsCounter * N_ROWS) + (columnsCounter + 1));
                    #elif (N_COLUMNS == 3)
                    return KEYPAD_4x3_adjustSwitchNumber((rowsCounter * N_ROWS) + (columnsCounter + 1));;
                    #endif
                }
            }
        }
    }
}

