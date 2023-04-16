/*******************************************************************
*   File name:    GIE.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declrations to deal with global interrupt
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef GIE_H
#define GIE_H

typedef enum
{
    GIE_enuOk = 0,
    GIE_enuNotOk
} GIE_enuErrorStatus;

GIE_enuErrorStatus GIE_enuEnable();
GIE_enuErrorStatus GIE_enuDisable();

#endif
