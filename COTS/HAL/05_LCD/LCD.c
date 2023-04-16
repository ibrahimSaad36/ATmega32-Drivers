/*******************************************************************
*   File name:    LCD.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definition needed deal with LCD HAL driver
                  for ATmega32A/ATmega32/ATmega16
*   Version: v1.0
*******************************************************************/

#include "../../Lib/Bit_math.h"
#include "LCD_Prv.h"
#include "LCD_Cfg.h"
#include "LCD.h"

static u8 LCD_u8StrLength(pu8 add_pu8String)
{
    u8 Loc_u8StrLength;
    if(add_pu8String == NULL)
    {
        Loc_u8StrLength = -1;
    }
    else
    {
        Loc_u8StrLength = 0;
        while (add_pu8String[Loc_u8StrLength] != '\0')
        {
            Loc_u8StrLength++;
        }
    }
    return Loc_u8StrLength;
}

static LCD_tenuErrorStatus LCD_enuWriteCmd(u8 cpy_u8Cmd)
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuNotOk;
    // select command register
    DIO_enuClearPin(LCD_RS);
    // write operation
    DIO_enuClearPin(LCD_RW);
    // send command
    if(LCD_MODE == LCD_8BIT)
    {
        switch (LCD_DATA_LINES)
        {
            case PORT_A:
                ASSIGN_REG(PORTA, cpy_u8Cmd);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_B:
                ASSIGN_REG(PORTB, cpy_u8Cmd);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_C:
                ASSIGN_REG(PORTC, cpy_u8Cmd);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_D:
                ASSIGN_REG(PORTD, cpy_u8Cmd);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            default:
                Loc_enuErrorStatus = LCD_enuNotOk;
        }
    }
    else if(LCD_MODE == LCD_4BIT)
    {
        switch (LCD_DATA_LINES)
        {
            case PORT_A:
                ASSIGN_HIG_NIB(PORTA, cpy_u8Cmd);
                // enable
                DIO_enuSetPin(LCD_EN);
                //small delay
                _delay_ms(2);
                DIO_enuClearPin(LCD_EN);
                _delay_ms(2);
                ASSIGN_LOW_NIB(PORTA, cpy_u8Cmd);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_B:
                ASSIGN_HIG_NIB(PORTB, cpy_u8Cmd);
                DIO_enuSetPin(LCD_EN);
                _delay_ms(2);
                DIO_enuClearPin(LCD_EN);
                _delay_ms(2);
                ASSIGN_LOW_NIB(PORTB, cpy_u8Cmd);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_C:
                ASSIGN_HIG_NIB(PORTC, cpy_u8Cmd);
                DIO_enuSetPin(LCD_EN);
                _delay_ms(2);
                DIO_enuClearPin(LCD_EN);
                _delay_ms(2);
                ASSIGN_LOW_NIB(PORTC, cpy_u8Cmd);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_D:
				PORTD = (PORTD & 0x0F) | (cpy_u8Cmd & 0xF0);
                DIO_enuSetPin(LCD_EN);
                _delay_ms(2);
                DIO_enuClearPin(LCD_EN);
                _delay_ms(2);
				PORTD = (PORTD & 0x0F) | (cpy_u8Cmd << 4);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            default:
                Loc_enuErrorStatus = LCD_enuNotOk;
        }
    }
    if(Loc_enuErrorStatus == LCD_enuOk)
    {
        // enable
        DIO_enuSetPin(LCD_EN);
        //small delay
        _delay_ms(2);
        DIO_enuClearPin(LCD_EN);
        _delay_ms(2);
    }
    return Loc_enuErrorStatus;
}

