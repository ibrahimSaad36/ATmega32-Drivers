/*******************************************************************
*   File name:    TMR1.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declrations to deal with timer1 peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef TMR1_H
#define TMR1_H

#include "TMR1_Prv.h"
#include "TMR1_Cfg.h"

typedef void (*TMR1_pfCallback_t)(void);

typedef enum
{
    TMR1_enuNotOk = 0,
    TMR1_enuOk,
    TMR1_enuNullPointer,
    TMR1_enuInvalidConfig,
    TMR1_enuInvalidOCRValue,
}TMR1_enuErrorStatus_t;

void TMR1_vidInit(void);
TMR1_enuErrorStatus_t TMR1_enuStart(void);
TMR1_enuErrorStatus_t TMR1_enuSetTicktimeMS(u32 cpy_u32Ticktime, u64 cpy_u64Clock);
TMR1_enuErrorStatus_t TMR1_enuSetDutyCycleChannelA(u8 cpy_u8Duty);
TMR1_enuErrorStatus_t TMR1_enuSetDutyCycleChannelB(u8 cpy_u8Duty);
TMR1_enuErrorStatus_t TMR1_enuSetOutCompareMatchChannelA(u16 cpy_u16CompareMatchVal);
TMR1_enuErrorStatus_t TMR1_enuSetOutCompareMatchChannelB(u16 cpy_u16CompareMatchVal);
TMR1_enuErrorStatus_t TMR1_enuStop(void);
TMR1_enuErrorStatus_t TMR1_enuSetOVCallback(TMR1_pfCallback_t add_pfCallback);
TMR1_enuErrorStatus_t TMR1_enuSetCompareMatchACallback(TMR1_pfCallback_t add_pfCallback);
TMR1_enuErrorStatus_t TMR1_enuSetCompareMatchBCallback(TMR1_pfCallback_t add_pfCallback);
TMR1_enuErrorStatus_t TMR1_enuSetICUCallback(TMR1_pfCallback_t add_pfCallback);

#endif
