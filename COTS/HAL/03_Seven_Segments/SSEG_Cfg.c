/*******************************************************************
*   File name:    SSEG_Cfg.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations needed deal with SSEG HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "SSEG_Cfg.h"

/*
    NOTE: DON'T change values of the following Array
    BUT if you want to add new character so that your seven segments can support
    it you should go to SSEG_Cfg.h file and add name of character (ex: A_CHAR)
    and add the values of pins from (A as lsb to H as msb)
*/
const u8 SSEG_NumbersArr [10] = {
	[ZERO]  = 0b00111111,
	[ONE]   = 0b00000110,
	[TWO]   = 0b01011011,
	[THREE] = 0b01001111,
	[FOUR]  = 0b01100110,
	[FIVE]  = 0b01101101,
	[SIX]   = 0b01111101,
	[SEVEN] = 0b00000111,
	[EIGHT] = 0b01111111,
	[NINE]  = 0b01101111
};

/*
    Please follow the following sequence to add a new Seven segment
        1- Go to SSEG_Cfg.h file and add seven segment name to ssegInfo_t enum
        2- In this file, add a new element to the array in this form
            [ssegNameAsIn_ssegInfo_t] = {
						.ssegMode = SSEG_enuModeCommonCathode or SSEG_enuModeCommonAnode,
						.dotActivate = FALSE or TRUE,
						.ssegPins = {
										[A_PIN]   = DIO_enuPin0,
										[B_PIN]   = DIO_enuPin1,
										[C_PIN]   = DIO_enuPin2,
										[D_PIN]   = DIO_enuPin3,
										[E_PIN]   = DIO_enuPin4,
										[F_PIN]   = DIO_enuPin5,
										[G_PIN]   = DIO_enuPin6,
										[DOT_PIN] = DIO_enuPin7
									}
				  }
        3- Please add correct values:
            * For ssegPins use: DIO_enuPin0 to DIO_enuPin31
            * For ssegMode use only SSEG_enuModeCommonCathode or SSEG_enuModeCommonAnode
            * For dotActivate use only: FALSE or TRUE
            otherwise action will not applied (functions accepts only these values)
*/

const SSEG_strConfig_t ssegConfigArr [ssegCount] = 
	{
		[sseg1] = {
						.ssegMode = SSEG_enuModeCommonCathode,
						.dotActivate = FALSE,
						.ssegPins = {
										[A_PIN]   = DIO_enuPin0,
										[B_PIN]   = DIO_enuPin1,
										[C_PIN]   = DIO_enuPin2,
										[D_PIN]   = DIO_enuPin3,
										[E_PIN]   = DIO_enuPin4,
										[F_PIN]   = DIO_enuPin5,
										[G_PIN]   = DIO_enuPin6,
										[DOT_PIN] = DIO_enuPin7
									}
				  },
		[sseg2] = {
						.ssegMode = SSEG_enuModeCommonCathode,
						.dotActivate = TRUE,
						.ssegPins = {
										[A_PIN]   = DIO_enuPin8,
										[B_PIN]   = DIO_enuPin9,
										[C_PIN]   = DIO_enuPin10,
										[D_PIN]   = DIO_enuPin11,
										[E_PIN]   = DIO_enuPin12,
										[F_PIN]   = DIO_enuPin13,
										[G_PIN]   = DIO_enuPin14,
										[DOT_PIN] = DIO_enuPin15
									}	
		}
	};
