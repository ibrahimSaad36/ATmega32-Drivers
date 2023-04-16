/*******************************************************************
*   File name:    TMR0_Prv.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all registers required to deal with timer0 peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef TMR0_PRV_H
#define TMR0_PRV_H

#include "../../Lib/Std_types.h"

#define NULL          ((void*) 0)

#define OCR0          *((volatile pu8) 0x5C)
#define TIMSK         *((volatile pu8) 0x59)
#define TIFR          *((volatile pu8) 0x58)
#define TCCR0         *((volatile pu8) 0x53) 
#define TCNT0         *((volatile pu8) 0x52)
#define SFIOR         *((volatile pu8) 0x50)

#define TCCR0_CS00      0
#define TCCR0_CS01      1
#define TCCR0_CS02      2
#define TCCR0_WGM01     3
#define TCCR0_COM00     4
#define TCCR0_COM01     5       /* DDR must be configured also */
#define TCCR0_WGM00     6
#define TCCR0_FOC0      7       /* Requires non PWM mode, update OC0 pin and no interrupt */

#define TIMSK_TOIE0     0
#define TIMSK_OCIE0     1

#define TIFR_TOV0       0
#define TIFR_OCF0       1

#define SFIOR_PSR10     0       /*  Prescaler Reset Timer/Counter1 and Timer/Counter0 */

#endif
