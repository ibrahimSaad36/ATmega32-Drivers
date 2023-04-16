/*******************************************************************
*   File name:    UART.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with UART peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#include "UART_Prv.h"
#include "UART.h"

#define UART_TIME_OUT           600000UL

#define MSK_SELECT_UCSRC        0b10000000
#define CALC_UBRR(fosc, baud)   ((fosc / (16 * baud)) - 1)
/* UBRR = ((fosc) / (16 * BAUD)) - 1 */

#define MSK_CLR_PARITY_BITS     0b11001111
#define MSK_NO_PARITY           0
#define MSK_EVEN_PARITY         0b00100000
#define MSK_ODD_PARITY          0b00110000

#define MSK_RXC                 0b10000000
#define MSK_TXC                 0b01000000
#define MSK_UDRE                0b00100000
#define MSK_FE                  0b00010000
#define MSK_DOR                 0b00001000
#define MSK_PE                  0b00000100


static u8 uart_u8RxFlag, uart_u8TxFlag;
static UART_RXCallBack_t uart_pfRxCallBack = NULL;
static UART_TXCallBack_t uart_pfTxCallBack = NULL;

void UART_vidInit(void)
{
    u8 Loc_u8Temp;
    u16 Loc_u16UBRRVal;

    UCSRC &= ~(1 << UCSRC_UMSEL) | MSK_SELECT_UCSRC;

    #if UART_MODE == UART_TX
        UCSRB |= (1 << UCSRB_TXEN);
        UCSRB |= (1 << UCSRB_TXCIE);
    #elif UART_MODE == UART_RX
        UCSRB |= (1 << UCSRB_RXEN);
        UCSRB |= (1 << UCSRB_RXCIE);
    #elif UART_MODE == UART_TXRX
        UCSRB |= (1 << UCSRB_TXEN);
        UCSRB |= (1 << UCSRB_RXEN);
        UCSRB |= (1 << UCSRB_TXCIE);
        UCSRB |= (1 << UCSRB_RXCIE);
    #else
        #error "Error in selected UART mode, pleas select a valid option"
    #endif

    #if STOP_BITS_NUMBER == ONE_STOP_BITS
        UCSRC &= ~(1 << UCSRC_USBS) | MSK_SELECT_UCSRC;
    #elif STOP_BITS_NUMBER == TWO_STOP_BITS
        UCSRC |= (1 << UCSRC_USBS) | MSK_SELECT_UCSRC;
    #else
        #error "Error in selected stop bits, pleas select a valid option"
    #endif

    Loc_u8Temp = UCSRC;
    Loc_u8Temp &= MSK_CLR_PARITY_BITS;
    #if PARITY_CHECK == NO_PARITY
        Loc_u8Temp |= MSK_NO_PARITY;
        UCSRC = Loc_u8Temp | MSK_SELECT_UCSRC;
    #elif PARITY_CHECK == EVEN_PARITY
        Loc_u8Temp |= MSK_EVEN_PARITY;
        UCSRC = Loc_u8Temp | MSK_SELECT_UCSRC;
    #elif PARITY_CHECK == ODD_PARITY
        Loc_u8Temp |= MSK_ODD_PARITY;
        UCSRC = Loc_u8Temp | MSK_SELECT_UCSRC;
    #else
        #error "Error in selected parity option, pleas select a valid option"
    #endif

    /* Data size is 8 bits */
    Loc_u8Temp = UCSRC;
    UCSRB &= ~(1 << UCSRB_UCSZ2);
    Loc_u8Temp |= (1 << UCSRC_UCSZ1);
    Loc_u8Temp |= (1 << UCSRC_UCSZ0);
    UCSRC = Loc_u8Temp | MSK_SELECT_UCSRC;

    Loc_u16UBRRVal = CALC_UBRR(FOSC, BAUD_RATE);
    UBRRH = ((u8) Loc_u16UBRRVal >> 8) & ~MSK_SELECT_UCSRC;
    UBRRL = (u8) Loc_u16UBRRVal;
}

