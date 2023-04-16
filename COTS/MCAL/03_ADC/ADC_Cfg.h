/*******************************************************************
*   File name:    ADC_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations to deal with ADC peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef ADC_CFG_H
#define ADC_CFG_H

/* Choose ADC mode (free running or auto triggered by source) */
#define ADC_MODE_FREE_RUNNING       0
#define ADC_MODE_ANALOG_COMPA       1
#define ADC_MODE_EXINT0             2
#define ADC_MODE_TIMR0_COMPA        3
#define ADC_MODE_TIMR0_OVF          4
#define ADC_MODE_TIMR1_COMP_B       5
#define ADC_MODE_TIMR1_OVF          6
#define ADC_MODE_TIMR1_CAP_EVENT    7

#define ADC_MDOE                    ADC_MODE_FREE_RUNNING

/* Choose ADC Prescaler */
#define ADC_PRES_2                  2
#define ADC_PRES_4                  4
#define ADC_PRES_8                  8
#define ADC_PRES_16                 16
#define ADC_PRES_32                 32
#define ADC_PRES_64                 64
#define ADC_PRES_128                128

#define ADC_PRESCALER               ADC_PRES_2

/* Choose if right adjust or left adjust */
#define ADC_RIGHT_ADJUST            0
#define ADC_LEFT_ADJUST             1

#define ADC_ADJUST                  ADC_RIGHT_ADJUST

/* Choose ADC VREF */

#define ADC_AVCC                    0
#define ADC_AREF                    1
#define ADC_INT                     2

#define ADC_VREF_SRC                ADC_AVCC

/* Choose ADC state */
#define ADC_EN                      1
#define ADC_DISABLE                 0

#define ADC_STATE                   ADC_EN

#endif