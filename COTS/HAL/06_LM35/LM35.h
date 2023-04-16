/*******************************************************************
*   File name:    LM35.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declaration to deal with LM35 HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef LM35_H
#define LM35_H

#include "LM35_Cfg.h"

typedef enum
{
    LM35_enuNotOk = 0,
    LM35_enuOk,
    LM35_enuNullPointer,
    LM35_enuInvalidSensorName,
    LM35_enuErrorGetAdcValue,
}LM35_enuErrorStatus_t;

void LM35_vidInit(void);
LM35_enuErrorStatus_t LM35_enuGetTemperatureC(LM35_enuSensorInfo_t cpy_enuSensorName, pu16 add_pu16Temp);
LM35_enuErrorStatus_t LM35_enuGetTemperatureF(LM35_enuSensorInfo_t cpy_enuSensorName, pu16 add_pu16Temp);

#endif
