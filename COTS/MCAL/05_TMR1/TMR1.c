/*******************************************************************
*   File name:    TMR1.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with timer1 peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/


#include "TMR1.h"

#define MSK_CLR_WGM                 0xE7FC
#define MSK_CLR_CS                  0xF8FF
#define MSK_CLR_COMA                0xFF3F
#define MSK_CLR_COMB                0xFFCF

#define MSK_COMA_CTC_DIS            0x0000
#define MSK_COMA_CTC_TGL            0x0040
#define MSK_COMA_CTC_CLR            0x0080
#define MSK_COMA_CTC_SET            0x00C0
#define MSK_COMB_CTC_DIS            0x0000
#define MSK_COMB_CTC_TGL            0x0010
#define MSK_COMB_CTC_CLR            0x0020
#define MSK_COMB_CTC_SET            0x0030

#define MSK_COMA_FPWM_DIS           0x0000
#define MSK_COMA_FPWM_NINV          0x0080
#define MSK_COMA_FPWM_INV           0x00C0
#define MSK_COMA_PCORR_DIS          0x0000
#define MSK_COMA_PCORR_CUSD         0x0080
#define MSK_COMA_PCORR_SUCD         0x00C0
#define MSK_COMB_FPWM_DIS           0x0000
#define MSK_COMB_FPWM_NINV          0x0020
#define MSK_COMB_FPWM_INV           0x0030
#define MSK_COMB_PCORR_DIS          0x0000
#define MSK_COMB_PCORR_CUSD         0x0020
#define MSK_COMB_PCORR_SUCD         0x0030

#define MSK_IC_CANCEL_EN            0x8000
#define MSK_IC_CANCEL_DIS           0x7FFF
#define MSK_ICES_FALLING            0xDFFF
#define MSK_ICES_RISING             0x4000

#define MSK_WGM_NORMAL              MSK_CLR_WGM
#define MSK_WGM_PCORR_8BITS         0x0001
#define MSK_WGM_PCORR_9BITS         0x0002
#define MSK_WGM_PCORR_10BITS        0x0003
#define MSK_WGM_CTC_OCR             0x0800
#define MSK_WGM_FPWM_8BITS          0x0801
#define MSK_WGM_FPWM_9BITS          0x0802
#define MSK_WGM_FPWM_10BITS         0x0803
#define MSK_WGM_PF_CTR_PWM_ICR      0x1000
#define MSK_WGM_PF_CTR_PWM_OCR      0x1001
#define MSK_WGM_PCORR_PWM_ICR       0x1002
#define MSK_WGM_PCORR_PWM_OCR       0x1003
#define MSK_WGM_CTC_ICR             0x1800
#define MSK_WGM_FPWM_ICR            0x1802
#define MSK_WGM_FPWM_OCR            0x1803

#define OVERFLOW_CALLBACK           0
#define OUTCOMPA_CALLBACK           1
#define OUTCOMPB_CALLBACK           2
#define ICU_CALLBACK                3

#define OCR_MAX_VALUE               65536
#define TIMER1_RESOLUTION           65535
#define TIMER1_OCR_VALUE            65525

static u8 timer1_u8Mode;
static u8 timer1_u8ChAMode;
static u8 timer1_u8ChBMode;
static u8 timer1_u8Prescaler;
static u16 timer1_u16Preload;
static u16 timer1_u16ISRCounts;

static TMR1_pfCallback_t timer1_pfCallback [4];

static u8 isInteger(f32 num);
static f32 getFraction(f32 num);

void TMR1_vidInit(void)
{
    u16 Loc_u16Temp = TCCR1;
    Loc_u16Temp &= MSK_CLR_WGM;
    /* Configure mode of operation for timer1 and OC1A, OC1B */
    #if TIMER1_MODE == TIMER1_MODE_NORMAL
        Loc_u16Temp &= MSK_WGM_NORMAL;
        timer1_u8Mode = TIMER1_MODE_NORMAL;
    #elif TIMER1_MODE == TIMER1_MODE_PCORR_PWM_8BITS
        Loc_u16Temp |= MSK_WGM_PCORR_8BITS;
        timer1_u8Mode = TIMER1_MODE_PCORR_PWM_8BITS;
    #elif TIMER1_MODE == TIMER1_MODE_PCORR_PWM_9BITS
        Loc_u16Temp |= MSK_WGM_PCORR_9BITS;
        timer1_u8Mode = TIMER1_MODE_PCORR_PWM_9BITS;
    #elif TIMER1_MODE == TIMER1_MODE_PCORR_PWM_10BITS
        Loc_u16Temp |= MSK_WGM_PCORR_10BITS;
        timer1_u8Mode = TIMER1_MODE_PCORR_PWM_10BITS;
    #elif TIMER1_MODE == TIMER1_MODE_CTC_OCR
        Loc_u16Temp |= MSK_WGM_CTC_OCR;
        timer1_u8Mode = TIMER1_MODE_CTC_OCR;
    #elif TIMER1_MODE == TIMER1_MODE_CTC_ICR
        Loc_u16Temp |= MSK_WGM_CTC_ICR;
        timer1_u8Mode = TIMER1_MODE_CTC_ICR;
    #elif TIMER1_MODE == TIMER1_MODE_FPWM_8BITS
        Loc_u16Temp |= MSK_WGM_FPWM_8BITS;
        timer1_u8Mode = TIMER1_MODE_FPWM_8BITS;
    #elif TIMER1_MODE == TIMER1_MODE_FPWM_9BITS
        Loc_u16Temp |= MSK_WGM_FPWM_9BITS;
        timer1_u8Mode = TIMER1_MODE_FPWM_9BITS;
    #elif TIMER1_MODE == TIMER1_MODE_FPWM_10BITS
        Loc_u16Temp |= MSK_WGM_FPWM_10BITS;
        timer1_u8Mode = TIMER1_MODE_FPWM_10BITS;
    #elif TIMER1_MODE == TIMER1_MODE_PWM_PHANDFREQ_CTRL_ICR
        Loc_u16Temp |= MSK_WGM_PF_CTR_PWM_ICR;
        timer1_u8Mode = TIMER1_MODE_PWM_PHANDFREQ_CTRL_ICR;
    #elif TIMER1_MODE == TIMER1_MODE_PWM_PHANDFREQ_CTRL_OCR
        Loc_u16Temp |= MSK_WGM_PF_CTR_PWM_OCR;
        timer1_u8Mode = TIMER1_MODE_PWM_PHANDFREQ_CTRL_OCR;
    #elif TIMER1_MODE == TIMER1_MODE_PCORR_PWM_ICR
        Loc_u16Temp |= MSK_WGM_PCORR_PWM_ICR;
        timer1_u8Mode = TIMER1_MODE_PCORR_PWM_ICR;
    #elif TIMER1_MODE == TIMER1_MODE_PCORR_PWM_OCR
        Loc_u16Temp |= MSK_WGM_PCORR_PWM_OCR;
        timer1_u8Mode = TIMER1_MODE_PCORR_PWM_OCR;
    #elif TIMER1_MODE == TIMER1_MODE_FPWM_ICR
        Loc_u16Temp |= MSK_WGM_FPWM_ICR;
        timer1_u8Mode = TIMER1_MODE_FPWM_ICR;
    #elif TIMER1_MODE == TIMER1_MODE_FPWM_OCR
        Loc_u16Temp |= MSK_WGM_FPWM_OCR;
        timer1_u8Mode = TIMER1_MODE_FPWM_OCR;
    #endif
    Loc_u16Temp &= MSK_CLR_COMA;
    Loc_u16Temp &= MSK_CLR_COMB;
    #if TIMER1_MODE == TIMER1_MODE_PCORR_PWM_8BITS || TIMER1_MODE == TIMER1_MODE_PCORR_PWM_9BITS || TIMER1_MODE == TIMER1_MODE_PCORR_PWM_10BITS || TIMER1_MODE == TIMER1_MODE_PCORR_PWM_ICR || TIMER1_MODE == TIMER1_MODE_PCORR_PWM_OCR
        #if TIMER1_CHANNEL_A_PCORR_PWM_MODE == TIMER1_PCORR_DIS
            Loc_u16Temp |= MSK_COMA_PCORR_DIS;
            timer1_u8ChAMode = TIMER1_PCORR_DIS;
        #elif TIMER1_CHANNEL_A_PCORR_PWM_MODE == TIMER1_PCORR_CUSD
            Loc_u16Temp |= MSK_COMA_PCORR_CUSD;
            timer1_u8ChAMode = TIMER1_PCORR_CUSD;
        #elif TIMER1_CHANNEL_A_PCORR_PWM_MODE == TIMER1_PCORR_SUCD
            Loc_u16Temp |= MSK_COMA_PCORR_SUCD;
            timer1_u8ChAMode = TIMER1_PCORR_SUCD;
        #endif
        #if TIMER1_CHANNEL_B_PCORR_PWM_MODE == TIMER1_PCORR_DIS
            Loc_u16Temp |= MSK_COMB_PCORR_DIS;
            timer1_u8ChBMode = TIMER1_PCORR_DIS;
        #elif TIMER1_CHANNEL_B_PCORR_PWM_MODE == TIMER1_PCORR_CUSD
            Loc_u16Temp |= MSK_COMB_PCORR_CUSD;
            timer1_u8ChBMode = TIMER1_PCORR_CUSD;
        #elif TIMER1_CHANNEL_B_PCORR_PWM_MODE == TIMER1_PCORR_SUCD
            Loc_u16Temp |= MSK_COMB_PCORR_SUCD;
            timer1_u8ChBMode = TIMER1_PCORR_SUCD;
        #endif
    #endif
    #if TIMER1_MODE == TIMER1_MODE_CTC_OCR || TIMER1_MODE == TIMER1_MODE_CTC_ICR
        #if TIMER1_CHANNEL_A_CTC_MODE == TIMER1_CTC_DIS
            Loc_u16Temp |= MSK_COMA_CTC_DIS;
            timer1_u8ChAMode = TIMER1_CTC_DIS;
        #elif TIMER1_CHANNEL_A_CTC_MODE == TIMER1_CTC_TGL
            Loc_u16Temp |= MSK_COMA_CTC_TGL;
            timer1_u8ChAMode = TIMER1_CTC_TGL;
        #elif TIMER1_CHANNEL_A_CTC_MODE == TIMER1_CTC_CLR
            Loc_u16Temp |= MSK_COMA_CTC_CLR;
            timer1_u8ChAMode = TIMER1_CTC_CLR;
        #elif TIMER1_CHANNEL_A_CTC_MODE == TIMER1_CTC_SET
            Loc_u16Temp |= MSK_COMA_CTC_SET;
            timer1_u8ChAMode = TIMER1_CTC_SET;
        #endif
        #if TIMER1_CHANNEL_B_CTC_MODE == TIMER1_CTC_DIS
            Loc_u16Temp |= MSK_COMB_CTC_DIS;
            timer1_u8ChBMode = TIMER1_CTC_DIS;
        #elif TIMER1_CHANNEL_B_CTC_MODE == TIMER1_CTC_TGL
            Loc_u16Temp |= MSK_COMB_CTC_TGL;
            timer1_u8ChBMode = TIMER1_CTC_TGL;
        #elif TIMER1_CHANNEL_B_CTC_MODE == TIMER1_CTC_CLR
            Loc_u16Temp |= MSK_COMB_CTC_CLR;
            timer1_u8ChBMode = TIMER1_CTC_CLR;
        #elif TIMER1_CHANNEL_B_CTC_MODE == TIMER1_CTC_SET
            Loc_u16Temp |= MSK_COMB_CTC_SET;
            timer1_u8ChBMode = TIMER1_CTC_SET;
        #endif
    #endif
    #if TIMER1_MODE == TIMER1_MODE_FPWM_8BITS || TIMER1_MODE == TIMER1_MODE_FPWM_9BITS || TIMER1_MODE == TIMER1_MODE_FPWM_10BITS || TIMER1_MODE == TIMER1_MODE_FPWM_ICR || TIMER1_MODE == TIMER1_MODE_FPWM_OCR
        #if TIMER1_CHANNEL_A_FPWM_MODE == TIMER1_FPWM_DIS
            Loc_u16Temp |= MSK_COMA_FPWM_DIS;
            timer1_u8ChAMode = TIMER1_FPWM_DIS;
        #elif TIMER1_CHANNEL_A_FPWM_MODE == TIMER1_FPWM_INV
            Loc_u16Temp |= MSK_COMA_FPWM_INV;
            timer1_u8ChAMode = TIMER1_FPWM_INV;
        #elif TIMER1_CHANNEL_A_FPWM_MODE == TIMER1_FPWM_NINV
            Loc_u16Temp |= MSK_COMA_FPWM_NINV;
            timer1_u8ChAMode = TIMER1_FPWM_NINV;
        #endif
        #if TIMER1_CHANNEL_B_FPWM_MODE == TIMER1_FPWM_DIS
            Loc_u16Temp |= MSK_COMB_FPWM_DIS;
            timer1_u8ChBMode = TIMER1_FPWM_DIS;
        #elif TIMER1_CHANNEL_B_FPWM_MODE == TIMER1_FPWM_INV
            Loc_u16Temp |= MSK_COMB_FPWM_INV;
            timer1_u8ChBMode = TIMER1_FPWM_INV;
        #elif TIMER1_CHANNEL_B_FPWM_MODE == TIMER1_FPWM_NINV
            Loc_u16Temp |= MSK_COMb_FPWM_NINV;
            timer1_u8ChBMode = TIMER1_FPWM_NINV;
        #endif
    #endif
    /* enable ICU noise canceler */
    Loc_u16Temp |= MSK_IC_CANCEL_EN;
    #if IC_EDGE_SELECT == IC_EDGE_FALLING
        Loc_u16Temp &= MSK_ICES_FALLING; 
    #elif IC_EDGE_SELECT == IC_EDGE_RISING
        Loc_u16Temp |= MSK_ICES_RISING; 
    #endif
    /* clock source */
    Loc_u16Temp &= MSK_CLR_CS;
    #if TIMER1_PRESCALER == TIMER1_PRESC_NO_PRES
        timer1_u8Prescaler = TIMER1_PRESC_NO_PRES;
    #elif TIMER1_PRESCALER == TIMER1_PRESC_PER8
        timer1_u8Prescaler = TIMER1_PRESC_PER8;
    #elif TIMER1_PRESCALER == TIMER1_PRESC_PER64
        timer1_u8Prescaler = TIMER1_PRESC_PER64;
    #elif TIMER1_PRESCALER == TIMER1_PRESC_PER256
        timer1_u8Prescaler = TIMER1_PRESC_PER256;
    #elif TIMER1_PRESCALER == TIMER1_PRESC_PER1024
        timer1_u8Prescaler = TIMER1_PRESC_PER1024;
    #elif TIMER1_PRESCALER == TIMER1_EXT_FALLLING
        timer1_u8Prescaler = TIMER1_EXT_FALLLING;
    #elif TIMER1_PRESCALER == TIMER1_EXT_RISING
        timer1_u8Prescaler = TIMER1_EXT_RISING;
    #endif

    /* ICU Enable or Disable */
    #if ICU_STATUS  == ICU_ENABLED
        TIMSK |= (1 << TIMSK_TICIE1);
    #elif ICU_STATUS  == ICU_DISABLED
        TIMSK &= ~(1 << TIMSK_TICIE1);
    #endif
    TCCR1 = Loc_u16Temp;
}

