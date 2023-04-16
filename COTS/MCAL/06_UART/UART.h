/*******************************************************************
*   File name:    UART.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declrations to deal with UART peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef UART_H
#define UART_H

#include "UART_Cfg.h"

typedef void (*UART_RXCallBack_t)(u8 uartData, u8 uartErrorStatus);
typedef void (*UART_TXCallBack_t)(void);

typedef enum
{
    UART_enuNotOk = 0,
    UART_enuOk,
    UART_enuNullPointer,
    UART_enuTimeOut,
    UART_enuFrameError,
    UART_enuDataOverRun,
    UART_enuParityError,
    UART_enuRXBusy,
    UART_enuTXBusy,
}UART_enuErrorStatus_t;

void UART_vidInit(void);
UART_enuErrorStatus_t UART_enuRecieveByteSync(pu8 add_pu8Byte);
UART_enuErrorStatus_t UART_enuTransmitByteSync(u8 cpy_u8Byte);
UART_enuErrorStatus_t UART_enuRecieveByteAsync(UART_RXCallBack_t add_pfRxCallBack);
UART_enuErrorStatus_t UART_enuTransmitByteAsync(u8 cpy_u8Byte, UART_TXCallBack_t add_pfTxCallBack);

#endif
