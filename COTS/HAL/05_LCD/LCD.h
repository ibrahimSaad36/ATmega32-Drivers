/*******************************************************************
*   File name:    LCD.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declaration to deal with LCD HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef LCD_H
#define LCD_H


#define F_CPU 8000000UL
#include <util/delay.h>

#include "../../Lib/Std_types.h"
#include "LCD_Cfg.h"

typedef enum
{
    LCD_enuNotOk = 0,
    LCD_enuOk,
    LCD_enuInvalidLocation,
    LCD_enuLCDBusy,
    LCD_enuErrorInInitConfig,
}LCD_tenuErrorStatus;

LCD_tenuErrorStatus LCD_enuInit(void);
LCD_tenuErrorStatus LCD_enuWriteCommand(u8 cpy_u8Cmd);
LCD_tenuErrorStatus LCD_enuWriteChar(u8 cpy_u8Char);
LCD_tenuErrorStatus LCD_enuWriteString(pu8 add_pu8String);
LCD_tenuErrorStatus LCD_enuWriteSpecialChar(pu8 cpy_u8Pattern, u8 cpy_u8Block, u8 cpy_u8X, u8 cpy_u8Y);
LCD_tenuErrorStatus LCD_enuWrtieNumber(s16 cpy_s16Num);
LCD_tenuErrorStatus LCD_enuClearScreen(void);
LCD_tenuErrorStatus LCD_enuGoToXY(u8 cpy_u8X, u8 cpy_u8Y);
LCD_tenuErrorStatus LCD_enuDisplayOn(void);
LCD_tenuErrorStatus LCD_enuDisplayOff(void);

#endif