TMR1_enuErrorStatus_t TMR1_enuStart(void)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    u16 Loc_u16Temp = TCCR1;
    if(timer1_u8Mode == TIMER1_MODE_NORMAL)
    {
        TIMSK |= (1 << TIMSK_TOIE1);
        Loc_u16Temp &= MSK_CLR_CS;
        Loc_u16Temp |= timer1_u8Prescaler;
        TCCR1 = Loc_u16Temp;
        Loc_enuErrorStatus = TMR1_enuOk;
    }
    else if(timer1_u8ChBMode == TIMER1_MODE_CTC_OCR || timer1_u8ChBMode == TIMER1_MODE_CTC_ICR)
    {
        TIMSK |= (1 << TIMSK_OCIE1A);
        TIMSK |= (1 << TIMSK_OCIE1B);
        Loc_u16Temp &= MSK_CLR_CS;
        Loc_u16Temp |= timer1_u8Prescaler;
        TCCR1 = Loc_u16Temp;
        Loc_enuErrorStatus = TMR1_enuOk;
    }
    else
    {
        Loc_enuErrorStatus = TMR1_enuInvalidConfig;
    }
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuSetTicktimeMS(u32 cpy_u32Ticktime, u64 cpy_u64Clock)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    if (timer1_u8Mode == TIMER1_MODE_NORMAL)
    {
        f32 Loc_f32TickTime, Loc_f32OvTime, Loc_f32OvReq;
        Loc_f32TickTime = 1.0 / cpy_u64Clock;
        Loc_f32OvTime = TIMER1_RESOLUTION * Loc_f32TickTime;
        Loc_f32OvReq = (cpy_u32Ticktime / 1000.0) / Loc_f32OvTime;
        if (Loc_f32OvReq == Loc_f32OvTime)
        {
            /* required only one isr */
            timer1_u16ISRCounts = 1;
        }
        else if(Loc_f32OvReq > Loc_f32OvTime)
        {
            /* required multiple isrs */
            if (isInteger(Loc_f32OvReq))
            {
                timer1_u16ISRCounts = (u16) Loc_f32OvReq;
                timer1_u16Preload = 0;
            }
            else
            {
                u16 Loc_u16IntegerVal = (u16) Loc_f32OvReq;
                f32 Loc_f32FloatVal = getFraction(Loc_f32OvReq);
                timer1_u16ISRCounts = Loc_u16IntegerVal + 1;
                timer1_u16Preload = (u16) (TIMER1_RESOLUTION * (1 - Loc_f32FloatVal));
            }
        }
        else
        {
            /* preload value */
            timer1_u16Preload = (u16) (TIMER1_RESOLUTION * (1 - Loc_f32OvReq));
            timer1_u16ISRCounts = 1;
        }
        Loc_enuErrorStatus = TMR1_enuOk;
    }
    else if (timer1_u8Mode == TIMER1_MODE_CTC_OCR)
    {
        f32 Loc_f32TickTime;
		Loc_f32TickTime = 1.0 / cpy_u64Clock;
		timer1_u16ISRCounts = (cpy_u32Ticktime / 1000.0) / (TIMER1_OCR_VALUE * 1.0 * Loc_f32TickTime);
    }
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuSetDutyCycleChannelA(u8 cpy_u8Duty)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuSetDutyCycleChannelB(u8 cpy_u8Duty)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuSetOutCompareMatchChannelA(u16 cpy_u16CompareMatchVal)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    if(cpy_u16CompareMatchVal < OCR_MAX_VALUE)
    {
        OCR1A = cpy_u16CompareMatchVal;
        Loc_enuErrorStatus = TMR1_enuOk;
    }
    else
    {
        Loc_enuErrorStatus = TMR1_enuInvalidOCRValue;
    }
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuSetOutCompareMatchChannelB(u16 cpy_u16CompareMatchVal)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    if(cpy_u16CompareMatchVal < OCR_MAX_VALUE)
    {
        OCR1B = cpy_u16CompareMatchVal;
        Loc_enuErrorStatus = TMR1_enuOk;
    }
    else
    {
        Loc_enuErrorStatus = TMR1_enuInvalidOCRValue;
    }
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuStop(void)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    if(timer1_u8Mode == TIMER1_MODE_NORMAL)
    {
        TIMSK &= ~(1 << TIMSK_TOIE1);
        TCCR1 &= MSK_CLR_CS;
        Loc_enuErrorStatus = TMR1_enuOk;
    }
    else if(timer1_u8ChBMode == TIMER1_MODE_CTC_OCR || timer1_u8ChBMode == TIMER1_MODE_CTC_ICR)
    {
        TIMSK &= ~(1 << TIMSK_OCIE1A);
        TIMSK &= ~(1 << TIMSK_OCIE1B);
        TCCR1 &= MSK_CLR_CS;
        Loc_enuErrorStatus = TMR1_enuOk;
    }
    else
    {
        Loc_enuErrorStatus = TMR1_enuInvalidConfig;
    }
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuSetOVCallback(TMR1_pfCallback_t add_pfCallback)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    if (add_pfCallback != NULL)
    {
        timer1_pfCallback[OVERFLOW_CALLBACK] = add_pfCallback;
    }
    else
    {
        Loc_enuErrorStatus = TMR1_enuNullPointer;
    }
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuSetCompareMatchACallback(TMR1_pfCallback_t add_pfCallback)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    if (add_pfCallback != NULL)
    {
        timer1_pfCallback[OUTCOMPA_CALLBACK] = add_pfCallback;
    }
    else
    {
        Loc_enuErrorStatus = TMR1_enuNullPointer;
    }
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuSetCompareMatchBCallback(TMR1_pfCallback_t add_pfCallback)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    if (add_pfCallback != NULL)
    {
        timer1_pfCallback[OUTCOMPB_CALLBACK] = add_pfCallback;
    }
    else
    {
        Loc_enuErrorStatus = TMR1_enuNullPointer;
    }
    return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus_t TMR1_enuSetICUCallback(TMR1_pfCallback_t add_pfCallback)
{
    TMR1_enuErrorStatus_t Loc_enuErrorStatus = TMR1_enuNotOk;
    if (add_pfCallback != NULL)
    {
        timer1_pfCallback[ICU_CALLBACK] = add_pfCallback;
    }
    else
    {
        Loc_enuErrorStatus = TMR1_enuNullPointer;
    }
    return Loc_enuErrorStatus;
}

