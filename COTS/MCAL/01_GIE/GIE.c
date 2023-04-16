/*******************************************************************
*   File name:    GIE.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with global interrupt
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#include "../../Lib/Bit_math.h"
#include "GIE_Prv.h"
#include "GIE.h"

GIE_enuErrorStatus GIE_enuEnable()
{
    SET_BIT(AVR_SREG, GI_BIT);
    return GIE_enuOk;
}

GIE_enuErrorStatus GIE_enuDisable()
{
    CLR_BIT(AVR_SREG, GI_BIT);
    return GIE_enuOk;
}