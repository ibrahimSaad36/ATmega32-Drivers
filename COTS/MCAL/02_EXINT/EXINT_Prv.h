/*******************************************************************
*   File name:    EXINT_Prv.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all registers required to deal with external interrupt
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef EXINT_PRV_H
#define EXINT_PRV_H

#include "../../Lib/Std_types.h"

#define AVR_MCUCR		    *((volatile u8*) 0x55)
#define AVR_MCUCSR		    *((volatile u8*) 0x54)
#define AVR_GICR		    *((volatile u8*) 0x5B)
#define AVR_GIFR		    *((volatile u8*) 0x5A)

#define INT0_SC_LL		    (0b00000000)
#define INT0_SC_LC		    (0b00000001)
#define INT0_SC_RE		    (0b00000011)
#define INT0_SC_FE		    (0b00000010)

#define INT1_SC_LL		    (0b00000000)
#define INT1_SC_LC		    (0b00000100)
#define INT1_SC_RE		    (0b00001100)
#define INT1_SC_FE		    (0b00001000)

#define INT2_SC_FE		    (0b00000000)
#define INT2_SC_RE		    (0b00100000)

#define MCUCR_INT0_0		0
#define MCUCR_INT0_1		1
#define MCUCR_INT1_0		2
#define MCUCR_INT1_1		3
#define MCUCSR_INT2			6

#define GICR_INT0			6
#define GICR_INT1			7
#define GICR_INT2			5

#define GIFR_INT0			6
#define GIFR_INT1			7
#define GIFR_INT2			5

#endif
