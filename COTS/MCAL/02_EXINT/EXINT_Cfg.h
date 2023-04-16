/*******************************************************************
*   File name:    EXINT_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations to deal with external interrupt
*                 in ATmega32
*   Version: v1.0
*******************************************************************/


#ifndef EXINT_CFG_H_
#define EXINT_CFG_H_

#define INT_EN			1
#define INT_DIS			0

#define RISING_EDGE		0
#define FALLING_EDGE	1
#define LOGICAL_CHANGE	2
#define LOW_LEVEL		3

#define INT0	INT_EN
#define INT1	INT_EN
#define INT2	INT_DIS

#define INT0_STATE	RISING_EDGE
#define INT1_STATE	FALLING_EDGE
#define INT2_STATE	FALLING_EDGE


#endif /* EXINT_CFG_H_ */