/*******************************************************************
*   File name:    TMR0.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with timer0 peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#include "../../Lib/Bit_math.h"
#include "TMR0_Prv.h"
#include "TMR0.h"

#define TIMER0_RESOLUTION               256.0F     /* 2^n >> 2^8 = 256 */
#define TIMER0_OCR_VALUE				250U
#define TIMER0_PWM_RESOLUTION			255U

#define MSK_CLR_WGM                     0b10110111
#define MSK_CLR_COM                     0b11001111
#define MSK_CLR_CS                      0b11111000

#define MSK_TMR_MODE_NORML              MSK_CLR_WGM
#define MSK_TMR_MODE_PWM_PHASE_CORR     0b01000000
#define MSK_TMR_MODE_CTC                0b00001000
#define MSK_TMR_MODE_PWM_FAST           0b01001000

#define MSK_CMP_MATCH_NPWM_MODE_DIS     MSK_CLR_COM
#define MSK_CMP_MATCH_NPWM_MODE_TGL     0b00010000
#define MSK_CMP_MATCH_NPWM_MODE_CLR     0b00100000
#define MSK_CMP_MATCH_NPWM_MODE_SET     0b00110000

#define MSK_FPWM_MODE_DIS               MSK_CLR_COM
#define MSK_FPWM_MODE_NINV              0b00100000      /* (non-inverting) clear on compare set at BOTTOM */
#define MSK_FPWM_MODE_INV               0b00110000      /* (inverting) set on compare clear at BOOTOM */

#define MSK_PPWM_MODE_DIS               MSK_CLR_COM
#define MSK_PPWM_MODE_CUSD              0b00100000      /* Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting */
#define MSK_PPWM_MODE_SUCD              0b00110000      /* Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting */

#define MSK_CS_NO_CLK                   MSK_CLR_CS
#define MSK_CS_NO_PRESC                 0b00000001
#define MSK_CS_PER8_PRESC               0b00000010
#define MSK_CS_PER64_PRESC              0b00000011
#define MSK_CS_PER256_PRESC             0b00000100
#define MSK_CS_PER1024_PRESC            0b00000101
#define MSK_CS_EXT_T0_FALLING           0b00000110
#define MSK_CS_EXT_T0_RISING            0b00000111

static TMR0cbf_t timer0_pfCallback = NULL;
static u8 timer0_u8Mode;
static u16 timer0_u16ISRCount;
static u16 timer0_u16Preload;
static u8 timer0_u8Prescaler;

/* if flag = 0, means isrCount = one ov */
/* if flag = 1, means isrCount = ov counts */
/* if flag = 2, means preload and ov counts */
/* if flag = 3, means preload one isr */
/* if flag = 4, means ctc only one isr or multiple isrs*/
/* if flag = 5, means not configured */
static u8 timer0_u8ISRFlag = 6;

static u8 isInteger(f32 num)
{
    u16 val = (u16) num;
    return (val == num);
}

static f32 getFraction(f32 num)
{
    u16 val = (u16) num;
    return (num - val);
}

