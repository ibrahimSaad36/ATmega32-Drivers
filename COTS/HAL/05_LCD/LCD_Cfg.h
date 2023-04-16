/*******************************************************************
*   File name:    LCD_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configuration data types needed to deal with LCD HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef LCD_CFG_H
#define LCD_CFG_H

#include "../../MCAL/00_DIO/DIO.h"

#define LCD_RS          DIO_enuPin31     /* PORTD PIN7*/
#define LCD_RW          DIO_enuPin30     /* PORTD PIN6*/
#define LCD_EN          DIO_enuPin29     /* PORTD PIN5*/

/*
    Choose from:
        PORT_A, PORT_B, PORT_C, PORT_D
*/
#define LCD_DATA_LINES  PORT_C   

#define LCD_4BIT        0
#define LCD_8BIT        1

#define LCD_MODE        LCD_8BIT

#define LCD_DISP_ON     1
#define LCD_DISP_OFF    0

#define LCD_DISP_INIT   LCD_DISP_ON

#define LCD_CURS_BLINK  1
#define LCD_CURS_FIXED  0

#define LCD_CURS_MODE   LCD_CURS_FIXED

#endif
