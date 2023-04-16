/*******************************************************************
*   File name:    PushButton.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with push button HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "../../../Lib/Bit_math.h"
#include "PushButton.h"

#define PB_STATE_CHANGE_TIMES       5

extern const PB_strconfig_t pbConfigArr [pbCount];
static u8 PB_arrPrevStates [pbCount];
static u8 PB_arrCounters [pbCount];
static u8 PB_arrActualStates [pbCount];

void PB_enuInit(void)
{
    // do nothing
}

PB_enuErrorStatus_t PB_enuGetButtonState(u8 cpy_u8ButtonName, pu8 add_pu8State)
{
    PB_enuErrorStatus_t Loc_enuErrorStatus = PB_enuNotOk;
    if(cpy_u8ButtonName >= 0 && cpy_u8ButtonName < (sizeof(pbConfigArr) / sizeof(PB_strconfig_t)))
    {
        if(add_pu8State == NULL)
        {
            Loc_enuErrorStatus = PB_enuNullPointer;
        }
        else
        {
            if(pbConfigArr[cpy_u8ButtonName].mode == PB_enuModePullDown || pbConfigArr[cpy_u8ButtonName].mode == PB_enuModePullUp)
            {
                *add_pu8State = PB_arrActualStates[cpy_u8ButtonName] ^ pbConfigArr[cpy_u8ButtonName].mode;
                Loc_enuErrorStatus = PB_enuOk;
            }
            else
            {
                Loc_enuErrorStatus = PB_enuUnknownMode;
            }
        }
    }
    else
    {
        Loc_enuErrorStatus = PB_enuInvalidPBName;
    }
    return Loc_enuErrorStatus;
}

void PB_vidRefreshButtonsReadingsTask(void)
{
    u8 Loc_u8Iterator, Loc_u8CurrentState;
    DIO_tenuErrorStatus Loc_enuDIOErrorStatus;
    for (Loc_u8Iterator = 0; Loc_u8Iterator < (sizeof(pbConfigArr) / sizeof(PB_strconfig_t)); Loc_u8Iterator++)
    {
        Loc_enuDIOErrorStatus = DIO_enuGetPin(pbConfigArr[Loc_u8Iterator].pin, &Loc_u8CurrentState);
        if(Loc_enuDIOErrorStatus == DIO_enuOK)
        {
            if(Loc_u8CurrentState == PB_arrPrevStates[Loc_u8Iterator])
            {
                PB_arrCounters[Loc_u8Iterator]++;
                if(PB_arrCounters[Loc_u8Iterator] == PB_STATE_CHANGE_TIMES)
                {
                    PB_arrActualStates[Loc_u8Iterator] = Loc_u8CurrentState;
                }
            }
            else
            {
                PB_arrCounters[Loc_u8Iterator] = 0;
            }
            PB_arrPrevStates[Loc_u8Iterator] = Loc_u8CurrentState;
        }
    }
}