void TMR0_vidInitPreCompile(void)
{
    u8 Loc_u8Temp;
    /* mode of operation */
    Loc_u8Temp = TCCR0;
    #if TMR0_MODE == TMR0_MODE_NORMAL
        Loc_u8Temp &= MSK_TMR_MODE_NORML;
        TCCR0 = Loc_u8Temp;
        timer0_u8Mode = TMR0_MODE_NORMAL;
    #elif TMR0_MODE == TMR0_MODE_CTC
        Loc_u8Temp &= MSK_CLR_WGM;
        Loc_u8Temp &= MSK_CLR_COM;
        Loc_u8Temp |= MSK_TMR_MODE_CTC;
        timer0_u8Mode = TMR0_MODE_CTC;
        #if TMR0_CTC_MODE == TMR0_MODE_CTC_COM_DIS
            Loc_u8Temp |= MSK_CMP_MATCH_NPWM_MODE_DIS;
            TCCR0 = Loc_u8Temp;
        #elif TMR0_CTC_MODE == TMR0_MODE_CTC_COM_TGL
            Loc_u8Temp |= MSK_CMP_MATCH_NPWM_MODE_TGL;
            TCCR0 = Loc_u8Temp;
        #elif TMR0_CTC_MODE == TMR0_MODE_CTC_COM_CLR
            Loc_u8Temp |= MSK_CMP_MATCH_NPWM_MODE_CLR;
            TCCR0 = Loc_u8Temp;
        #elif TMR0_CTC_MODE == TMR0_MODE_CTC_COM_SET
            Loc_u8Temp |= MSK_CMP_MATCH_NPWM_MODE_SET;
            TCCR0 = Loc_u8Temp;
        #endif
    #elif TMR0_MODE == TMR0_MODE_FAST_PWM_DIS
        Loc_u8Temp &= MSK_CLR_WGM;
        Loc_u8Temp |= MSK_TMR_MODE_PWM_FAST;
        Loc_u8Temp &= MSK_CLR_COM;
        Loc_u8Temp |= MSK_FPWM_MODE_DIS;
        timer0_u8Mode = TMR0_MODE_FAST_PWM_DIS;
        TCCR0 = Loc_u8Temp;
    #elif TMR0_MODE == TMR0_MODE_FAST_PWM_INV
        Loc_u8Temp &= MSK_CLR_WGM;
        Loc_u8Temp |= MSK_TMR_MODE_PWM_FAST;
        Loc_u8Temp &= MSK_CLR_COM;
        Loc_u8Temp |= MSK_FPWM_MODE_INV;
        timer0_u8Mode = TMR0_MODE_FAST_PWM_INV;
        TCCR0 = Loc_u8Temp;
    #elif TMR0_MODE == TMR0_MODE_FAST_PWM_NINV
        Loc_u8Temp &= MSK_CLR_WGM;
        Loc_u8Temp |= MSK_TMR_MODE_PWM_FAST;
        Loc_u8Temp &= MSK_CLR_COM;
        Loc_u8Temp |= MSK_FPWM_MODE_NINV;
        timer0_u8Mode = TMR0_MODE_FAST_PWM_NINV;
        TCCR0 = Loc_u8Temp;
    #elif TMR0_MODE == TMR0_MODE_PCORR_PWM_DIS
        Loc_u8Temp &= MSK_CLR_WGM;
        Loc_u8Temp |= MSK_TMR_MODE_PWM_PHASE_CORR;
        Loc_u8Temp &= MSK_CLR_COM;
        Loc_u8Temp |= MSK_PPWM_MODE_DIS;
        timer0_u8Mode = TMR0_MODE_PCORR_PWM_DIS;
        TCCR0 = Loc_u8Temp;
    #elif TMR0_MODE == TMR0_MODE_PCORR_PWM_CUSD
        Loc_u8Temp &= MSK_CLR_WGM;
        Loc_u8Temp |= MSK_TMR_MODE_PWM_PHASE_CORR;
        Loc_u8Temp &= MSK_CLR_COM;
        Loc_u8Temp |= MSK_PPWM_MODE_CUSD;
        timer0_u8Mode = TMR0_MODE_PCORR_PWM_CUSD;
        TCCR0 = Loc_u8Temp;
    #elif TMR0_MODE == TMR0_MODE_PCORR_PWM_SUCD
        Loc_u8Temp &= MSK_CLR_WGM;
        Loc_u8Temp |= MSK_TMR_MODE_PWM_PHASE_CORR;
        Loc_u8Temp &= MSK_CLR_COM;
        Loc_u8Temp |= MSK_PPWM_MODE_SUCD;
        timer0_u8Mode = TMR0_MODE_PCORR_PWM_SUCD;
        TCCR0 = Loc_u8Temp;
    #endif
    /* clock source and initial state */
    #if TMR0_INIT_STATE == TMR0_INIT_STOOPED
        Loc_u8Temp = TCCR0;
        Loc_u8Temp &= MSK_CS_NO_CLK;
        TCCR0 = Loc_u8Temp;
		timer0_u8Prescaler = TMR0_CLOCK_SRC;
    #elif TMR0_INIT_STATE == TMR0_INIT_RUNNING
        Loc_u8Temp = TCCR0;
        Loc_u8Temp &= MSK_CLR_CS;
        #if TMR0_CLOCK_SRC == TMR0_NO_PRESC
            Loc_u8Temp |= MSK_CS_NO_PRESC;
            TCCR0 = Loc_u8Temp;
            timer0_u8Prescaler = MSK_CS_NO_PRESC;
        #elif TMR0_CLOCK_SRC == TMR0_PER8_PRESC
            Loc_u8Temp |= MSK_CS_PER8_PRESC;
            TCCR0 = Loc_u8Temp;
            timer0_u8Prescaler = MSK_CS_PER8_PRESC;
        #elif TMR0_CLOCK_SRC == TMR0_PER64_PRESC
            Loc_u8Temp |= MSK_CS_PER64_PRESC;
            TCCR0 = Loc_u8Temp;
            timer0_u8Prescaler = MSK_CS_PER64_PRESC;
        #elif TMR0_CLOCK_SRC == TMR0_PER256_PRESC
            Loc_u8Temp |= MSK_CS_PER256_PRESC;
            TCCR0 = Loc_u8Temp;
            timer0_u8Prescaler = MSK_CS_PER256_PRESC;
        #elif TMR0_CLOCK_SRC == TMR0_PER1024_PRESC
            Loc_u8Temp |= MSK_CS_PER1024_PRESC;
            TCCR0 = Loc_u8Temp;
            timer0_u8Prescaler = MSK_CS_PER1024_PRESC;
        #elif TMR0_CLOCK_SRC == TMR0_EXT_T0_FALLING
            Loc_u8Temp |= MSK_CS_EXT_T0_FALLING;
            TCCR0 = Loc_u8Temp;
            timer0_u8Prescaler = MSK_CS_EXT_T0_FALLING;
        #elif TMR0_CLOCK_SRC == TMR0_EXT_T0_RISING
            Loc_u8Temp |= MSK_CS_EXT_T0_RISING;
            timer0_u8Prescaler = MSK_CS_EXT_T0_RISING;
            TCCR0 = Loc_u8Temp;
        #endif
    #endif
}

