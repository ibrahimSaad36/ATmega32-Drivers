/*******************************************************************
*   File name:    LM35_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configuration data types needed to deal with LM35 HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef LM35_CFG_H
#define LM35_CFG_H

#include "../../Lib/Std_types.h"
#include "../../MCAL/03_ADC/ADC.h"

typedef struct
{
    u8 ADC_channel;
}LM35_strConfig_t;

typedef enum
{
    sensor1,
    sensor2,
    lm35SensorsNum,     /* DON'T change or remove this enumerator */
}LM35_enuSensorInfo_t;

#endif
