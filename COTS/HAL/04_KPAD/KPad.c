/*******************************************************************
*   File name:    KPad.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definition needed deal with KPad HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "../../Lib/Bit_math.h"
#include "KPad_Cfg.h"
#include "KPad.h"

extern const u8 KPAD_arrRows[MAX_ROWS];
extern const u8 KPAD_arrCols[MAX_COLS];
extern const u8 KPAD_arrChars [MAX_ROWS][MAX_COLS];

KPAD_enuErrorStatus KPAD_enuGetKey(u8* add_u8Key)
{
    u8 Loc_u8RowIterator;
    u8 Loc_u8ColIterator;
	u8 Loc_u8Temp;
    KPAD_enuErrorStatus Loc_enuErrorStatus = KPAD_enuNotOk;
    if(add_u8Key == NULL){
        Loc_enuErrorStatus = KPAD_enuNullPointer;
    }
	else
	{
		for(Loc_u8RowIterator = 0; Loc_u8RowIterator < MAX_ROWS; Loc_u8RowIterator++){
			DIO_enuClearPin(KPAD_arrRows[Loc_u8RowIterator]);
			for (Loc_u8ColIterator = 0; Loc_u8ColIterator < MAX_COLS; Loc_u8ColIterator++){
				DIO_enuGetPin(KPAD_arrCols[Loc_u8ColIterator], &Loc_u8Temp);
				if(Loc_u8Temp == 0)
				{
					*add_u8Key = KPAD_arrChars[Loc_u8RowIterator][Loc_u8ColIterator];
				}
			}
			DIO_enuSetPin(KPAD_arrRows[Loc_u8RowIterator]);
		}
	}
    return Loc_enuErrorStatus;
}