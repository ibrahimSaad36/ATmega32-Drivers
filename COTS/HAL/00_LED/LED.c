/*******************************************************************
*   File name:    LED.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with LED HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "../../Lib/Bit_math.h"
#include "LED.h"

extern const LED_strconfig_t ledConfigArr [ledCount];

LED_enuErrorStatus_t LED_enuInit(void)
{
    LED_enuErrorStatus_t Loc_enuErrorStatus = LED_enuNotOk;
    u8 Loc_u8ArrSize = sizeof(ledConfigArr) / sizeof(LED_strconfig_t);
    u8 Loc_u8Iterator;
    for (Loc_u8Iterator = 0; Loc_u8Iterator < Loc_u8ArrSize && Loc_enuErrorStatus == DIO_enuOK; Loc_u8Iterator++)
    {
        if(ledConfigArr[Loc_u8Iterator].initialState == LED_ON)
        {
            if(ledConfigArr[Loc_u8Iterator].mode == LED_enuModeForward)
            {
                Loc_enuErrorStatus = DIO_enuSetPin(ledConfigArr[Loc_u8Iterator].pin);
            }
            else if(ledConfigArr[Loc_u8Iterator].mode == LED_enuModeReverse)
            {
                Loc_enuErrorStatus = DIO_enuClearPin(ledConfigArr[Loc_u8Iterator].pin);
            }
            else
            {
                Loc_enuErrorStatus = LED_enuUnknownMode;
            }
        }
        else if(ledConfigArr[Loc_u8Iterator].initialState == LED_OFF)
        {
            if(ledConfigArr[Loc_u8Iterator].mode == LED_enuModeForward)
            {
                Loc_enuErrorStatus = DIO_enuClearPin(ledConfigArr[Loc_u8Iterator].pin);
            }
            else if(ledConfigArr[Loc_u8Iterator].mode == LED_enuModeReverse)
            {
                Loc_enuErrorStatus = DIO_enuSetPin(ledConfigArr[Loc_u8Iterator].pin);
            }
            else
            {
                Loc_enuErrorStatus = LED_enuUnknownMode;
            }
        }
        else
        {
            Loc_enuErrorStatus = LED_enuUnknownInitialState;
        }
    }
    return Loc_enuErrorStatus;
}

LED_enuErrorStatus_t LED_enuSetLedOn(u8 cpy_u8LedName)
{
    LED_enuErrorStatus_t Loc_enuErrorStatus = LED_enuNotOk;
    if(cpy_u8LedName >= 0 && cpy_u8LedName < (sizeof(ledConfigArr) / sizeof(LED_enuErrorStatus_t)))
    {
        if (ledConfigArr[cpy_u8LedName].mode == LED_enuModeForward)
        {
            Loc_enuErrorStatus = DIO_enuSetPin(ledConfigArr[cpy_u8LedName].pin);
        }
        else if (ledConfigArr[cpy_u8LedName].mode == LED_enuModeReverse)
        {
            Loc_enuErrorStatus = DIO_enuClearPin(ledConfigArr[cpy_u8LedName].pin);
        }
        else
        {
            Loc_enuErrorStatus = LED_enuUnknownMode;
        }
    }
    else
    {
        Loc_enuErrorStatus = LED_enuInvalidLedNo;
    }
    return Loc_enuErrorStatus;
}

LED_enuErrorStatus_t LED_enuSetLedOff(u8 cpy_u8LedName)
{
    LED_enuErrorStatus_t Loc_enuErrorStatus = LED_enuNotOk;
    if(cpy_u8LedName >= 0 && cpy_u8LedName < (sizeof(ledConfigArr) / sizeof(LED_enuErrorStatus_t)))
    {
        if (ledConfigArr[cpy_u8LedName].mode == LED_enuModeForward)
        {
            Loc_enuErrorStatus = DIO_enuClearPin(ledConfigArr[cpy_u8LedName].pin);
        }
        else if (ledConfigArr[cpy_u8LedName].mode == LED_enuModeReverse)
        {
            Loc_enuErrorStatus = DIO_enuSetPin(ledConfigArr[cpy_u8LedName].pin);
        }
        else
        {
            Loc_enuErrorStatus = LED_enuUnknownMode;
        }
    }
    else
    {
        Loc_enuErrorStatus = LED_enuInvalidLedNo;
    }
    return Loc_enuErrorStatus;
}