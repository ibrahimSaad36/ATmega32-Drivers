/*******************************************************************
*   File name:    TMR0.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declrations to deal with timer0 peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef TMR0_H
#define TMR0_H

#include "TMR0_Cfg.h"

typedef enum 
{
    TMR0_enuNotOk = 0,
    TMR0_enuOk,
    TMR0_enuNullPointer,
    TMR0_enuUnknownConfigMode,
    TMR0_enuOcPinDisconnected,
    TMR0_enuInvalidConfig,
    TMR0_enuInvalidDutyCycle,
}TMR0_enuErrorStatus_t;

typedef void (*TMR0cbf_t)(void);

void TMR0_vidInitPreCompile(void);
void TMR0_vidInitPostCompile(TMR0Config_t cpy_strTMR0Config);
TMR0_enuErrorStatus_t TMR0_enuSetTickTimeMS(u16 cpy_u16TickTime, u64 cpy_u32Clock);
TMR0_enuErrorStatus_t TMR0_enuStart(void);
TMR0_enuErrorStatus_t TMR0_enuRegisterCallback(TMR0cbf_t add_cbf);
TMR0_enuErrorStatus_t TMR0_enuSetDutyCycle(u8 cpy_u8DutyCycle);

#endif
