/*******************************************************************
*   File name:    ADC.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declrations to deal with ADC peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef ADC_H
#define ADC_H

#include "../../Lib/Std_types.h"

#define ADC_CHANNEL_0       0b00000000
#define ADC_CHANNEL_1       0b00000001
#define ADC_CHANNEL_2       0b00000010
#define ADC_CHANNEL_3       0b00000011
#define ADC_CHANNEL_4       0b00000100
#define ADC_CHANNEL_5       0b00000101
#define ADC_CHANNEL_6       0b00000110
#define ADC_CHANNEL_7       0b00000111

typedef enum 
{
    ADC_enuNotOk = 0,
    ADC_enuOk,
    ADC_enuInvalidInitOption,
    ADC_enuInvalidChannel,
    ADC_enuNullPointer,
    ADC_enuErrorChainBusy,
}ADC_tenuErrorStatus;

typedef enum
{
    ADC_enuChainBusy = 0,
    ADC_enuChainReady,
}ADC_tenuChainState;

typedef struct
{
    u8 chainLength;
    pu8 chainChannels;
    pu8 chainResults;
    void (*EOJ) (void);
}ADC_strChain_t;


ADC_tenuErrorStatus ADC_enuInit(void);
ADC_tenuErrorStatus ADC_enuEnableADC();
ADC_tenuErrorStatus ADC_enuDisbleADC();
ADC_tenuErrorStatus ADC_enuGetChannelValue(u8 cpy_u8Channel, pu16 add_pu16Value);
ADC_tenuErrorStatus ADC_enuStartConversion(u8 cpy_u8Channel);
ADC_tenuErrorStatus ADC_enuStartConversionAsync(ADC_strChain_t cpy_strChain);
ADC_tenuErrorStatus ADC_enuGetChainState(pu8 add_pu8State);
ADC_tenuErrorStatus ADC_enuSetADCCallBack(void (*cbf) (void));

#endif