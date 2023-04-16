/*******************************************************************
*   File name:    SSEG_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configuration data types needed to deal with SSEG HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef SSEG_CFG_H
#define SSEG_CFG_H

#include "../../Lib/Std_types.h"
#include "../../MCAL/00_DIO/DIO.h"

#define ZERO        0
#define ONE         1
#define TWO         2
#define THREE       3
#define FOUR        4
#define FIVE        5
#define SIX         6
#define SEVEN       7
#define EIGHT       8
#define NINE        9

#define A_PIN       0
#define B_PIN       1
#define C_PIN       2
#define D_PIN       3
#define E_PIN       4
#define F_PIN       5
#define G_PIN       6
#define DOT_PIN     7

/*  
    Use TRUE or FALSE to indicate the status of dotActivate
*/

typedef enum
{
	FALSE = 0,
	TRUE,	
}Boolean_t;

/*  
    The mode of seven segments only accepts one of these two modes
    otherwise error is returned (SSEG_enuUnsupportedMode)
*/

typedef enum
{
	SSEG_enuModeCommonAnode = 0,
	SSEG_enuModeCommonCathode,
}SSEG_enuMode_t;

/*  
    The contents of this struct are used to represent all configurations of
    a seven segments
*/

typedef struct
{
	SSEG_enuMode_t ssegMode;
	Boolean_t dotActivate;
	u8 ssegPins[8];
}SSEG_strConfig_t;

/*  
    To add a new seven segment first add its name here and then follow
    the steps in SSEG_Cfg.c file
*/

typedef enum
{
	sseg1,
	sseg2,
	ssegCount,		/* DON'T remove or change value of this enumerator */
}ssegInfo_t;

#endif
