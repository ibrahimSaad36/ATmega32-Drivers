/*******************************************************************
*   File name:    LCD_Prv.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all specifications for LCD HAL driver
*   Version: v1.0
*******************************************************************/

#ifndef LCD_PRV_H
#define LCD_PRV_H

#define NULL ((void*) 0)

#define LCD_CMD_8BITS_2LINE     0b00111100
#define LCD_CMD_4BITS_2LINE     0b00101100
#define LCD_CMD_CLR_SCR         0x01
#define LCD_CMD_DISP_ON         0b00001100
#define LCD_CMD_DISP_OFF        0b00001000
#define LCD_CMD_CURS_BLI        0b00001111
#define LCD_CMD_CURS_FIX        0b00001110
#define LCD_CMD_CURS_AUTO       0b00000110

#define LCD_BUSY_MSK         0b10000000
#define LCD_BUSY             0b10000000
#define LCD_NOT_BUSY         0

#endif