void TMR0_vidInitPostCompile(TMR0Config_t cpy_strTMR0Config)
{
    u8 Loc_u8Temp = TCCR0;
    Loc_u8Temp &= MSK_CLR_WGM;
    switch (cpy_strTMR0Config.timerMode)
    {
        case TMR0_MODE_NORMAL:
            Loc_u8Temp &= MSK_TMR_MODE_NORML;
            timer0_u8Mode = TMR0_MODE_NORMAL;
            break;
        case TMR0_MODE_CTC:
            Loc_u8Temp &= MSK_CLR_COM;
            Loc_u8Temp |= MSK_TMR_MODE_CTC;
            timer0_u8Mode = TMR0_MODE_CTC;
            switch (cpy_strTMR0Config.compareMatchOutMode)
            {
                case TMR0_MODE_CTC_COM_DIS:
                    Loc_u8Temp |= MSK_CMP_MATCH_NPWM_MODE_DIS;
                    break;
                case TMR0_MODE_CTC_COM_TGL:
                    Loc_u8Temp |= MSK_CMP_MATCH_NPWM_MODE_TGL;
                    break;
                case TMR0_MODE_CTC_COM_CLR:
                    Loc_u8Temp |= MSK_CMP_MATCH_NPWM_MODE_CLR;
                    break;
                case TMR0_MODE_CTC_COM_SET:
                    Loc_u8Temp |= MSK_CMP_MATCH_NPWM_MODE_SET;
                    break;
            }
            break;
        case TMR0_MODE_FAST_PWM_DIS:
            Loc_u8Temp &= MSK_CLR_COM;
            Loc_u8Temp |= MSK_FPWM_MODE_DIS;
            timer0_u8Mode = TMR0_MODE_FAST_PWM_DIS;
            break;
        case TMR0_MODE_FAST_PWM_INV:
            Loc_u8Temp &= MSK_CLR_COM;
            Loc_u8Temp |= MSK_FPWM_MODE_INV;
            timer0_u8Mode = TMR0_MODE_FAST_PWM_INV;
            break;
        case TMR0_MODE_FAST_PWM_NINV:
            Loc_u8Temp &= MSK_CLR_COM;
            Loc_u8Temp |= MSK_FPWM_MODE_NINV;
            timer0_u8Mode = TMR0_MODE_FAST_PWM_NINV;
            break;
        case TMR0_MODE_PCORR_PWM_DIS:
            Loc_u8Temp &= MSK_CLR_COM;
            Loc_u8Temp |= MSK_PPWM_MODE_DIS;
            timer0_u8Mode = TMR0_MODE_PCORR_PWM_DIS;
            break;
        case TMR0_MODE_PCORR_PWM_CUSD:
            Loc_u8Temp &= MSK_CLR_COM;
            Loc_u8Temp |= MSK_PPWM_MODE_CUSD;
            timer0_u8Mode = TMR0_MODE_PCORR_PWM_CUSD;
            break;
        case TMR0_MODE_PCORR_PWM_SUCD:
            Loc_u8Temp &= MSK_CLR_COM;
            Loc_u8Temp |= MSK_PPWM_MODE_SUCD;
            timer0_u8Mode = TMR0_MODE_PCORR_PWM_SUCD;
            break;
    }
    Loc_u8Temp &= MSK_CLR_CS;
    switch (cpy_strTMR0Config.clockSource)
    {
        case TMR0_NO_PRESC:
            Loc_u8Temp |= MSK_CS_NO_PRESC;
			timer0_u8Prescaler = MSK_CS_NO_PRESC;
            break;
        case TMR0_PER8_PRESC:
            Loc_u8Temp |= MSK_CS_PER8_PRESC;
			timer0_u8Prescaler = MSK_CS_PER8_PRESC;
            break;
        case TMR0_PER64_PRESC:
            Loc_u8Temp |= MSK_CS_PER64_PRESC;
			timer0_u8Prescaler = MSK_CS_PER64_PRESC;
            break;
        case TMR0_PER256_PRESC:
            Loc_u8Temp |= MSK_CS_PER256_PRESC;
			timer0_u8Prescaler = MSK_CS_PER256_PRESC;
            break;
        case TMR0_PER1024_PRESC:
            Loc_u8Temp |= MSK_CS_PER1024_PRESC;
			timer0_u8Prescaler = MSK_CS_PER1024_PRESC;
            break;
        case TMR0_EXT_T0_FALLING:
            Loc_u8Temp |= MSK_CS_EXT_T0_FALLING;
			timer0_u8Prescaler = MSK_CS_EXT_T0_FALLING;
            break;
        case TMR0_EXT_T0_RISING:
            Loc_u8Temp |= MSK_CS_EXT_T0_RISING;
			timer0_u8Prescaler = MSK_CS_EXT_T0_RISING;
            break;
    }
    TCCR0 = Loc_u8Temp;
}

