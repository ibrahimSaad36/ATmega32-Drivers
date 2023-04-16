/*******************************************************************
*   File name:    LED_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all user defined data types for configuration to deal with LED HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef LED_CFG_H
#define LED_CFG_H

#include "../../Lib/Std_types.h"
#include "../../MCAL/00_DIO/DIO.h"

#define LED_ON      1
#define LED_OFF     0

/*
    Suppoted mode must be from these values only
       LED_enuModeReverse or LED_enuModeForward, 
*/

typedef enum
{
    LED_enuModeReverse = 0,
    LED_enuModeForward,
}LED_enuMode_t;

/*
    To add a new LED add its name here (ex: ledActionDone) and then go to 
    LED_Cfg.c file and follow the steps there.
*/

typedef enum
{
    ledAlarm,
    ledStart,
    ledCount,  /* Don't change value of this enumerator or remove it */
}ledsInfo_t;

/*
    DON'T add or remove anything from this struct
*/

typedef struct
{
    u8 pin;
    LED_enuMode_t mode;
    u8 initialState;
}LED_strconfig_t;


#endif
