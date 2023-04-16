/*******************************************************************
*   File name:    SPI_Cfg.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all configurations to deal with SPI peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef SPI_CFG_H
#define SPI_CFG_H

#include "../../Lib/Std_types.h"

#define polarity_RisingFalling      0xD2        /* leading is rising edge, trailing is falling edge */ 
#define polarity_FallingRising      0xD4        /* leading is falling edge, trailing is rising edge */   

#define phase_SampleSetup           0xB6        /* leading for sampling, trailing for setup */
#define phase_SetupSample           0xB7        /* leading for setup, trailing for sampling */

#define mode_Master                 0xE1
#define mode_Slave                  0xE2

#define dataOrder_LSBFirst          0xC3
#define dataOrder_MSB_First         0xC4

typedef enum 
{
    SPI_enuDataRate_fclk_2   = 0b11100000,
    SPI_enuDataRate_fclk_4   = 0b11100000,
    SPI_enuDataRate_fclk_8   = 0b11100001,
    SPI_enuDataRate_fclk_16  = 0b11100001,
    SPI_enuDataRate_fclk_32  = 0b11100010,
    SPI_enuDataRate_fclk_64  = 0b11100010,
    SPI_enuDataRate_fclk_128 = 0b11100011,
}SPI_enuDataRate_t;

typedef struct 
{
    u8 id;      /* may be useful in case of slave */
    u8 polarity;
    u8 phase;
    SPI_enuDataRate_t dataRate;
    u8 mode;    /* msater or slave */
    u8 dataOrder;
}SPI_Cfg_t;

#endif
