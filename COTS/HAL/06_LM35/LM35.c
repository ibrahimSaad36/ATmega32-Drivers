/*******************************************************************
*   File name:    LM35.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definition needed deal with LM35 HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "LM35.h"

extern const LM35_strConfig_t LM35ConfigArr [lm35SensorsNum];

static LM35_enuErrorStatus_t LM35_enuGetTemp(LM35_enuSensorInfo_t cpy_enuSensorName, pu16 add_pu16Temp);

void LM35_vidInit(void)
{
    ADC_enuInit();
}

LM35_enuErrorStatus_t LM35_enuGetTemperatureC(LM35_enuSensorInfo_t cpy_enuSensorName, pu16 add_pu16Temp)
{
    return LM35_enuGetTemp(cpy_enuSensorName, add_pu16Temp);
}

LM35_enuErrorStatus_t LM35_enuGetTemperatureF(LM35_enuSensorInfo_t cpy_enuSensorName, pu16 add_pu16Temp)
{
    LM35_enuErrorStatus_t Loc_enuErrorStatus = LM35_enuGetTemp(cpy_enuSensorName, add_pu16Temp);
    if(Loc_enuErrorStatus == LM35_enuOk)
    {
        *add_pu16Temp = (*add_pu16Temp * (9.0 / 5)) + 32;
    }
    return Loc_enuErrorStatus;
}

static LM35_enuErrorStatus_t LM35_enuGetTemp(LM35_enuSensorInfo_t cpy_enuSensorName, pu16 add_pu16Temp)
{
    LM35_enuErrorStatus_t Loc_enuLm35ErrorStatus = LM35_enuNotOk;
    if(cpy_enuSensorName >= 0 && cpy_enuSensorName < (sizeof(LM35ConfigArr) / sizeof(LM35_strConfig_t)))
    {
        if(add_pu16Temp == NULL)
        {
            Loc_enuLm35ErrorStatus = LM35_enuNullPointer;
        }
        else
        {
            ADC_tenuErrorStatus Loc_enuAdcErrorStatus;
            u16 Loc_u16AdcValue;
            Loc_enuAdcErrorStatus = ADC_enuStartConversion(LM35ConfigArr[cpy_enuSensorName].ADC_channel);
            Loc_enuAdcErrorStatus = ADC_enuGetChannelValue(LM35ConfigArr[cpy_enuSensorName].ADC_channel, &Loc_u16AdcValue);
            if(Loc_enuAdcErrorStatus == ADC_enuOk)
            {
                *add_pu16Temp = ((u32) 500 * Loc_u16AdcValue) / 1023;
                Loc_enuLm35ErrorStatus = LM35_enuOk;
            }
            else
            {
                Loc_enuLm35ErrorStatus = LM35_enuErrorGetAdcValue;
            }
        }
    }
    else
    {
        Loc_enuLm35ErrorStatus = LM35_enuInvalidSensorName;
    }
    return Loc_enuLm35ErrorStatus;
}