TMR0_enuErrorStatus_t TMR0_enuSetTickTimeMS(u16 cpy_u16TickTime, u64 cpy_u32Clock)
{
    TMR0_enuErrorStatus_t Loc_enuErrorStatus = TMR0_enuNotOk;
    if(timer0_u8Mode == TMR0_MODE_NORMAL)
    {
        f32 Loc_f32TickTime, Loc_f32OvTime, Loc_f32OvReq;
        Loc_f32TickTime = 1.0 / cpy_u32Clock;
        Loc_f32OvTime = TIMER0_RESOLUTION * Loc_f32TickTime;
        Loc_f32OvReq = (cpy_u16TickTime / 1000.0) / Loc_f32OvTime;
        if (Loc_f32OvReq == Loc_f32OvTime)
        {
            /* required only one isr */
            timer0_u8ISRFlag = 0;
        }
        else if(Loc_f32OvReq > Loc_f32OvTime)
        {
            /* required multiple isrs */
            if (isInteger(Loc_f32OvReq))
            {
                timer0_u16ISRCount = (u16) Loc_f32OvReq;
                timer0_u8ISRFlag = 1;
            }
            else
            {
                u16 Loc_u16IntegerVal = (u16) Loc_f32OvReq;
                f32 Loc_f32FloatVal = getFraction(Loc_f32OvReq);
                timer0_u16ISRCount = Loc_u16IntegerVal + 1;
                timer0_u16Preload = (u16) (TIMER0_RESOLUTION * (1 - Loc_f32FloatVal));
                timer0_u8ISRFlag = 2;
            }
        }
        else
        {
            /* preload value */
            timer0_u16Preload = (u16) (TIMER0_RESOLUTION * (1 - Loc_f32OvReq));
            timer0_u8ISRFlag = 3;
        }
        Loc_enuErrorStatus = TMR0_enuOk;
    }
    else if(timer0_u8Mode == TMR0_MODE_CTC)
    {
		f32 Loc_f32TickTime;
		Loc_f32TickTime = 1.0 / cpy_u32Clock;
		timer0_u16ISRCount = (cpy_u16TickTime / 1000.0) / (TIMER0_OCR_VALUE * 1.0 * Loc_f32TickTime);
		timer0_u8ISRFlag = 4;
	}
    else
    {
        Loc_enuErrorStatus = TMR0_enuUnknownConfigMode;
    }
    return Loc_enuErrorStatus;
}

