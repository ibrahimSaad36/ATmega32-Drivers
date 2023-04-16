/*******************************************************************
*   File name:    SPI.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with SPI peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#include "SPI_Prv.h"
#include "SPI.h"

#define SPI_TIMOUT              60000UL
#define DUMMY_DATA              0x33

#define SS_PIN                  DIO_enuPin12

#define MSK_CHECK_VALID_POL     0xF0
#define MSK_VALID_POL           0xD0

#define MSK_CHECK_VALID_MODE    0xF0
#define MSK_VALID_MODE          0xE0

#define MSK_CHECK_VALID_PHASE   0xF0
#define MSK_VALID_PHASE         0xB0

#define MSK_CHECK_VALID_DORD    0xF0
#define MSK_VALID_DORD          0xC0   

#define MSK_CHECK_VALID_DRATE   0b11100000
#define MSK_VALID_DRATE         0b11100000
#define MSK_CLR_CHECK_DRATE     0b00011111

#define MSK_CLR_SPR             0b11111100

#define MSK_SPIF                0b10000000
#define MSK_WCOL                0b01000000

struct SPIReg_t
{
    u8 SPI_SPCR;
    u8 SPI_SPSR;
    u8 SPI_SPDR;
};

static volatile struct SPIReg_t* spiRegs = (volatile struct SPIReg_t* const) SPI_BASE_ADD;

SPI_enuErrorStatus_t SPI_enuInit(const SPI_Cfg_t* add_pstrConfig)
{
    SPI_enuErrorStatus_t Loc_enuErrorStatus = SPI_enuNotOk;
    if((add_pstrConfig->mode & MSK_CHECK_VALID_MODE) == MSK_VALID_MODE)
    {
        if(add_pstrConfig->mode == mode_Master)
        {
            spiRegs->SPI_SPCR |= (1 << SPCR_MSTR);
        }
        else
        {
            spiRegs->SPI_SPCR &= ~(1 << SPCR_MSTR);
        }
        if((add_pstrConfig->polarity & MSK_CHECK_VALID_POL) == MSK_VALID_POL)
        {
            if(add_pstrConfig->polarity == polarity_FallingRising)
            {
                spiRegs->SPI_SPCR |= (1 << SPCR_CPOL);
            }
            else
            {
                spiRegs->SPI_SPCR &= ~(1 << SPCR_CPOL);
            }
        }
        else
        {
            Loc_enuErrorStatus = SPI_enuInvalidPolarity;
        }
        if((add_pstrConfig->phase & MSK_CHECK_VALID_PHASE) == MSK_VALID_PHASE)
        {
            if(add_pstrConfig->phase == phase_SampleSetup)
            {
                spiRegs->SPI_SPCR &= ~(1 << SPCR_CPHA);
            }
            else
            {
                spiRegs->SPI_SPCR |= (1 << SPCR_CPHA);
            }
        }
        else
        {
            Loc_enuErrorStatus = SPI_enuInvalidPhase;
        }
        if((add_pstrConfig->dataOrder & MSK_CHECK_VALID_DORD) == MSK_VALID_DORD)
        {
            if(add_pstrConfig->dataOrder == dataOrder_LSBFirst)
            {
                spiRegs->SPI_SPCR |= (1 << SPCR_DORD);
            }
            else
            {
                spiRegs->SPI_SPCR &= ~(1 << SPCR_DORD);
            }
        }
        else
        {
            Loc_enuErrorStatus = SPI_enuInvalidDataOrder;
        }
        if((add_pstrConfig->dataRate & MSK_CHECK_VALID_DRATE) == MSK_VALID_DRATE)
        {
            u8 Loc_u8Temp;
            u8 Loc_u8Drate = add_pstrConfig->dataRate & MSK_CLR_CHECK_DRATE;
            if(add_pstrConfig->dataRate == SPI_enuDataRate_fclk_2 || add_pstrConfig->dataRate == SPI_enuDataRate_fclk_32
                || add_pstrConfig->dataRate == SPI_enuDataRate_fclk_16)
            {
                spiRegs->SPI_SPSR |= (1 << SPSR_SPI2X);
            }
            Loc_u8Temp = spiRegs->SPI_SPCR;
            Loc_u8Temp &= MSK_CLR_SPR;
            Loc_u8Temp |= Loc_u8Drate;
            spiRegs->SPI_SPCR = Loc_u8Temp;
            Loc_enuErrorStatus = SPI_enuOk;
        }
        else
        {
            Loc_enuErrorStatus = SPI_enuInvalidDataRate;
        }
    }
    else
    {
        Loc_enuErrorStatus = SPI_enuInvalidMode;
    }
    return Loc_enuErrorStatus;
}

void SPI_vidEnable(void)
{
    spiRegs->SPI_SPCR |= (1 << SPCR_SPE);
    spiRegs->SPI_SPCR |= (1 << SPCR_SPIE);
}

void SPI_vidDisable(void)
{
    spiRegs->SPI_SPCR &= ~(1 << SPCR_SPIE);
}

SPI_enuErrorStatus_t SPI_enuMasterSendByteSync(u8 cpy_u8Data)
{
    u16 Loc_u16Timeout = SPI_TIMOUT;
    SPI_enuErrorStatus_t Loc_enuErrorStatus = SPI_enuNotOk;
    DIO_enuClearPin(SS_PIN);
    spiRegs->SPI_SPDR = cpy_u8Data;
    while (!(spiRegs->SPI_SPSR & MSK_SPIF) && Loc_u16Timeout > 0)
    {
        Loc_u16Timeout--;
    }
    if(spiRegs->SPI_SPSR & MSK_SPIF)
    {
        spiRegs->SPI_SPSR &= ~(1 << SPSR_SPIF);
        Loc_enuErrorStatus = SPI_enuOk;
    }
    else
    {
        Loc_enuErrorStatus = SPI_enuTimeout;
    }
    return Loc_enuErrorStatus;
}

SPI_enuErrorStatus_t SPI_enuSlaveRecieveByteSync(pu8 add_pu8Data)
{
    SPI_enuErrorStatus_t Loc_enuErrorStatus = SPI_enuNotOk;
    if(add_pu8Data)
    {
        u16 Loc_u16Timeout = SPI_TIMOUT;
        spiRegs->SPI_SPDR = DUMMY_DATA;
        while (!(spiRegs->SPI_SPSR & MSK_SPIF) && Loc_u16Timeout > 0)
        {
            Loc_u16Timeout--;
        }
        if(spiRegs->SPI_SPSR & MSK_SPIF)
        {
            spiRegs->SPI_SPSR &= ~(1 << SPSR_SPIF);
            *add_pu8Data = spiRegs->SPI_SPDR;
            Loc_enuErrorStatus = SPI_enuOk;
        }
        else
        {
            Loc_enuErrorStatus = SPI_enuTimeout;
        }
    }
    else
    {
        Loc_enuErrorStatus = SPI_enuNullPointer;
    }
    return Loc_enuErrorStatus;
}

/* SPI, STC */
void __vector_12 (void) __attribute__ ((signal));
void __vector_12 (void)
{
}
