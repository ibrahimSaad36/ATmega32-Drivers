/*******************************************************************
*   File name:    UART_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations to deal with UART peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef UART_CFG_H
#define UART_CFG_H

#include "../../Lib/Std_types.h"

/* Transmit or recieve */
#define UART_TX             0x9
#define UART_RX             0x10
#define UART_TXRX           0x11

#define UART_MODE           UART_TXRX

/* Stop Bits */
#define TWO_STOP_BITS       0x12
#define ONE_STOP_BITS       0x13

#define STOP_BITS_NUMBER    TWO_STOP_BITS

/* Parity Check */
#define NO_PARITY           0x14
#define EVEN_PARITY         0x15
#define ODD_PARITY          0x16

#define PARITY_CHECK        NO_PARITY

/* Baud Rate */
/* Supported baud rates are:
        * 2400
        * 4800
        * 9600      (Recommended, 0.2% error when Fosc is 16 MHZ)
        * 14400
        * 19200
        * 28800
        * 38400
        * 57600
        * 76800
        * 115200
        * 230400
        * 250000
*/
#define BAUD_RATE          9600UL
#define FOSC               16000000UL     /* Used in calculations, the clock of the cpu */ 

#endif