static LCD_tenuErrorStatus LCD_enuWriteData(u8 cpy_u8Data)
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuNotOk;
    // select data register
    DIO_enuSetPin(LCD_RS);
    // write operation
    DIO_enuClearPin(LCD_RW);
    // send command
    if(LCD_MODE == LCD_8BIT)
    {
        switch (LCD_DATA_LINES)
        {
            case PORT_A:
                ASSIGN_REG(PORTA, cpy_u8Data);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_B:
                ASSIGN_REG(PORTB, cpy_u8Data);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_C:
                ASSIGN_REG(PORTC, cpy_u8Data);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_D:
                ASSIGN_REG(PORTD, cpy_u8Data);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            default:
                Loc_enuErrorStatus = LCD_enuNotOk;
        }
    }
    else if(LCD_MODE == LCD_4BIT)
    {
        switch (LCD_DATA_LINES)
        {
            case PORT_A:
                ASSIGN_HIG_NIB(PORTA, cpy_u8Data);
                // enable
                DIO_enuSetPin(LCD_EN);
                //small delay
                _delay_ms(2);
                DIO_enuClearPin(LCD_EN);
                _delay_ms(2);
                ASSIGN_LOW_NIB(PORTA, cpy_u8Data);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_B:
                ASSIGN_HIG_NIB(PORTB, cpy_u8Data);
                DIO_enuSetPin(LCD_EN);
                _delay_ms(2);
                DIO_enuClearPin(LCD_EN);
                _delay_ms(2);
                ASSIGN_LOW_NIB(PORTB, cpy_u8Data);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_C:
                ASSIGN_HIG_NIB(PORTC, cpy_u8Data);
                DIO_enuSetPin(LCD_EN);
                _delay_ms(2);
                DIO_enuClearPin(LCD_EN);
                _delay_ms(2);
                ASSIGN_LOW_NIB(PORTC, cpy_u8Data);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            case PORT_D:
				PORTD = (PORTD & 0x0F) | (cpy_u8Data & 0xF0);
                DIO_enuSetPin(LCD_EN);
                _delay_ms(2);
                DIO_enuClearPin(LCD_EN);
                _delay_ms(2);
                PORTD = (PORTD & 0x0F) | (cpy_u8Data << 4);
                Loc_enuErrorStatus = LCD_enuOk;
                break;
            default:
                Loc_enuErrorStatus = LCD_enuNotOk;
        }
    }
    if(Loc_enuErrorStatus == LCD_enuOk)
    {
        // enable
        DIO_enuSetPin(LCD_EN);
        //small delay
        _delay_ms(2);
        DIO_enuClearPin(LCD_EN);
        _delay_ms(2);
    }
    return Loc_enuErrorStatus;
}

LCD_tenuErrorStatus LCD_enuInit(void)
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuNotOk;
    #if (LCD_MODE == LCD_4BIT)
        Loc_enuErrorStatus = LCD_enuWriteCmd(LCD_CMD_4BITS_2LINE);
    #elif (LCD_MODE == LCD_8BIT)
        Loc_enuErrorStatus = LCD_enuWriteCmd(LCD_CMD_8BITS_2LINE);
    #else
        Loc_enuErrorStatus = LCD_enuErrorInInitConfig;
    #endif

    #if (LCD_DISP_INIT == LCD_DISP_ON)
        Loc_enuErrorStatus = LCD_enuWriteCmd(LCD_CMD_DISP_ON);
    #elif (LCD_DISP_INIT == LCD_DISP_OFF)
        Loc_enuErrorStatus = LCD_enuWriteCmd(LCD_CMD_DISP_OFF);
    #else
        Loc_enuErrorStatus = LCD_enuErrorInInitConfig;
    #endif

    #if (LCD_CURS_MODE == LCD_CURS_BLINK)
        Loc_enuErrorStatus = LCD_enuWriteCmd(LCD_CMD_CURS_BLI);
    #elif (LCD_CURS_MODE == LCD_CURS_FIXED)
        Loc_enuErrorStatus = LCD_enuWriteCmd(LCD_CMD_CURS_FIX);
    #else
        Loc_enuErrorStatus = LCD_enuErrorInInitConfig;
    #endif

    // clear screen
    Loc_enuErrorStatus = LCD_enuWriteCmd(LCD_CMD_CLR_SCR);
    // auto increment cursor
    Loc_enuErrorStatus = LCD_enuWriteCmd(LCD_CMD_CURS_AUTO);

    return Loc_enuErrorStatus;
}

