/*******************************************************************
*   File name:    SSEG.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declaration to deal with SSEG HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef SSEG_H
#define SSEG_H

#include "SSEG_Cfg.h"

typedef enum
{
	SSEG_enuNotOk = 0,
	SSEG_enuOk,
	SSEG_enuUnsupportedNumber,
	SSEG_enuInvalidName,
	SSEG_enuUnsupportedMode,
	SSEG_enuNumberCanNotFit,
}SSEG_enuErrorStatus_t;

/**********************************************************
    Description:       This function do nothing
    Input parameters:  void (no inputs expected)
    Return:            void (no return)
***********************************************************/
void SSEG_voidInit();


/**********************************************************
    Description:       This function used to write a number to a specific seven segment unit
    Input parameters:  Expected name of SSEG as written in ssegInfo_t
                       and a number from 0 to 9 only
    Return:            SSEG_enuErrorStatus_t with the following values:
                            * SSEG_enuOk: if number is written correctly to the SSEG unit
                            * SSEG_enuNotOk: if couldn't display number to SSEG unit due to an issue setting or clearing
                              pin or invalid pin written in configurations
                            * SSEG_enuUnsupportedMode: if mode in ssegConfigArr is invalid (not SSEG_enuModeCommonAnode or SSEG_enuModeCommonCathode)
                            * SSEG_enuUnsupportedNumber: if number is out of range (0 to 9)
                            * SSEG_enuInvalidName: if the name SSEG unit is invalid (the name must match the name written in ssegInfo_t)
***********************************************************/
SSEG_enuErrorStatus_t SSEG_enuWriteNumber(u8 cpy_u8Name, u8 cpy_u8Number);


/**********************************************************
    Description:       This function used to write a number to a group of seven segment units,
                       this number must fit into these units and each digit of the number will be displayed
                       to a single unit.
    Input parameters:  Expected array of SSEG units names as written in ssegInfo_t
                       and the numbers of units or cpy_u8ArrSize
                       and a number from 0 to 255 and it must fit with the number of units passed to function
    Return:            SSEG_enuErrorStatus_t with the following values:
                            * SSEG_enuOk: if number is written correctly to the SSEG units
                            * SSEG_enuNotOk: if couldn't display number to SSEG unit due to an issue setting or clearing
                              pin or invalid pin written in configurations
                            * SSEG_enuUnsupportedMode: if mode in ssegConfigArr is invalid (not SSEG_enuModeCommonAnode or SSEG_enuModeCommonCathode)
                            * SSEG_enuInvalidName: if the name SSEG unit is invalid (the name must match the name written in ssegInfo_t)
                            * SSEG_enuNumberCanNotFit: if the passed number can't fit to the number of units
***********************************************************/
SSEG_enuErrorStatus_t SSEG_enuWriteToMultipleSegs(ssegInfo_t* add_ssegInfoArr, u8 cpy_u8ArrSize,u8 cpy_u8Number);

#endif
