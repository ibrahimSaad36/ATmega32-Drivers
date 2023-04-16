/*******************************************************************
*   File name:    PushButton.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with push button HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "../../Lib/Bit_math.h"
#include "PushButton.h"

extern const PB_strconfig_t pbConfigArr [pbCount];

void PB_enuInit(void)
{
    // do nothing
}

PB_enuErrorStatus_t PB_enuGetButtonState(u8 cpy_u8ButtonName, pu8 add_pu8State)
{
    PB_enuErrorStatus_t Loc_enuErrorStatus = PB_enuNotOk;
    if(cpy_u8ButtonName >= 0 && cpy_u8ButtonName < (sizeof(pbConfigArr) / sizeof(PB_strconfig_t)))
    {
        u8 Loc_u8PinState;
        Loc_enuErrorStatus = DIO_enuGetPin(pbConfigArr[cpy_u8ButtonName].pin, &Loc_u8PinState);
        if(Loc_enuErrorStatus == DIO_enuOK)
        {
            if(pbConfigArr[cpy_u8ButtonName].mode == PB_enuModePullDown || pbConfigArr[cpy_u8ButtonName].mode == PB_enuModePullUp)
            {
                *add_pu8State = Loc_u8PinState ^ pbConfigArr[cpy_u8ButtonName].mode;
                Loc_enuErrorStatus = PB_enuOk;
            }
            else
            {
                Loc_enuErrorStatus = PB_enuUnknownMode;
            }
        }
        else
        {
            Loc_enuErrorStatus = PB_enuNotOk;
        }
    }
    else
    {
        Loc_enuErrorStatus = PB_enuInvalidPBName;
    }
    return Loc_enuErrorStatus;
}
