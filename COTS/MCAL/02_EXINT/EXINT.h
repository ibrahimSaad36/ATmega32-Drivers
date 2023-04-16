/*******************************************************************
*   File name:    EXINT.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declrations to deal with external interrupt
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef EXINT_H_
#define EXINT_H_

typedef void (*EXINT_pfCallBack_t)(void);

typedef enum
{
	EXINT_enuOk = 0,
	EXINT_enuNotOk,
	EXINT_enuNotSupportedInterruptName,
	EXINT_enuNotSupportedInterruptOption,
	EXINT_enuNullPointer,
} EXINT_enuErrorStatus;
typedef enum
{
	EXINT_enuINT0 = 0,
	EXINT_enuINT1,
	EXINT_enuINT2
}EXINT_enuInterruptNumber;

EXINT_enuErrorStatus EXINT_enuInit(void);
EXINT_enuErrorStatus EXINT_enuEnableInterrupt(EXINT_enuInterruptNumber cpy_enuInterrupt, u8 cpy_u8Option);
EXINT_enuErrorStatus EXINT_enuDisableInterrupt(EXINT_enuInterruptNumber cpy_enuInterrupt);
EXINT_enuErrorStatus EXINT_enuSetCallBack(EXINT_enuInterruptNumber cpy_enuInterrupt, EXINT_pfCallBack_t add_pfCallBack);

#endif /* EXINT_H_ */