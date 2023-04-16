/*******************************************************************
*   File name:    TMR1_Prv.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all registers required to deal with timer1 peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/


#ifndef TMR1_PRV_H
#define TMR1_PRV_H

#include "../../Lib/Std_types.h"

#define SFIOR           *((volatile pu8 )  0x50)
#define TCCR1A          *((volatile pu8 )  0x4F)
#define TCCR1B          *((volatile pu8 )  0x4E)
#define TCCR1           *((volatile pu16)  0x4F)
#define TCNT1H          *((volatile pu8 )  0x4D)
#define TCNT1L          *((volatile pu8 )  0x4C)
#define TCNT1           *((volatile pu16)  0x4D)
#define OCR1AH          *((volatile pu8 )  0x4B)
#define OCR1AL          *((volatile pu8 )  0x4A)
#define OCR1A           *((volatile pu16)  0x4B)
#define OCR1BH          *((volatile pu8 )  0x49)
#define OCR1BL          *((volatile pu8 )  0x48)
#define OCR1B           *((volatile pu16)  0x49)
#define ICR1H           *((volatile pu8 )  0x47)
#define ICR1L           *((volatile pu8 )  0x46)
#define ICR1            *((volatile pu16)  0x47)
#define TIMSK           *((volatile pu8)   0x59)

#define SFIOR_PSR10     0

#define TCCR1A_FOC1A    3
#define TCCR1A_FOC1B    2

#define TIMSK_TICIE1    5
#define TIMSK_OCIE1A    4
#define TIMSK_OCIE1B    3
#define TIMSK_TOIE1     2

#endif
