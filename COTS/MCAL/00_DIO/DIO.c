/*******************************************************************
*   File name:    DIO.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with DIO peripheral
*                 features in ATmega32
*   Version: v1.0
*******************************************************************/

#include "DIO_Prv.h"
#include "DIO.h"
#include "../../Lib/Bit_math.h"

#define PORT_A          0
#define PORT_B          1
#define PORT_C          2
#define PORT_D          3

extern const DIO_strPinCfg_t DIO_strPinCfg [32];

DIO_tenuErrorStatus DIO_enuInit(void){
    u8 i;
	DIO_tenuErrorStatus Loc_enuErrorState = DIO_enuNotOK;
    for(i = 0; i < DIO_enuNumberOfPins; i++){
        u8 Loc_u8Port = i / 8;
        u8 Loc_u8PinNumber = i % 8;
        switch (Loc_u8Port)
        {
            case PORT_A:
                if(DIO_strPinCfg[i].DIO_PinDirection == DIO_DIR_OUTPUT){
                    SET_BIT(DDRA, Loc_u8PinNumber);
                }else{
                    CLR_BIT(DDRA, Loc_u8PinNumber);
                    if(DIO_strPinCfg[i].DIO_InputStatus == DIO_INPUT_PULL_UP)
                        SET_BIT(PORTA, Loc_u8PinNumber);
                }
				Loc_enuErrorState = DIO_enuOK;
                break;
            case PORT_B:
                if(DIO_strPinCfg[i].DIO_PinDirection == DIO_DIR_OUTPUT){
                    SET_BIT(DDRB, Loc_u8PinNumber);
                }else{
                    CLR_BIT(DDRB, Loc_u8PinNumber);
                    if(DIO_strPinCfg[i].DIO_InputStatus == DIO_INPUT_PULL_UP)
                        SET_BIT(PORTB, Loc_u8PinNumber);
                }
				Loc_enuErrorState = DIO_enuOK;
                break;
            case PORT_C:
                if(DIO_strPinCfg[i].DIO_PinDirection == DIO_DIR_OUTPUT){
                    SET_BIT(DDRC, Loc_u8PinNumber);
                }else{
                    CLR_BIT(DDRC, Loc_u8PinNumber);
                    if(DIO_strPinCfg[i].DIO_InputStatus == DIO_INPUT_PULL_UP)
                        SET_BIT(PORTC, Loc_u8PinNumber);
                }
				Loc_enuErrorState = DIO_enuOK;
                break;
            case PORT_D:
                if(DIO_strPinCfg[i].DIO_PinDirection == DIO_DIR_OUTPUT){
                    SET_BIT(DDRD, Loc_u8PinNumber);
                }else{
                    CLR_BIT(DDRD, Loc_u8PinNumber);
                    if(DIO_strPinCfg[i].DIO_InputStatus == DIO_INPUT_PULL_UP)
                        SET_BIT(PORTD, Loc_u8PinNumber);
                }
				Loc_enuErrorState = DIO_enuOK;
                break;
            default:
                Loc_enuErrorState = DIO_enuNotOK;
        }
    }
	return Loc_enuErrorState;
}
DIO_tenuErrorStatus DIO_enuSetPin(DIO_enuPins_t cpy_u8PinNumber){
    if(cpy_u8PinNumber >= 0 && cpy_u8PinNumber < DIO_enuNumberOfPins){
        u8 Loc_u8Port = cpy_u8PinNumber / 8;
        u8 Loc_u8PinNumber = cpy_u8PinNumber % 8;
        switch (Loc_u8Port)
        {
            case PORT_A:
                SET_BIT(PORTA, Loc_u8PinNumber);
                return DIO_enuOK;
            case PORT_B:
                SET_BIT(PORTB, Loc_u8PinNumber);
                return DIO_enuOK;
            case PORT_C:
                SET_BIT(PORTC, Loc_u8PinNumber);
                return DIO_enuOK;
            case PORT_D:
                SET_BIT(PORTD, Loc_u8PinNumber);
                return DIO_enuOK;
        }
    }
    return DIO_enuNotOK;
}
DIO_tenuErrorStatus DIO_enuClearPin(DIO_enuPins_t cpy_u8PinNumber){
    if(cpy_u8PinNumber >= 0 && cpy_u8PinNumber < DIO_enuNumberOfPins){
        u8 Loc_u8Port = cpy_u8PinNumber / 8;
        u8 Loc_u8PinNumber = cpy_u8PinNumber % 8;
        switch (Loc_u8Port)
        {
            case PORT_A:
                CLR_BIT(PORTA, Loc_u8PinNumber);
                return DIO_enuOK;
            case PORT_B:
                CLR_BIT(PORTB, Loc_u8PinNumber);
                return DIO_enuOK;
            case PORT_C:
                CLR_BIT(PORTC, Loc_u8PinNumber);
                return DIO_enuOK;
            case PORT_D:
                CLR_BIT(PORTD, Loc_u8PinNumber);
                return DIO_enuOK;
        }
    }
    return DIO_enuNotOK;
}
DIO_tenuErrorStatus DIO_enuGetPin(DIO_enuPins_t cpy_u8PinNumber, u8* add_pu8PinValue){
    if(cpy_u8PinNumber >= 0 && cpy_u8PinNumber < DIO_enuNumberOfPins){
        u8 Loc_u8Port = cpy_u8PinNumber / 8;
        u8 Loc_u8PinNumber = cpy_u8PinNumber % 8;
        switch (Loc_u8Port)
        {
            case PORT_A:
                *add_pu8PinValue = GET_BIT(PINA, Loc_u8PinNumber);
                return DIO_enuOK;
            case PORT_B:
                *add_pu8PinValue = GET_BIT(PINB, Loc_u8PinNumber);
                return DIO_enuOK;
            case PORT_C:
                *add_pu8PinValue = GET_BIT(PINC, Loc_u8PinNumber);
                return DIO_enuOK;
            case PORT_D:
                *add_pu8PinValue = GET_BIT(PIND, Loc_u8PinNumber);
                return DIO_enuOK;
        }
    }
    return DIO_enuNotOK;
}