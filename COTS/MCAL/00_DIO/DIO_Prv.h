/*******************************************************************
*   File name:    DIO_Prv.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all registers required to deal with DIO peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef DIO_PRV_H
#define DIO_PRV_H

#include "../../Lib/Std_types.h"

/* PORTA */
#define PORTA *((volatile u8*) 0x3B)
#define DDRA  *((volatile u8*) 0x3A)
#define PINA  *((volatile u8*) 0x39)

/* PORTB */
#define PORTB *((volatile u8*) 0x38)
#define DDRB  *((volatile u8*) 0x37)
#define PINB  *((volatile u8*) 0x36)

/* PORTC */
#define PORTC *((volatile u8*) 0x35)
#define DDRC  *((volatile u8*) 0x34)
#define PINC  *((volatile u8*) 0x33)

/* PORTD */
#define PORTD  *((volatile u8*) 0x32)
#define DDRD   *((volatile u8*) 0x31)
#define PIND   *((volatile u8*) 0x30)

#endif