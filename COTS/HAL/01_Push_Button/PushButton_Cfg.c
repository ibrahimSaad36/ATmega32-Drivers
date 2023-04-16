/*******************************************************************
*   File name:    PushButton_Cfg.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all configuration array of push buttons to deal with buttons HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "PushButton_Cfg.h"

/*
    Please follow the following sequence to add a new push button
        1- Go to PushButton_Cfg.h file and add push button name to pbsInfo_t enum
        2- In this file, add a new element to the array in this form
            [pbNameInpbsInfo_t] = {
                                        .pin = DIO_enuPinNo,
                                        .mode = PB_enuModePullUp OR PB_enuModePullDown,
                                    }
        3- Please add correct values:
            * For pin use: DIO_enuPin0 to DIO_enuPin31
            * For mode use only PB_enuModePullUp or PB_enuModePullDown
*/

const PB_strconfig_t pbConfigArr [pbCount] = 
    {
        [pbStart] = {
                        .pin = DIO_enuPin0,
                        .mode = PB_enuModePullUp,
                     },
        [pbStop] = {
                        .pin = DIO_enuPin1,
                        .mode = PB_enuModePullDown,
                     }
    };