/*******************************************************************
*   File name:    ADC_Priv.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all registers required to deal with ADC peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef ADC_PRV_H
#define ADC_PRV_H

#include "../../Lib/Std_types.h"

/* Registers */
#define ADMUX		 *((volatile pu8) 0x27)
#define ADCSRA		 *((volatile pu8) 0x26)
#define ADCH		 *((volatile pu8) 0x25)
#define ADCL		 *((volatile pu8) 0x24)
#define ADC_DATA     *((volatile pu16) 0x24)
#define SFIOR		 *((volatile pu8) 0x50)

#define NULL     ((void*) 0)

/* ISR */
#define ADC_ISR(vec)   void __vector_16 (void) __attribute__ ((signal)); \
					   void __vector_16 (void)

/* ADMUX bits and options */
// bits [7:6] VREF source
#define VREF_SRC_AREF       0b00000000  /* AREF: external*/
#define VREF_SRC_AVCC       0b01000000  /* VCC*/  
#define VREF_SRC_INT        0b11000000  /* Internal: 2.56v*/

#define ADMUX_ADLAR             5
#define ADMUX_ADLAR_RIGHT       0
#define ADMUX_ADLAR_LEFT        1

/* ADCSRA bits and options */
#define ADCSRA_ADEN    7
#define ADCSRA_ADSC    6
#define ADCSRA_ADATE   5
#define ADCSRA_ADIF    4
#define ADCSRA_ADIE    3

#define ADC_CONVERSION_DONE     1
#define ADC_CONVERTING          0
//ADPS [2:0] ADC Prescaler Select Bits
#define ADCSRA_PRESC_2        0b00000001
#define ADCSRA_PRESC_4        0b00000010
#define ADCSRA_PRESC_8        0b00000011
#define ADCSRA_PRESC_16       0b00000100
#define ADCSRA_PRESC_32       0b00000101
#define ADCSRA_PRESC_64       0b00000110
#define ADCSRA_PRESC_128      0b00000111

/* SFIOR bits and options */
//Auto trigger source [7:5]
#define ATS_FREE_RUNNING            0b00000000
#define ATS_ANALOG_COMP             0b00100000
#define ATS_EXINT0                  0b01000000
#define ATS_TIMR0_COMPA             0b01100000
#define ATS_TIMR0_OVF               0b10000000
#define ATS_TIMR1_COMP_B            0b10100000
#define ATS_TIMR1_OVF               0b11000000
#define ATS_TIMR1_CAP_EVENT         0b11100000

#endif