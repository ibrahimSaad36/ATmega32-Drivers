/*******************************************************************
*   File name:    DIO.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declarations to deal with DIO peripheral
*                 features in ATmega32
*   Version: v1.0
*******************************************************************/
#ifndef DIO_H
#define DIO_H

#include "DIO_Cfg.h"

typedef enum{
    DIO_enuOK = 0,
    DIO_enuNotOK,
    DIO_enuNullPointer
}DIO_tenuErrorStatus;

typedef enum{
	DIO_enuPin0,
	DIO_enuPin1,
	DIO_enuPin2,
	DIO_enuPin3,
	DIO_enuPin4,
	DIO_enuPin5,
	DIO_enuPin6,
	DIO_enuPin7,
	DIO_enuPin8,
	DIO_enuPin9,
	DIO_enuPin10,
	DIO_enuPin11,
	DIO_enuPin12,
	DIO_enuPin13,
	DIO_enuPin14,
	DIO_enuPin15,
	DIO_enuPin16,
	DIO_enuPin17,
	DIO_enuPin18,
	DIO_enuPin19,
	DIO_enuPin20,
	DIO_enuPin21,
	DIO_enuPin22,
	DIO_enuPin23,
	DIO_enuPin24,
	DIO_enuPin25,
	DIO_enuPin26,
	DIO_enuPin27,
	DIO_enuPin28,
	DIO_enuPin29,
	DIO_enuPin30,
	DIO_enuPin31,
	DIO_enuNumberOfPins
}DIO_enuPins_t;

typedef enum{
    DIO_enuLow = 0,
    DIO_enuHigh
}DIO_enuPinValue_t;


/*
    DIO init function
    Input: void
    Output: DIO_tenuErrorStatus
*/
DIO_tenuErrorStatus DIO_enuInit(void);
/*
    DIO set pin function
    Input: u8 (range from 0 to 31, otherwise error reported DIO_enuNotOK)
    Output: DIO_tenuErrorStatus
*/
DIO_tenuErrorStatus DIO_enuSetPin(DIO_enuPins_t cpy_u8PinNumber);
/*
    DIO clear pin function
    Input: u8 (range from 0 to 31, otherwise error reported DIO_enuNotOK)
    Output: DIO_tenuErrorStatus
*/
DIO_tenuErrorStatus DIO_enuClearPin(DIO_enuPins_t cpy_u8PinNumber);
/*
    get pin function
    Input: u8 (range from 0 to 31, otherwise error reported DIO_enuNotOK), and pointer to store value of pin in that address
    Output: DIO_tenuErrorStatus
*/
DIO_tenuErrorStatus DIO_enuGetPin(DIO_enuPins_t cpy_u8PinNumber, u8* add_pu8PinValue);


#endif