/* TIMER1 CAPT */
void __vector_6 (void) __attribute__ ((signal));
void __vector_6 (void)
{
    if (timer1_pfCallback[ICU_CALLBACK] != NULL)
    {
        timer1_pfCallback[ICU_CALLBACK]();
    }
}

/* TIMER1 COMPA */
void __vector_7 (void) __attribute__ ((signal));
void __vector_7 (void)
{
    if (timer1_pfCallback[OUTCOMPA_CALLBACK] != NULL)
    {
        timer1_pfCallback[OUTCOMPA_CALLBACK]();
    }
}

/* TIMER1 COMPB */
void __vector_8 (void) __attribute__ ((signal));
void __vector_8 (void)
{
    if (timer1_pfCallback[OUTCOMPB_CALLBACK] != NULL)
    {
        timer1_pfCallback[OUTCOMPB_CALLBACK]();
    }
}

/* TIMER1 OVF */
void __vector_9 (void) __attribute__ ((signal));
void __vector_9 (void)
{
    static u16 Loc_u16Counter;
    Loc_u16Counter++;
    timer1_u16ISRCounts;
    if(Loc_u16Counter++ == timer1_u16ISRCounts)
    {
        if (timer1_pfCallback[OVERFLOW_CALLBACK] != NULL)
        {
            Loc_u16Counter = 0;
            timer1_pfCallback[OVERFLOW_CALLBACK]();
        }
    }
    else
    {
        TCNT1 = timer1_u16Preload;
    }
}

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
