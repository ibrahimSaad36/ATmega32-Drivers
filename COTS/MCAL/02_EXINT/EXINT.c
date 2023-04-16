/*******************************************************************
*   File name:    EXINT.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with external interrupt
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#include "../../Lib/Bit_math.h"
#include "EXINT_Prv.h"
#include "EXINT_Cfg.h"
#include "EXINT.h"

#define INTERRUPTS_NUMBER		3

static EXINT_pfCallBack_t extint_Callback [INTERRUPTS_NUMBER] = {NULL, NULL, NULL};

EXINT_enuErrorStatus EXINT_enuInit(void)
{
	EXINT_enuErrorStatus Loc_enuErrorStatus = EXINT_enuNotOk;
	u8 temp = AVR_MCUCR;
	#if INT0 == INT_EN
		#if INT0_STATE == RISING_EDGE
			CLR_BIT(temp, MCUCR_INT0_0);
			CLR_BIT(temp, MCUCR_INT0_1);
			temp = temp | INT0_SC_RE;
			AVR_MCUCR = temp;
			SET_BIT(AVR_GICR, GICR_INT0);
			Loc_enuErrorStatus = EXINT_enuOk;
		#elif INT0_STATE == FALLING_EDGE
			CLR_BIT(temp, MCUCR_INT0_0);
			CLR_BIT(temp, MCUCR_INT0_1);
			temp = temp | INT0_SC_FE;
			AVR_MCUCR = temp;
			SET_BIT(AVR_GICR, GICR_INT0);
			Loc_enuErrorStatus = EXINT_enuOk;
		#elif INT0_STATE == LOGICAL_CHANGE
			CLR_BIT(temp, MCUCR_INT0_0);
			CLR_BIT(temp, MCUCR_INT0_1);
			temp = temp | INT0_SC_LC;
			AVR_MCUCR = temp;
			SET_BIT(AVR_GICR, GICR_INT0);
			Loc_enuErrorStatus = EXINT_enuOk;
		#elif INT0_STATE == LOW_LEVEL
			CLR_BIT(temp, MCUCR_INT0_0);
			CLR_BIT(temp, MCUCR_INT0_1);
			temp = temp | INT0_SC_LL;
			AVR_MCUCR = temp;
			SET_BIT(AVR_GICR, GICR_INT0);
			Loc_enuErrorStatus = EXINT_enuOk;
		#else
			Loc_enuErrorStatus = EXINT_enuNotSupportedInterruptOption;
		#endif
	#endif
	#if INT1 == INT_EN
		#if INT1_STATE == RISING_EDGE
			CLR_BIT(temp, MCUCR_INT1_0);
			CLR_BIT(temp, MCUCR_INT1_1);
			temp = temp | INT1_SC_RE;
			AVR_MCUCR = temp;
			SET_BIT(AVR_GICR, GICR_INT1);
			Loc_enuErrorStatus = EXINT_enuOk;
		#elif INT1_STATE == FALLING_EDGE
			CLR_BIT(temp, MCUCR_INT1_0);
			CLR_BIT(temp, MCUCR_INT1_1);
			temp = temp | INT1_SC_FE;
			AVR_MCUCR = temp;
			SET_BIT(AVR_GICR, GICR_INT1);
			Loc_enuErrorStatus = EXINT_enuOk;
		#elif INT1_STATE == LOGICAL_CHANGE
			CLR_BIT(temp, MCUCR_INT1_0);
			CLR_BIT(temp, MCUCR_INT1_1);
			temp = temp | INT1_SC_LC;
			AVR_MCUCR = temp;
			SET_BIT(AVR_GICR, GICR_INT1);
			Loc_enuErrorStatus = EXINT_enuOk;
		#elif INT1_STATE == LOW_LEVEL
			CLR_BIT(temp, MCUCR_INT1_0);
			CLR_BIT(temp, MCUCR_INT1_1);
			temp = temp | INT1_SC_LL;
			AVR_MCUCR = temp;
			SET_BIT(AVR_GICR, GICR_INT1);
			Loc_enuErrorStatus = EXINT_enuOk;
		#else
			Loc_enuErrorStatus = EXINT_enuNotSupportedInterruptOption;
		#endif
	#endif
	#if INT2 == INT_EN
		#if INT2_STATE == RISING_EDGE
			CLR_BIT(AVR_MCUCSR, MCUCSR_INT2);
			SET_BIT(AVR_GICR, GICR_INT2);
		#elif INT2_STATE == FALLING_EDGE
			SET_BIT(AVR_MCUCSR, MCUCSR_INT2);
			SET_BIT(AVR_GICR, GICR_INT2);
		#else
			Loc_enuErrorStatus = EXINT_enuNotSupportedInterruptOption;
		#endif
	#endif
	return Loc_enuErrorStatus;
}

EXINT_enuErrorStatus EXINT_enuEnableInterrupt(EXINT_enuInterruptNumber cpy_enuInterrupt, u8 cpy_u8Option)
{
	EXINT_enuErrorStatus Loc_enuErrorStatus = EXINT_enuNotOk;
	u8 temp = AVR_MCUCR;
	switch (cpy_enuInterrupt)
	{
		case EXINT_enuINT0:
			switch (cpy_u8Option)
			{
				case RISING_EDGE:
					CLR_BIT(temp, MCUCR_INT0_0);
					CLR_BIT(temp, MCUCR_INT0_1);
					temp = temp | INT0_SC_RE;
					AVR_MCUCR = temp;
					SET_BIT(AVR_GICR, GICR_INT0);
					Loc_enuErrorStatus = EXINT_enuOk;
					break;
				case FALLING_EDGE:
					CLR_BIT(temp, MCUCR_INT0_0);
					CLR_BIT(temp, MCUCR_INT0_1);
					temp = temp | INT0_SC_FE;
					AVR_MCUCR = temp;
					SET_BIT(AVR_GICR, GICR_INT0);
					Loc_enuErrorStatus = EXINT_enuOk;
					break;
				case LOGICAL_CHANGE:
					CLR_BIT(temp, MCUCR_INT0_0);
					CLR_BIT(temp, MCUCR_INT0_1);
					temp = temp | INT0_SC_LC;
					AVR_MCUCR = temp;
					SET_BIT(AVR_GICR, GICR_INT0);
					Loc_enuErrorStatus = EXINT_enuOk;
					break;
				case LOW_LEVEL:
					CLR_BIT(temp, MCUCR_INT0_0);
					CLR_BIT(temp, MCUCR_INT0_1);
					temp = temp | INT0_SC_LL;
					AVR_MCUCR = temp;
					SET_BIT(AVR_GICR, GICR_INT0);
					Loc_enuErrorStatus = EXINT_enuOk;
					break;
				default:
					Loc_enuErrorStatus = EXINT_enuNotSupportedInterruptOption;
			}
			break;
		case EXINT_enuINT1:
			switch (cpy_u8Option)
			{
				case RISING_EDGE:
					CLR_BIT(temp, MCUCR_INT1_0);
					CLR_BIT(temp, MCUCR_INT1_1);
					temp = temp | INT1_SC_RE;
					AVR_MCUCR = temp;
					SET_BIT(AVR_GICR, GICR_INT1);
					Loc_enuErrorStatus = EXINT_enuOk;
					break;
				case FALLING_EDGE:
					CLR_BIT(temp, MCUCR_INT1_0);
					CLR_BIT(temp, MCUCR_INT1_1);
					temp = temp | INT1_SC_FE;
					AVR_MCUCR = temp;
					SET_BIT(AVR_GICR, GICR_INT1);
					Loc_enuErrorStatus = EXINT_enuOk;
					break;
				case LOGICAL_CHANGE:
					CLR_BIT(temp, MCUCR_INT1_0);
					CLR_BIT(temp, MCUCR_INT1_1);
					temp = temp | INT1_SC_LC;
					AVR_MCUCR = temp;
					SET_BIT(AVR_GICR, GICR_INT1);
					Loc_enuErrorStatus = EXINT_enuOk;
					break;
				case LOW_LEVEL:
					CLR_BIT(temp, MCUCR_INT1_0);
					CLR_BIT(temp, MCUCR_INT1_1);
					temp = temp | INT1_SC_LL;
					AVR_MCUCR = temp;
					SET_BIT(AVR_GICR, GICR_INT1);
					Loc_enuErrorStatus = EXINT_enuOk;
					break;
			
				default:
					Loc_enuErrorStatus = EXINT_enuNotSupportedInterruptOption;
			}
			break;
		case EXINT_enuINT2:
			switch (cpy_u8Option)
			{
				case FALLING_EDGE:
					CLR_BIT(AVR_MCUCSR, MCUCSR_INT2);
					SET_BIT(AVR_GICR, GICR_INT2);
					break;
				case RISING_EDGE:
					SET_BIT(AVR_MCUCSR, MCUCSR_INT2);
					SET_BIT(AVR_GICR, GICR_INT2);
					break;
				default:
					Loc_enuErrorStatus = EXINT_enuNotSupportedInterruptOption;
			}
			break;
		default:
			Loc_enuErrorStatus = EXINT_enuNotSupportedInterruptName;
	}
	return Loc_enuErrorStatus;
}

EXINT_enuErrorStatus EXINT_enuDisableInterrupt(EXINT_enuInterruptNumber cpy_enuInterrupt)
{
	EXINT_enuErrorStatus Loc_enuErrorStatus = EXINT_enuNotOk;
	switch (cpy_enuInterrupt){
		case EXINT_enuINT0:
			CLR_BIT(AVR_GICR, GICR_INT0);
			Loc_enuErrorStatus = EXINT_enuOk;
			break;
		case EXINT_enuINT1:
			CLR_BIT(AVR_GICR, GICR_INT1);
			Loc_enuErrorStatus = EXINT_enuOk;
			break;
		case EXINT_enuINT2:
			CLR_BIT(AVR_GICR, GICR_INT2);
			Loc_enuErrorStatus = EXINT_enuOk;
			break;
		default:
			Loc_enuErrorStatus = EXINT_enuNotSupportedInterruptName;
	}
	return Loc_enuErrorStatus;
}

EXINT_enuErrorStatus EXINT_enuSetCallBack(EXINT_enuInterruptNumber cpy_enuInterrupt, EXINT_pfCallBack_t add_pfCallBack)
{
	EXINT_enuErrorStatus Loc_enuErrorStatus = EXINT_enuNotOk;
	if (cpy_enuInterrupt >= EXINT_enuINT0 && cpy_enuInterrupt <= EXINT_enuINT2)
	{
		if (add_pfCallBack == NULL)
		{
			Loc_enuErrorStatus = EXINT_enuNullPointer;
		}
		else
		{
			extint_Callback[cpy_enuInterrupt] = add_pfCallBack;
		}
	}
	else
	{
		Loc_enuErrorStatus = EXINT_enuNotSupportedInterruptName;
	}
	return Loc_enuErrorStatus;
}

/* INT0 ISR */
void __vector_1 (void) __attribute__ ((signal));
void __vector_1 (void)
{
	if (extint_Callback[EXINT_enuINT0] != NULL)
	{
		extint_Callback[EXINT_enuINT0]();
	}
}

/* INT1 ISR */
void __vector_2 (void) __attribute__ ((signal));
void __vector_2 (void)
{
	if (extint_Callback[EXINT_enuINT1] != NULL)
	{
		extint_Callback[EXINT_enuINT1]();
	}
}

/* INT2 ISR */
void __vector_3 (void) __attribute__ ((signal));
void __vector_3 (void)
{
	if (extint_Callback[EXINT_enuINT2] != NULL)
	{
		extint_Callback[EXINT_enuINT2]();
	}
}

