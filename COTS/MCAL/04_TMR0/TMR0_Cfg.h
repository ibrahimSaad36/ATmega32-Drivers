/*******************************************************************
*   File name:    TMR0_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations to deal with timer0 peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef TMR0_CFG_H
#define TMR0_CFG_H

#include "../../Lib/Std_types.h"

/* TIMER0 mode of operation */
#define TMR0_MODE_NORMAL            0x11
#define TMR0_MODE_CTC               0x12
#define TMR0_MODE_FAST_PWM_DIS      0x17
#define TMR0_MODE_FAST_PWM_INV      0x18        /* (inverting) set on compare clear at BOOTOM */
#define TMR0_MODE_FAST_PWM_NINV     0x19        /* (non-inverting) clear on compare set at BOTTOM */
#define TMR0_MODE_PCORR_PWM_DIS     0x1A
#define TMR0_MODE_PCORR_PWM_CUSD    0x1B        /* Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting */
#define TMR0_MODE_PCORR_PWM_SUCD    0x1C        /* Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting */

#define TMR0_MODE                   TMR0_MODE_FAST_PWM_INV

/* TIMER0 CTC modes */
#define TMR0_MODE_CTC_COM_DIS       0x13
#define TMR0_MODE_CTC_COM_TGL       0x14
#define TMR0_MODE_CTC_COM_CLR       0x15
#define TMR0_MODE_CTC_COM_SET       0x16

#define TMR0_CTC_MODE               TMR0_MODE_CTC_COM_SET

/* TIMER0 initial state */
#define TMR0_INIT_STOOPED           0x31
#define TMR0_INIT_RUNNING           0x32

#define TMR0_INIT_STATE             TMR0_INIT_RUNNING

/* TIMER0 prescaler */
#define TMR0_NO_PRESC               0x21  
#define TMR0_PER8_PRESC             0x22
#define TMR0_PER64_PRESC            0x23
#define TMR0_PER256_PRESC           0x24
#define TMR0_PER1024_PRESC          0x25
#define TMR0_EXT_T0_FALLING         0x26
#define TMR0_EXT_T0_RISING          0x27

#define TMR0_CLOCK_SRC              TMR0_PER8_PRESC

typedef struct
{
    u8 timerMode;
    u8 clockSource;
    u8 compareMatchOutMode;
}TMR0Config_t;

#endif
