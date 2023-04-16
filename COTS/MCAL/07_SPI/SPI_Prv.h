/*******************************************************************
*   File name:    SPI_Prv.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all registers required to deal with SPI peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef SPI_PRV_H
#define SPI_PRV_H

#include "../../Lib/Std_types.h"

#define SPI_BASE_ADD            0x2D

#define SPCR                    ((volatile pu8) 0x2D)
#define SPSR                    ((volatile pu8) 0x2E)
#define SPDR                    ((volatile pu8) 0x2F)

#define SPCR_SPIE               7
#define SPCR_SPE                6
#define SPCR_DORD               5
#define SPCR_MSTR               4
#define SPCR_CPOL               3
#define SPCR_CPHA               2
/* SPI CLOCK RATE: bits [1, 0] */
#define DORD_LSB_FIRST          1
#define DORD_MSB_FIRST          0
#define MSTR_MASTER             1
#define MSTR_SLAVE              0
#define CPOL_LEA_RIS_TR_FAL     0
#define CPOL_LEA_FAL_TR_RIS     1
#define CPHA_LEA_SAM_FAL_SET    0
#define CPHA_LEA_SET_FAL_SAM    1

#define SPSR_SPI2X              0
#define SPSR_SPIF               7
#define SPSR_WCOL               6

#endif
