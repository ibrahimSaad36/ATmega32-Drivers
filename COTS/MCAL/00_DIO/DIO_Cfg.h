/*******************************************************************
*   File name:    DIO_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations to deal with DIO peripheral
*                 features in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef DIO_CFG_H
#define DIO_CFG_H

#include "../../Lib/Std_types.h"

#define DIO_DIR_INPUT           0
#define DIO_DIR_OUTPUT          1
#define DIO_INPUT_PULL_UP       0
#define DIO_INPUT_PULL_DOWN     1

typedef struct{
    u8 DIO_PinDirection;
    u8 DIO_InputStatus;
}DIO_strPinCfg_t;

#endif