UART_enuErrorStatus_t UART_enuRecieveByteSync(pu8 add_pu8Byte)
{
    UART_enuErrorStatus_t Loc_enuErrorStatus = UART_enuNotOk;
    if(add_pu8Byte == NULL)
    {
        Loc_enuErrorStatus = UART_enuNullPointer;
    }
    else
    {
        u16 Loc_u16Timeout = UART_TIME_OUT;
        while (!(MSK_RXC & UCSRA) && (Loc_u16Timeout > 0))
        {
            Loc_u16Timeout--;
        }
        if(MSK_RXC & UCSRA)
        {
            if(MSK_DOR & UCSRA)
            {
                Loc_enuErrorStatus = UART_enuDataOverRun;
            }
            else if(MSK_FE & UCSRA)
            {
                Loc_enuErrorStatus = UART_enuFrameError;
            }
            else if(MSK_PE & UCSRA)
            {
                Loc_enuErrorStatus = UART_enuParityError;
            }
            else
            {
                *add_pu8Byte = UDR;
                Loc_enuErrorStatus = UART_enuOk;
            }
        }
        else
        {
            Loc_enuErrorStatus = UART_enuTimeOut;
        }
    }
    return Loc_enuErrorStatus;
}

UART_enuErrorStatus_t UART_enuTransmitByteSync(u8 cpy_u8Byte)
{
    UART_enuErrorStatus_t Loc_enuErrorStatus = UART_enuNotOk;
    u16 Loc_u16Timeout = UART_TIME_OUT;
    while (!(MSK_UDRE & UCSRA) && (Loc_u16Timeout > 0))
    {
        Loc_u16Timeout--;
    }
    if(MSK_UDRE & UCSRA)
    {
        UDR = cpy_u8Byte;
        Loc_u16Timeout = UART_TIME_OUT;
        while (!(MSK_TXC & UCSRA) && (Loc_u16Timeout > 0))
        {
            Loc_u16Timeout--;
        }
        if(MSK_TXC & UCSRA)
        {
            Loc_enuErrorStatus = UART_enuOk;
        }
        else
        {
            Loc_enuErrorStatus = UART_enuTimeOut;
        }
    }
    return Loc_enuErrorStatus;
}

UART_enuErrorStatus_t UART_enuRecieveByteAsync(UART_RXCallBack_t add_pfRxCallBack)
{
    UART_enuErrorStatus_t Loc_enuErrorStatus = UART_enuNotOk;
    if(add_pfRxCallBack == NULL)
    {
        Loc_enuErrorStatus = UART_enuNullPointer;
    }
    else
    {
        if(uart_u8RxFlag)
        {
            Loc_enuErrorStatus = UART_enuRXBusy;
        }
        else
        {
            uart_pfRxCallBack = add_pfRxCallBack;
            uart_u8RxFlag = 1;
            Loc_enuErrorStatus = UART_enuOk;
        }
    }
    return Loc_enuErrorStatus;
}

UART_enuErrorStatus_t UART_enuTransmitByteAsync(u8 cpy_u8Byte, UART_TXCallBack_t add_pfTxCallBack)
{
    UART_enuErrorStatus_t Loc_enuErrorStatus = UART_enuNotOk;
    if(add_pfTxCallBack == NULL)
    {
        Loc_enuErrorStatus = UART_enuNullPointer;
    }
    else
    {
        if(uart_u8TxFlag)
        {
            Loc_enuErrorStatus = UART_enuRXBusy;
        }
        else
        {
            UDR = cpy_u8Byte;
            uart_pfTxCallBack = add_pfTxCallBack;
            uart_u8TxFlag = 1;
            Loc_enuErrorStatus = UART_enuOk;
        }
    }
    return Loc_enuErrorStatus;
}

/*  USART, RXC */
void __vector_13 (void) __attribute__ ((signal));
void __vector_13 (void)
{
    if(uart_u8RxFlag)
    {
        UART_enuErrorStatus_t Loc_enuErrorStatus = UART_enuNotOk;
        if(MSK_DOR & UCSRA)
        {
            Loc_enuErrorStatus = UART_enuDataOverRun;
        }
        else if(MSK_FE & UCSRA)
        {
            Loc_enuErrorStatus = UART_enuFrameError;
        }
        else if(MSK_PE & UCSRA)
        {
            Loc_enuErrorStatus = UART_enuParityError;
        }
        else
        {
            Loc_enuErrorStatus = UART_enuOk;
            uart_u8RxFlag = 0;
            uart_pfRxCallBack(UDR, Loc_enuErrorStatus);
        }
    }
}

/*  USART, TXC */
void __vector_15 (void) __attribute__ ((signal));
void __vector_15 (void)
{
    if(uart_u8TxFlag)
    {
        uart_u8TxFlag = 0;
        uart_pfTxCallBack();
    }
}