TMR0_enuErrorStatus_t TMR0_enuStart(void)
{
    TMR0_enuErrorStatus_t Loc_enuErrorStatus = TMR0_enuNotOk;
    if(TMR0_INIT_STATE == TMR0_INIT_STOOPED)
    {
        u8 Loc_u8Temp = TCCR0;
        Loc_u8Temp &= MSK_CLR_CS;
        Loc_u8Temp |= timer0_u8Prescaler;
        TCCR0 = Loc_u8Temp;
    }
    if (timer0_u8Mode == TMR0_MODE_NORMAL)
    {
        SET_BIT(TIMSK, TIMSK_TOIE0);
        Loc_enuErrorStatus = TMR0_enuOk;
    }
    else if (timer0_u8Mode == TMR0_MODE_CTC)
    {
        SET_BIT(TIMSK, TIMSK_OCIE0);
		OCR0 = TIMER0_OCR_VALUE;
        Loc_enuErrorStatus = TMR0_enuOk;
    }
    else
    {
        Loc_enuErrorStatus = TMR0_enuUnknownConfigMode;
    }
    return Loc_enuErrorStatus;
}

TMR0_enuErrorStatus_t TMR0_enuRegisterCallback(TMR0cbf_t add_cbf)
{
    TMR0_enuErrorStatus_t Loc_enuErrorStatus = TMR0_enuNotOk;
    if(add_cbf != NULL)
    {
        timer0_pfCallback = add_cbf;
        Loc_enuErrorStatus = TMR0_enuOk;
    }
    else
    {
        Loc_enuErrorStatus = TMR0_enuNullPointer;
    }
    return Loc_enuErrorStatus;
}

TMR0_enuErrorStatus_t TMR0_enuSetDutyCycle(u8 cpy_u8DutyCycle)
{
    TMR0_enuErrorStatus_t Loc_enuErrorStatus = TMR0_enuNotOk;
    if (cpy_u8DutyCycle > 100)
    {
        Loc_enuErrorStatus = TMR0_enuInvalidDutyCycle;
    }
    else
    {
        u8 Loc_u8OcrValue;
        switch (timer0_u8Mode)
        {
            case TMR0_MODE_FAST_PWM_DIS:
            case TMR0_MODE_PCORR_PWM_DIS:
                Loc_enuErrorStatus = TMR0_enuOcPinDisconnected;
                break;
            case TMR0_MODE_FAST_PWM_INV:
            case TMR0_MODE_PCORR_PWM_SUCD:
                Loc_u8OcrValue = (1 - (cpy_u8DutyCycle * 1.0) / 100) * TIMER0_PWM_RESOLUTION;
                OCR0 = Loc_u8OcrValue;
                Loc_enuErrorStatus = TMR0_enuOk;
                break;
            case TMR0_MODE_FAST_PWM_NINV:
            case TMR0_MODE_PCORR_PWM_CUSD:
                Loc_u8OcrValue = ((cpy_u8DutyCycle * 1.0) / 100) * TIMER0_PWM_RESOLUTION;
                OCR0 = Loc_u8OcrValue;
                Loc_enuErrorStatus = TMR0_enuOk;
                break;
            default:
                Loc_enuErrorStatus = TMR0_enuInvalidConfig;
        }
    }
    return Loc_enuErrorStatus;
}

/* TIMER0 OVF */
void __vector_11 (void) __attribute__ ((signal));
void __vector_11 (void)
{
	static u16 Loc_u16Counter = 0;
	switch(timer0_u8ISRFlag)
	{
		case 0:
			if (timer0_pfCallback != NULL)
			{
				timer0_pfCallback();
				Loc_u16Counter = 0;
			}
			break;
		case 1:
			Loc_u16Counter++;
			if (Loc_u16Counter == timer0_u16ISRCount)
			{
				if (timer0_pfCallback != NULL)
				{
					timer0_pfCallback();
					Loc_u16Counter = 0;
				}
			}
			break;
		case 2:
			Loc_u16Counter++;
			if (Loc_u16Counter == timer0_u16ISRCount)
			{
				if (timer0_pfCallback != NULL)
				{
					TCNT0 = timer0_u16Preload;
					timer0_pfCallback();
					Loc_u16Counter = 0;
				}
			}
			break;
		case 3:
			if (timer0_pfCallback != NULL)
			{
				TCNT0 = timer0_u16Preload;
				timer0_pfCallback();
			}
			break;
	}
}
/* TIMER0 COMP */
void __vector_10 (void) __attribute__ ((signal));
void __vector_10 (void)
{
	static u16 Loc_u16Counter = 0;
	Loc_u16Counter++;
	if (Loc_u16Counter == timer0_u16ISRCount)
	{
		if (timer0_pfCallback != NULL)
		{
			timer0_pfCallback();
			Loc_u16Counter = 0;
		}
	}
}
