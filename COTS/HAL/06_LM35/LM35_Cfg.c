/*******************************************************************
*   File name:    LM35_Cfg.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations needed deal with LM35 HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "LM35_Cfg.h"

const LM35_strConfig_t LM35ConfigArr [lm35SensorsNum] = 
    {
        [sensor1] = {
                        .ADC_channel = ADC_CHANNEL_0,
                    },
        [sensor2] = {
                        .ADC_channel = ADC_CHANNEL_1,
                    }
    };