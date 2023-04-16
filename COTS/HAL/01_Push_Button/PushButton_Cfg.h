/*******************************************************************
*   File name:    PushButton_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all user defined data types for configuration to deal with push button HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef PUSHBUTTON_CFG_H
#define PUSHBUTTON_CFG_H

#include "../../Lib/Std_types.h"
#include "../../MCAL/00_DIO/DIO.h"

/*
    Suppoted mode must be from these values only
       PB_enuModePullUp or PB_enuModePullDown, 
*/

typedef enum
{
    PB_enuModePullDown = 0,
    PB_enuModePullUp,
}PB_enuMode_t;

/*
    To add a new push button add its name here (ex: pbActionDone) and then go to 
    PushButton_Cfg.c file and follow the steps there.
*/

typedef enum
{
    pbStart,
    pbStop,
    pbCount,  /* Don't change value of this enumerator or remove it */
}pbsInfo_t;

/*
    DON'T add or remove anything from this struct
*/

typedef struct
{
    u8 pin;
    PB_enuMode_t mode;
}PB_strconfig_t;


#endif
