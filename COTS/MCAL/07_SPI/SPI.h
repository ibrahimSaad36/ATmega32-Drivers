/*******************************************************************
*   File name:    SPI.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declrations to deal with SPI peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef SPI_H
#define SPI_H

#include "../../MCAL/00_DIO/DIO.h"
#include "SPI_Cfg.h"

typedef enum
{
    SPI_enuNotOk = 0,
    SPI_enuOk,
    SPI_enuNullPointer,
    SPI_enuInvalidMode,
    SPI_enuInvalidPolarity,
    SPI_enuInvalidPhase,
    SPI_enuInvalidDataRate,
    SPI_enuInvalidDataOrder,
    SPI_enuWriteCollision,
    SPI_enuTimeout,
}SPI_enuErrorStatus_t;

SPI_enuErrorStatus_t SPI_enuInit(const SPI_Cfg_t* add_pstrConfig);
void SPI_vidEnable(void);
void SPI_vidDisable(void);
SPI_enuErrorStatus_t SPI_enuMasterSendByteSync(u8 cpy_u8Data);
SPI_enuErrorStatus_t SPI_enuSlaveRecieveByteSync(pu8 add_pu8Data);

#endif
