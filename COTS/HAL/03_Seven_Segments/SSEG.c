/*******************************************************************
*   File name:    SSEG.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definition needed deal with SSEG HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "SSEG.h"

#define DOT_INDEX	    7
#define STATE_LOW	    0
#define STATE_HIGH	    1

extern const u8 SSEG_NumbersArr [10];
extern const SSEG_strConfig_t ssegConfigArr [ssegCount];

static u8 countNmberDigits(u8 cpy_u8Number)
{
	u8 count = 0;
	if (cpy_u8Number == 0)
	{
		count = 1;
	}
	else
	{
		while(cpy_u8Number != 0)
		{
			count++;
			cpy_u8Number /= 10;
		}
	}
	return count;
}

static SSEG_enuErrorStatus_t SSEG_enuWriteToPins(u8 cpy_u8Name, u8 cpy_u8Number)
{
	SSEG_enuErrorStatus_t Loc_enuErrorStatus = SSEG_enuNotOk;
	u8 Loc_u8Iterator;
	u8 Loc_u8State;
	for(Loc_u8Iterator = 0; Loc_u8Iterator < 8 && Loc_enuErrorStatus == DIO_enuOK; Loc_u8Iterator++)
	{
		Loc_u8State = ((cpy_u8Number & (1 << Loc_u8Iterator)) >> Loc_u8Iterator);
		if (Loc_u8State == STATE_HIGH)
		{
			Loc_enuErrorStatus = DIO_enuSetPin(ssegConfigArr[cpy_u8Name].ssegPins[Loc_u8Iterator]);
		}
		else if (Loc_u8State == STATE_LOW)
		{
			Loc_enuErrorStatus = DIO_enuClearPin(ssegConfigArr[cpy_u8Name].ssegPins[Loc_u8Iterator]);
		}
	}
	return Loc_enuErrorStatus;
}

void SSEG_voidInit()
{
    // do nothing
}

SSEG_enuErrorStatus_t SSEG_enuWriteNumber(u8 cpy_u8Name, u8 cpy_u8Number)
{
	SSEG_enuErrorStatus_t Loc_enuErrorStatus = SSEG_enuNotOk;
	if (cpy_u8Name >= 0 && cpy_u8Name < (sizeof(ssegConfigArr) / sizeof(SSEG_strConfig_t)))
	{
		if (cpy_u8Number >= 0 && cpy_u8Number <= 9)
		{
			if (ssegConfigArr[cpy_u8Name].ssegMode == SSEG_enuModeCommonCathode)
			{
				Loc_enuErrorStatus = SSEG_enuWriteToPins(cpy_u8Name, SSEG_NumbersArr[cpy_u8Number]);
				if (ssegConfigArr[cpy_u8Name].dotActivate == TRUE && Loc_enuErrorStatus == DIO_enuOK)
				{
					Loc_enuErrorStatus = DIO_enuSetPin(ssegConfigArr[cpy_u8Name].ssegPins[DOT_INDEX]);
					if (Loc_enuErrorStatus == DIO_enuOK)
					{
						Loc_enuErrorStatus = SSEG_enuOk;
					}
					else
					{
						Loc_enuErrorStatus = SSEG_enuNotOk;
					}
				}
			}
			else if (ssegConfigArr[cpy_u8Name].ssegMode == SSEG_enuModeCommonAnode)
			{
				Loc_enuErrorStatus = SSEG_enuWriteToPins(cpy_u8Name, ~SSEG_NumbersArr[cpy_u8Number]);
				if (ssegConfigArr[cpy_u8Name].dotActivate == TRUE && Loc_enuErrorStatus == DIO_enuOK)
				{
					Loc_enuErrorStatus = DIO_enuClearPin(ssegConfigArr[cpy_u8Name].ssegPins[DOT_INDEX]);
					if (Loc_enuErrorStatus == DIO_enuOK)
					{
						Loc_enuErrorStatus = SSEG_enuOk;
					}
					else
					{
						Loc_enuErrorStatus = SSEG_enuNotOk;
					}
				}
			}
			else
			{
				Loc_enuErrorStatus = SSEG_enuUnsupportedMode;
			}
		}
		else
		{
			Loc_enuErrorStatus = SSEG_enuUnsupportedNumber;
		}
	}
	else
	{
		Loc_enuErrorStatus = SSEG_enuInvalidName;
	}
}

SSEG_enuErrorStatus_t SSEG_enuWriteToMultipleSegs(ssegInfo_t* add_ssegInfoArr, u8 cpy_u8ArrSize,u8 cpy_u8Number)
{
	SSEG_enuErrorStatus_t Loc_enuErrorStatus = SSEG_enuNotOk;
	if (countNmberDigits(cpy_u8Number) == cpy_u8ArrSize)
	{
		s8 Loc_u8Iterator = cpy_u8ArrSize - 1;
		u8 Loc_u8DisplayNumber;
        u8 Loc_u8ConfigArrSize = sizeof(ssegConfigArr) / sizeof(SSEG_strConfig_t);
        while(cpy_u8Number != 0 && Loc_enuErrorStatus == DIO_enuOK)
		{
            if (add_ssegInfoArr[Loc_u8Iterator] >= 0 && add_ssegInfoArr[Loc_u8Iterator] < Loc_u8ConfigArrSize)
            {
                Loc_u8DisplayNumber = cpy_u8Number % 10;
                cpy_u8Number /= 10;
                if ((ssegConfigArr[add_ssegInfoArr[Loc_u8Iterator]]).ssegMode == SSEG_enuModeCommonCathode)
                {
                    Loc_enuErrorStatus = SSEG_enuWriteToPins(add_ssegInfoArr[Loc_u8Iterator], SSEG_NumbersArr[Loc_u8DisplayNumber]);
                    if ((ssegConfigArr[add_ssegInfoArr[Loc_u8Iterator]]).dotActivate == TRUE)
                    {
                        Loc_enuErrorStatus = DIO_enuSetPin((ssegConfigArr[add_ssegInfoArr[Loc_u8Iterator]]).ssegPins[DOT_INDEX]);
                    }
                }
                else if ((ssegConfigArr[add_ssegInfoArr[Loc_u8Iterator]]).ssegMode == SSEG_enuModeCommonAnode)
                {
                    Loc_enuErrorStatus = SSEG_enuWriteToPins(add_ssegInfoArr[Loc_u8Iterator], ~SSEG_NumbersArr[Loc_u8DisplayNumber]);
                    if ((ssegConfigArr[add_ssegInfoArr[Loc_u8Iterator]]).dotActivate == TRUE)
                    {
                        Loc_enuErrorStatus = DIO_enuClearPin((ssegConfigArr[add_ssegInfoArr[Loc_u8Iterator]]).ssegPins[DOT_INDEX]);
                    }
                }
                else
                {
                    Loc_enuErrorStatus = SSEG_enuUnsupportedMode;
                    break;
                }
                Loc_u8Iterator--;
            }
			else
            {
                Loc_enuErrorStatus = SSEG_enuInvalidName;
                break;
            }
		}
        if (Loc_enuErrorStatus == DIO_enuOK)
        {
            Loc_enuErrorStatus = SSEG_enuOk;
        }
        else
        {
            Loc_enuErrorStatus = SSEG_enuNotOk;
        }
	}
	else
	{
		Loc_enuErrorStatus = SSEG_enuNumberCanNotFit;
	}
	return Loc_enuErrorStatus;
}

