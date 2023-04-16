/*******************************************************************
*   File name:    KPad.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declaration to deal with KPAD HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef KPAD_H
#define KPAD_H

#include "KPad_Cfg.h"

typedef enum
{
	KPAD_enuOk = 0,
	KPAD_enuNotOk,
	KPAD_enuNullPointer
} KPAD_enuErrorStatus;

KPAD_enuErrorStatus KPAD_enuGetKey(u8* add_u8Key);

#endif
