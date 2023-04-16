/*******************************************************************
*   File name:    KPad_Cfg.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations needed deal with KPAD HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "KPad_Cfg.h"

const u8 KPAD_arrRows[MAX_ROWS] = {
	DIO_enuPin0,
	DIO_enuPin1,
	DIO_enuPin2,
	DIO_enuPin3,
};
const u8 KPAD_arrCols[MAX_COLS] = {
	DIO_enuPin4,
	DIO_enuPin5,
	DIO_enuPin6,
};

const u8 KPAD_arrChars [MAX_ROWS][MAX_COLS] = {
                    {'1', '2', '3'},
                    {'4', '5', '6'},
                    {'7', '8', '9'},
                    {'*', '0', '#'}
                 };