LCD_tenuErrorStatus LCD_enuWriteCommand(u8 cpy_u8Cmd)
{
    return LCD_enuWriteCmd(cpy_u8Cmd);
}

LCD_tenuErrorStatus LCD_enuWriteChar(u8 cpy_u8Char)
{
    return LCD_enuWriteData(cpy_u8Char);
}

LCD_tenuErrorStatus LCD_enuWriteString(pu8 add_pu8String)
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuNotOk;
    u8 Loc_u8Iterator;
    for (Loc_u8Iterator = 0; Loc_u8Iterator < LCD_u8StrLength(add_pu8String); Loc_u8Iterator++)
    {
        Loc_enuErrorStatus = LCD_enuWriteData(add_pu8String[Loc_u8Iterator]);
    }
    return Loc_enuErrorStatus;
}

LCD_tenuErrorStatus LCD_enuClearScreen(void)
{
    return LCD_enuWriteCommand(LCD_CMD_CLR_SCR);
}

LCD_tenuErrorStatus LCD_enuGoToXY(u8 cpy_u8X, u8 cpy_u8Y)
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuNotOk;
    if((cpy_u8X == 0 || cpy_u8X == 1) && (cpy_u8Y >=0 && cpy_u8Y <= 15))
    {
        if(cpy_u8X == 0)
        {
            LCD_enuWriteCmd(128 + cpy_u8Y);
        }
        else
        {
            LCD_enuWriteCmd(128 + 0x40 + cpy_u8Y);
        }
        Loc_enuErrorStatus = LCD_enuOk;
    }
    else
    {
        Loc_enuErrorStatus = LCD_enuInvalidLocation;
    }
    return Loc_enuErrorStatus;
}

LCD_tenuErrorStatus LCD_enuDisplayOn(void)
{
    return LCD_enuWriteCmd(LCD_CMD_DISP_ON);
}

LCD_tenuErrorStatus LCD_enuDisplayOff(void)
{
    return LCD_enuWriteCmd(LCD_CMD_DISP_OFF);
}

LCD_tenuErrorStatus LCD_enuWriteSpecialChar(pu8 cpy_u8Pattern, u8 cpy_u8Block, u8 cpy_u8X, u8 cpy_u8Y)
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuNotOk;
    u8 Loc_u8Add = cpy_u8Block * 8;
    Loc_enuErrorStatus = LCD_enuWriteCmd(Loc_u8Add + 64);
    if(Loc_enuErrorStatus == LCD_enuOk)
    {
        u8 Loc_u8Iterator;
        for (Loc_u8Iterator = 0; Loc_u8Iterator < 8; Loc_u8Iterator++)
        {
            Loc_enuErrorStatus = LCD_enuWriteData(cpy_u8Pattern[Loc_u8Iterator]);
        }
        LCD_enuGoToXY(cpy_u8X, cpy_u8Y);
        LCD_enuWriteData(cpy_u8Block);
    }
    return Loc_enuErrorStatus;
}

LCD_tenuErrorStatus LCD_enuWrtieNumber(s16 cpy_s16Num)
{
    LCD_tenuErrorStatus Loc_enuErrorStatus = LCD_enuNotOk;
    u8 Loc_arrU8Digits[5];
    s8 Loc_s8Iterator = 0;
    s8 Loc_s8Counter = 0;
    if(cpy_s16Num == 0)
	{
		LCD_enuWriteData('0');
	}
	else
	{
		if(cpy_s16Num < 0)
		{
			Loc_enuErrorStatus = LCD_enuWriteData('-');
			cpy_s16Num *= -1;
		}
		while (cpy_s16Num != 0)
		{
			Loc_arrU8Digits[Loc_s8Iterator] = (u8) cpy_s16Num % 10;
			cpy_s16Num /= 10;
			Loc_s8Iterator++;
			Loc_s8Counter++;
		}
		for (Loc_s8Iterator = Loc_s8Counter - 1; Loc_s8Iterator >= 0; Loc_s8Iterator--)
		{
			Loc_enuErrorStatus = LCD_enuWriteData('0' + Loc_arrU8Digits[Loc_s8Iterator]);
		}
	}
    return Loc_enuErrorStatus;
}