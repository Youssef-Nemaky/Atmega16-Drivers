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
*                                Static Function Prototypes  
==============================================================================
*/
#if (N_COLUMNS == 3)
static uint8 KEYPAD_4x3_adjustSwitchNumber(uint8 a_switchNumber);
#elif  (N_COLUMNS == 4)
static uint8 KEYPAD_4x4_adjustSwitchNumber(uint8 a_switchNumber);
#endif

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
            GPIO_writePort(KEYPAD_PORT, 0x0F);
            GPIO_setPortDirection(KEYPAD_PORT, PORT_INPUT);
            GPIO_setPinDirection(KEYPAD_PORT, columnsCounter + N_ROWS, PIN_OUTPUT);
            for(rowsCounter = 0; rowsCounter < N_ROWS; rowsCounter++){
                if(!GPIO_readPin(KEYPAD_PORT, rowsCounter)){
                    #if (N_COLUMNS == 4)
                    return KEYPAD_4x4_adjustSwitchNumber((rowsCounter * N_COLUMNS) + (columnsCounter + 1));
                    #elif (N_COLUMNS == 3)
                    return KEYPAD_4x3_adjustSwitchNumber((rowsCounter * N_COLUMNS) + (columnsCounter + 1));
                    #endif
                }
            }
        }
    }
}


#if (N_COLUMNS == 3)
static uint8 KEYPAD_4x3_adjustSwitchNumber(uint8 a_switchNumber){
    uint8 pressedKey;
    switch (a_switchNumber){
        case 10: pressedKey = '*';            break;
        case 11: pressedKey = 0;              break;
        case 12: pressedKey = '#';            break;
        default: pressedKey = a_switchNumber; break;
    }
    return pressedKey;
}
#elif  (N_COLUMNS == 4)
#if (PROTEUS_KEYPAD == TRUE)
static uint8 KEYPAD_4x4_adjustSwitchNumber(uint8 a_switchNumber){
    uint8 pressedKey;
    switch (a_switchNumber){
    case 1:   pressedKey = 7;                break;
    case 2:   pressedKey = 8;                break;
    case 3:   pressedKey = 9;                break;
    case 4:   pressedKey = '/';              break;
    case 5:   pressedKey = 4;                break;            
    case 6:   pressedKey = 5;                break;
    case 7:   pressedKey = 6;                break;
    case 8:   pressedKey = 'x';              break;
    case 9:   pressedKey = 1;                break;
    case 10:  pressedKey = 2;                break;
    case 11:  pressedKey = 3;                break;
    case 12:  pressedKey = '-';              break;
    case 13:  pressedKey = 'c';              break;
    case 14:  pressedKey = 0;                break;
    case 15:  pressedKey = '=';              break;
    case 16:  pressedKey = '+';              break;
    }
    return pressedKey;
}
#endif

#else
static uint8 KEYPAD_4x4_adjustSwitchNumber(uint8 a_switchNumber){
    uint8 pressedKey;
    switch (a_switchNumber){
    case 4:   pressedKey = 'A';              break;
    case 5:   pressedKey = 4;                break;
    case 6:   pressedKey = 5;                break;
    case 7:   pressedKey = 6;                break;
    case 8:   pressedKey = 'B';              break;            
    case 9:   pressedKey = 7;                break;
    case 10:  pressedKey = 8;                break;
    case 11:  pressedKey = 9;                break;
    case 12:  pressedKey = 'C';              break;
    case 13:  pressedKey = '*';              break;
    case 14:  pressedKey = 0;                break;
    case 15:  pressedKey = '#';              break;
    case 16:  pressedKey = 'D';              break;
    default: pressedKey = a_switchNumber;    break;
    }
    return pressedKey;
}
#endif