/*******************************************************************
*   File name:    TMR1_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations to deal with timer1 peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef TMR1_CFG_H
#define TMR1_CFG_H

#include "../../Lib/Std_types.h"

/* Choose timer1 mode */

#define TIMER1_MODE_NORMAL                  10
#define TIMER1_MODE_PCORR_PWM_8BITS         11
#define TIMER1_MODE_PCORR_PWM_9BITS         12
#define TIMER1_MODE_PCORR_PWM_10BITS        13
#define TIMER1_MODE_CTC_OCR                 14
#define TIMER1_MODE_CTC_ICR                 15
#define TIMER1_MODE_FPWM_8BITS              16
#define TIMER1_MODE_FPWM_9BITS              17
#define TIMER1_MODE_FPWM_10BITS             18
#define TIMER1_MODE_PWM_PHANDFREQ_CTRL_ICR  19
#define TIMER1_MODE_PWM_PHANDFREQ_CTRL_OCR  20
#define TIMER1_MODE_PCORR_PWM_ICR           21
#define TIMER1_MODE_PCORR_PWM_OCR           22
#define TIMER1_MODE_FPWM_ICR                23
#define TIMER1_MODE_FPWM_OCR                24

#define TIMER1_MODE                         TIMER1_MODE_NORMAL

#define TIMER1_CTC_DIS                      40
#define TIMER1_CTC_TGL                      41
#define TIMER1_CTC_CLR                      42
#define TIMER1_CTC_SET                      43

#define TIMER1_FPWM_DIS                     44
#define TIMER1_FPWM_INV                     45
#define TIMER1_FPWM_NINV                    46

#define TIMER1_PCORR_DIS                    47
#define TIMER1_PCORR_CUSD                   48
#define TIMER1_PCORR_SUCD                   49

#define TIMER1_CHANNEL_A_CTC_MODE           TIMER1_CTC_DIS
#define TIMER1_CHANNEL_B_CTC_MODE           TIMER1_CTC_DIS
#define TIMER1_CHANNEL_A_FPWM_MODE          TIMER1_FPWM_DIS
#define TIMER1_CHANNEL_B_FPWM_MODE          TIMER1_FPWM_DIS
#define TIMER1_CHANNEL_A_PCORR_PWM_MODE     TIMER1_PCORR_DIS
#define TIMER1_CHANNEL_B_PCORR_PWM_MODE     TIMER1_PCORR_DIS

/* Choose ICU Configuration */
#define ICU_ENABLED             40
#define ICU_DISABLED            41

#define ICU_STATUS              ICU_ENABLED

#define IC_EDGE_FALLING         28
#define IC_EDGE_RISING          29

#define IC_EDGE_SELECT          IC_EDGE_RISING

/* Choose timer1 prescaler */
#define TIMER1_PRESC_NO_PRES    0x0100
#define TIMER1_PRESC_PER8       0x0200
#define TIMER1_PRESC_PER64      0x0300
#define TIMER1_PRESC_PER256     0x0400
#define TIMER1_PRESC_PER1024    0x0500
#define TIMER1_EXT_FALLLING     0x0600
#define TIMER1_EXT_RISING       0x0700

#define TIMER1_PRESCALER        TIMER1_PRESC_PER8

#endif
