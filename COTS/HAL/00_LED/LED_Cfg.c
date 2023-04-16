/*******************************************************************
*   File name:    LED_Cfg.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all configuration array of LEDs to deal with LED HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "LED_Cfg.h"

/*
    Please follow the following sequence to add a new LED
        1- Go to LED_Cfg.h file and add LED name to ledsInfo_t enum
        2- In this file, add a new element to the array in this form
            [ledNameInledsInfo_t] = {
                                        .pin = DIO_enuPinNo,
                                        .mode = LED_enuModeForward OR LED_enuModeReverse,
                                        .initialState = LED_ON OR LED_OFF,
                                    }
        3- Please add correct values:
            * For pin use: DIO_enuPin0 to DIO_enuPin31
            * For mode use only LED_enuModeForward or LED_enuModeReverse
            * For initialState use only: LED_ON or LED_OFF
            otherwise action will not applied (functions accepts only these values)
*/

const LED_strconfig_t ledConfigArr [ledCount] = 
    {
        [ledAlarm] = {
                        .pin = DIO_enuPin0,
                        .mode = LED_enuModeForward,
                        .initialState = LED_ON,
                     },
        [ledStart] = {
                        .pin = DIO_enuPin1,
                        .mode = LED_enuModeForward,
                        .initialState = LED_OFF,
                     }
    };