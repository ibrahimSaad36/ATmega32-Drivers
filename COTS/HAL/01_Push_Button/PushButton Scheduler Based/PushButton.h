/*******************************************************************
*   File name:    PushButton.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs prototypes to deal with push button HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "PushButton_Cfg.h"

#define PB_PRESSED      1
#define PB_RELEASED     0

typedef enum
{
    PB_enuNotOk = 0,
    PB_enuOk,
    PB_enuInvalidPBName,
    PB_enuUnknownMode,
    PB_enuNullPointer,
}PB_enuErrorStatus_t;


/**********************************************************
    Description:       This function do nothing
    Input parameters:  void (no inputs expected)
    Return:            void (no return)
***********************************************************/
void PB_enuInit(void);


/**********************************************************
    Description:       This function used to get the state of the push button if it pressed or released
    Input parameters:  expected name of push button as written in pbsInfo_t in PushButton_Cfg.h file
    Return:            PB_enuErrorStatus_t with the following values:
                            * PB_enuUnknownMode: if mode of push button not PB_enuModePullDown or PB_enuModePullUp
                            * PB_enuInvalidPBName: if push button name doesn't exist in pbConfigArr
                            * PB_enuNotOk: if there was error while reading the state of push button
                            * PB_enuOk: if reading of the push button state is done correctly
    State of push button:
                       State of push button will be returned in a pointer of u8 and it will contain only one value
                       of the following:
                            *  PB_PRESSED: in case of push button is pressed
                            *  PB_RELEASED: in case of push button released
***********************************************************/
PB_enuErrorStatus_t PB_enuGetButtonState(u8 cpy_u8ButtonName, pu8 add_pu8State);

void PB_vidRefreshButtonsReadingsTask(void);

#endif
