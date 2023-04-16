/*******************************************************************
*   File name:    GIE_Prv.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all registers required to deal with global interrupt
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef GIE_PRV_H
#define GIE_PRV_H

#include "../../Lib/Std_types.h"

#define AVR_SREG *((volatile u8*) 0x5F)
#define GI_BIT 7

#endif
