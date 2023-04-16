/*******************************************************************
*   File name:    LED.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs prototypes to deal with LED HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#ifndef LED_H
#define LED_H

#include "LED_Cfg.h"

typedef enum
{
    LED_enuNotOk = 0,
    LED_enuOk,
    LED_enuInvalidLedNo,
    LED_enuUnknownMode,
    LED_enuUnknownInitialState,
}LED_enuErrorStatus_t;


/**********************************************************
    Description:       This function used to turn on of off all LEDs in ledConfigArr
                       according to initialState for each LED.
                       (turned on if initialState == LED_ON), (turned off if initialState == LED_OFF)
    Input parameters:  void (no inputs expected)
    Return:            LED_enuErrorStatus_t with the following values:
                            * LED_enuUnknownMode: if mode of LED not LED_enuModeForward or LED_enuModeReverse
                            * LED_enuUnknownInitialState: if initialState of LED not LED_ON or LED_OFF
                            * DIO_enuNotOk: in case of error ocurred when setting or clearing pin of LED
                            * DIO_enuInvalidPinNo: if pin of LED is invalid (accpeted pins are from DIO_enuPin0 to DIO_enuPin31)
                            * DIO_enuOk: if LED turned on or off correctly and no errors occured
***********************************************************/
LED_enuErrorStatus_t LED_enuInit(void);


/**********************************************************
    Description:       This function used to turn on the LED of the name passed to function
                        (this name must be in ledsInfo_t in LED_Cfg.h file)
    Input parameters:  expected name of LED as written in ledsInfo_t in LED_Cfg.h file
    Return:            LED_enuErrorStatus_t with the following values:
                            * LED_enuUnknownMode: if mode of LED not LED_enuModeForward or LED_enuModeReverse
                            * LED_enuUnknownInitialState: if initialState of LED not LED_ON or LED_OFF
                            * DIO_enuInvalidPinNo: if pin of LED is invalid (accpeted pins are from DIO_enuPin0 to DIO_enuPin31)
                            * DIO_enuNotOk: in case of error ocurred when setting or clearing pin of LED
                            * DIO_enuOk: if LED turned on or off correctly and no errors occured     
***********************************************************/
LED_enuErrorStatus_t LED_enuSetLedOn(u8 cpy_u8LedName);


/**********************************************************
    Description:       This function used to turn on the LED of the name passed to function
                        (this name must be in ledsInfo_t in LED_Cfg.h file)
    Input parameters:  expected name of LED as written in ledsInfo_t in LED_Cfg.h file
    Return:            LED_enuErrorStatus_t with the following values:
                            * LED_enuUnknownMode: if mode of LED not LED_enuModeForward or LED_enuModeReverse
                            * LED_enuUnknownInitialState: if initialState of LED not LED_ON or LED_OFF
                            * DIO_enuNotOk: in case of error ocurred when setting or clearing pin of LED
                            * DIO_enuInvalidPinNo: if pin of LED is invalid (accpeted pins are from DIO_enuPin0 to DIO_enuPin31)
                            * DIO_enuOk: if LED turned on or off correctly and no errors occured             
***********************************************************/
LED_enuErrorStatus_t LED_enuSetLedOff(u8 cpy_u8LedName);

#endif
