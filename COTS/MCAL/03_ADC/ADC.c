/*******************************************************************
*   File name:    ADC.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with ADC peripheral
*                 in ATmega32
*   Version: v1.0
*******************************************************************/

#include "../../Lib/Bit_math.h"
#include "ADC_Priv.h"
#include "ADC_Cfg.h"
#include "ADC.h"

#define ADC_TIMEOUT			2000000UL
#define MSK_CLEAR_CHANNEL	0b11100000
#define MSK_CLEAR_PRESCALER 0b11111000
#define MSK_CLEAR_MODE		0b00011111
#define MSK_CLEAR_VREF		0b00111111

static ADC_strChain_t ADC_strChain = {0, NULL, NULL};
static ADC_tenuChainState ADC_enuChainState = ADC_enuChainReady;
static u8 ADC_u8ChainSelected = 0;    /* cbf (2), chain(1), not selected(0)*/
static void (*ADC_ptrCallBack) (void) = NULL;
static u8 ADC_u8CurrentIndex = 0;

/* static function to select channel */
static ADC_tenuErrorStatus ADC_enuSelectChannel(u8 cpy_u8Channel)
{
    ADC_tenuErrorStatus Loc_enuErrorStatus = ADC_enuNotOk;
    u8 Loc_u8Temp;
    switch (cpy_u8Channel)
    {
        case ADC_CHANNEL_0:
            Loc_u8Temp = ADMUX;
			Loc_u8Temp &= MSK_CLEAR_CHANNEL;
            Loc_u8Temp |= ADC_CHANNEL_0;
            ADMUX = Loc_u8Temp;
            Loc_enuErrorStatus = ADC_enuOk;
            break;
        case ADC_CHANNEL_1:
            Loc_u8Temp = ADMUX;
			Loc_u8Temp &= MSK_CLEAR_CHANNEL;
            Loc_u8Temp |= ADC_CHANNEL_1;
            ADMUX = Loc_u8Temp;
            Loc_enuErrorStatus = ADC_enuOk;
            break;
        case ADC_CHANNEL_2:
            Loc_u8Temp = ADMUX;
			Loc_u8Temp &= MSK_CLEAR_CHANNEL;
            Loc_u8Temp |= ADC_CHANNEL_2;
            ADMUX = Loc_u8Temp;
            Loc_enuErrorStatus = ADC_enuOk;
            break;
        case ADC_CHANNEL_3:
            Loc_u8Temp = ADMUX;
			Loc_u8Temp &= MSK_CLEAR_CHANNEL;
            Loc_u8Temp |= ADC_CHANNEL_3;
            ADMUX = Loc_u8Temp;
            Loc_enuErrorStatus = ADC_enuOk;
            break;
        case ADC_CHANNEL_4:
            Loc_u8Temp = ADMUX;
			Loc_u8Temp &= MSK_CLEAR_CHANNEL;
            Loc_u8Temp |= ADC_CHANNEL_4;
            ADMUX = Loc_u8Temp;
            Loc_enuErrorStatus = ADC_enuOk;
            break;
        case ADC_CHANNEL_5:
            Loc_u8Temp = ADMUX;
			Loc_u8Temp &= MSK_CLEAR_CHANNEL;
            Loc_u8Temp |= ADC_CHANNEL_5;
            ADMUX = Loc_u8Temp;
            Loc_enuErrorStatus = ADC_enuOk;
            break;
        case ADC_CHANNEL_6:
            Loc_u8Temp = ADMUX;
			Loc_u8Temp &= MSK_CLEAR_CHANNEL;
            Loc_u8Temp |= ADC_CHANNEL_6;
            ADMUX = Loc_u8Temp;
            Loc_enuErrorStatus = ADC_enuOk;
            break;
        case ADC_CHANNEL_7:
            Loc_u8Temp = ADMUX;
			Loc_u8Temp &= MSK_CLEAR_CHANNEL;
            Loc_u8Temp |= ADC_CHANNEL_7;
            ADMUX = Loc_u8Temp;
            Loc_enuErrorStatus = ADC_enuOk;
            break;
        default:
            Loc_enuErrorStatus = ADC_enuInvalidChannel;
    }
    return Loc_enuErrorStatus;
}

ADC_tenuErrorStatus ADC_enuInit(void)
{
    ADC_tenuErrorStatus Loc_enuErrorStatus = ADC_enuNotOk;
    u8 Loc_u8Temp;
	
	/* ADC Enable or disable */
	#if (ADC_STATE == ADC_EN)
		SET_BIT(ADCSRA, ADCSRA_ADEN);
		Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_STATE == ADC_DISABLE)
		CLR_BIT(ADCSRA, ADCSRA_ADEN);
		Loc_enuErrorStatus = ADC_enuOk;
	#else
		Loc_enuErrorStatus = ADC_enuInvalidInitOption;
	#endif
	
	/* ADC Prescaler */
	#if (ADC_PRESCALER == ADC_PRES_2)
		Loc_u8Temp = ADCSRA;
		Loc_u8Temp &= MSK_CLEAR_PRESCALER;
		Loc_u8Temp |= ADCSRA_PRESC_2;
		ADCSRA = Loc_u8Temp;
		Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_PRESCALER == ADC_PRES_4)
		Loc_u8Temp = ADCSRA;
		Loc_u8Temp &= MSK_CLEAR_PRESCALER;
		Loc_u8Temp |= ADCSRA_PRESC_4;
		ADCSRA = Loc_u8Temp;
		Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_PRESCALER == ADC_PRES_8)
		Loc_u8Temp = ADCSRA;
		Loc_u8Temp &= MSK_CLEAR_PRESCALER;
		Loc_u8Temp |= ADCSRA_PRESC_8;
		ADCSRA = Loc_u8Temp;
		Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_PRESCALER == ADC_PRES_16)
		Loc_u8Temp = ADCSRA;
		Loc_u8Temp &= MSK_CLEAR_PRESCALER;
		Loc_u8Temp |= ADCSRA_PRESC_16;
		ADCSRA = Loc_u8Temp;
		Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_PRESCALER == ADC_PRES_32)
		Loc_u8Temp = ADCSRA;
		Loc_u8Temp &= MSK_CLEAR_PRESCALER;
		Loc_u8Temp |= ADCSRA_PRESC_32;
		ADCSRA = Loc_u8Temp;
		Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_PRESCALER == ADC_PRES_64)
		Loc_u8Temp = ADCSRA;
		Loc_u8Temp &= MSK_CLEAR_PRESCALER;
		Loc_u8Temp |= ADCSRA_PRESC_64;
		ADCSRA = Loc_u8Temp;
	Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_PRESCALER == ADC_PRES_128)
		Loc_u8Temp = ADCSRA;
		Loc_u8Temp &= MSK_CLEAR_PRESCALER;
		Loc_u8Temp |= ADCSRA_PRESC_128;
		ADCSRA = Loc_u8Temp;
		Loc_enuErrorStatus = ADC_enuOk;
	#else
		Loc_enuErrorStatus = ADC_enuInvalidInitOption;
	#endif
	
	/* ADC VREF source */
	#if (ADC_VREF_SRC == ADC_AVCC)
		Loc_u8Temp = ADMUX;
		Loc_u8Temp &= MSK_CLEAR_VREF;
		Loc_u8Temp |= VREF_SRC_AREF;
		ADMUX = Loc_u8Temp;
		Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_VREF_SRC == ADC_AREF)
		Loc_u8Temp = ADMUX;
		Loc_u8Temp &= MSK_CLEAR_VREF;
		Loc_u8Temp |= VREF_SRC_AVCC;
		ADMUX = Loc_u8Temp;
		Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_VREF_SRC == ADC_INT)
		Loc_u8Temp = ADMUX;
		Loc_u8Temp &= MSK_CLEAR_VREF;
		Loc_u8Temp |= VREF_SRC_INT;
		ADMUX = Loc_u8Temp;
		Loc_enuErrorStatus = ADC_enuOk;
	#else
		Loc_enuErrorStatus = ADC_enuInvalidInitOption;
	#endif
	
	/* ADC Adjustment */
	#if (ADC_ADJUST == ADC_RIGHT_ADJUST)
		CLR_BIT(ADMUX, ADMUX_ADLAR);
		Loc_enuErrorStatus = ADC_enuOk;
	#elif (ADC_ADJUST == ADC_LEFT_ADJUST)
		SET_BIT(ADMUX, ADMUX_ADLAR);
		Loc_enuErrorStatus = ADC_enuOk;
	#else
		Loc_enuErrorStatus = ADC_enuInvalidInitOption;
	#endif
	
    /* ADC Mode */
    #if (ADC_MDOE == ADC_MODE_FREE_RUNNING)
        Loc_u8Temp = SFIOR;
		Loc_u8Temp &= MSK_CLEAR_MODE;
        Loc_u8Temp |= ATS_FREE_RUNNING;
        SFIOR = Loc_u8Temp;
        Loc_enuErrorStatus = ADC_enuOk;
    #elif (ADC_MDOE == ADC_MODE_ANALOG_COMPA)
        Loc_u8Temp = SFIOR;
		Loc_u8Temp &= MSK_CLEAR_MODE;
        Loc_u8Temp |= ATS_ANALOG_COMP;
        SFIOR = Loc_u8Temp;
        Loc_enuErrorStatus = ADC_enuOk;
    #elif (ADC_MDOE == ADC_MODE_EXINT0)
        Loc_u8Temp = SFIOR;
		Loc_u8Temp &= MSK_CLEAR_MODE;
        Loc_u8Temp |= ATS_EXINT0;
        SFIOR = Loc_u8Temp;
        Loc_enuErrorStatus = ADC_enuOk;
    #elif (ADC_MDOE == ADC_MODE_TIMR0_COMPA)
        Loc_u8Temp = SFIOR;
        Loc_u8Temp |= ATS_TIMR0_COMPA;
        SFIOR = Loc_u8Temp;
		Loc_u8Temp &= MSK_CLEAR_MODE;
        Loc_enuErrorStatus = ADC_enuOk;
    #elif (ADC_MDOE == ADC_MODE_TIMR0_OVF)
        Loc_u8Temp = SFIOR;
		Loc_u8Temp &= MSK_CLEAR_MODE;
        Loc_u8Temp |= ATS_TIMR0_OVF;
        SFIOR = Loc_u8Temp;
        Loc_enuErrorStatus = ADC_enuOk;
    #elif (ADC_MDOE == ADC_MODE_TIMR1_COMP_B)
        Loc_u8Temp = SFIOR;
		Loc_u8Temp &= MSK_CLEAR_MODE;
        Loc_u8Temp |= ATS_TIMR1_COMP_B;
        SFIOR = Loc_u8Temp;
        Loc_enuErrorStatus = ADC_enuOk;
    #elif (ADC_MDOE == ADC_MODE_TIMR1_OVF)
        Loc_u8Temp = SFIOR;
		Loc_u8Temp &= MSK_CLEAR_MODE;
        Loc_u8Temp |= ATS_TIMR1_OVF;
        SFIOR = Loc_u8Temp;
        Loc_enuErrorStatus = ADC_enuOk;
    #elif (ADC_MDOE == ADC_MODE_TIMR1_CAP_EVENT)
        Loc_u8Temp = SFIOR;
		Loc_u8Temp &= MSK_CLEAR_MODE;
        Loc_u8Temp |= ATS_TIMR1_CAP_EVENT;
        SFIOR = Loc_u8Temp;
        Loc_enuErrorStatus = ADC_enuOk;
    #else
        Loc_enuErrorStatus = ADC_enuInvalidInitOption;
    #endif
    return Loc_enuErrorStatus;
}

ADC_tenuErrorStatus ADC_enuEnableADC()
{
    ADC_tenuErrorStatus Loc_enuErrorStatus = ADC_enuNotOk;
    SET_BIT(ADCSRA, ADCSRA_ADEN);
    if(GET_BIT(ADCSRA, ADCSRA_ADEN) == 1)
    {
        Loc_enuErrorStatus = ADC_enuOk;
    }
    return Loc_enuErrorStatus;
}

ADC_tenuErrorStatus ADC_enuDisbleADC()
{
    ADC_tenuErrorStatus Loc_enuErrorStatus = ADC_enuNotOk;
    CLR_BIT(ADCSRA, ADCSRA_ADEN);
    if(GET_BIT(ADCSRA, ADCSRA_ADEN) == 0)
    {
        Loc_enuErrorStatus = ADC_enuOk;
    }
    return Loc_enuErrorStatus;
}

ADC_tenuErrorStatus ADC_enuGetChannelValue(u8 cpy_u8Channel, pu16 add_pu16Value)
{
    ADC_tenuErrorStatus Loc_enuErrorStatus = ADC_enuNotOk;
    u16 Loc_u16Iterator = ADC_TIMEOUT;
    Loc_enuErrorStatus = ADC_enuSelectChannel(cpy_u8Channel);
    if (Loc_enuErrorStatus == ADC_enuOk)
    {
        while ((GET_BIT(ADCSRA, ADCSRA_ADIF) == ADC_CONVERTING) && (Loc_u16Iterator > 0))
        {
            Loc_u16Iterator--;
        }
        if(Loc_u16Iterator == ADC_TIMEOUT)
        {
            Loc_enuErrorStatus = ADC_enuNotOk;
        }
        else
        {
            if(GET_BIT(ADMUX, ADMUX_ADLAR) == ADMUX_ADLAR_RIGHT)
            {
				u16 Loc_u16ADCL = (u16) ADCL;
				u16 Loc_u16ADCH = (u16)((ADCH) << 8);
                *add_pu16Value = Loc_u16ADCL + Loc_u16ADCH;
            }
            else
            {
                u16 Loc_u16ADCL = (u16) ((ADCL) >> 6);
                u16 Loc_u16ADCH = (u16) (ADCH);
                *add_pu16Value = Loc_u16ADCL + Loc_u16ADCH;
            }
            Loc_enuErrorStatus = ADC_enuOk;
        }
    }
    return Loc_enuErrorStatus;
}

ADC_tenuErrorStatus ADC_enuStartConversion(u8 cpy_u8Channel)
{
    ADC_tenuErrorStatus Loc_enuErrorStatus = ADC_enuNotOk;
    Loc_enuErrorStatus = ADC_enuSelectChannel(cpy_u8Channel);
    if(Loc_enuErrorStatus == ADC_enuOk)
    {
        SET_BIT(ADCSRA, ADCSRA_ADSC);
		CLR_BIT(ADCSRA, ADCSRA_ADIF);
        Loc_enuErrorStatus = ADC_enuOk;
    }
    return Loc_enuErrorStatus;
}

ADC_tenuErrorStatus ADC_enuStartConversionAsync(ADC_strChain_t cpy_strChain)
{
    ADC_tenuErrorStatus Loc_enuErrorStatus = ADC_enuNotOk;
    if(ADC_enuChainState == ADC_enuChainReady)
    {
        ADC_enuChainState = ADC_enuChainBusy;
        ADC_strChain.chainLength = cpy_strChain.chainLength;
        ADC_strChain.chainChannels = cpy_strChain.chainChannels;
        ADC_strChain.chainResults = cpy_strChain.chainResults;
        ADC_strChain.EOJ = cpy_strChain.EOJ;
        ADC_u8CurrentIndex = 0;
        ADC_enuSelectChannel(ADC_u8CurrentIndex);
    }
    else
    {
        Loc_enuErrorStatus = ADC_enuErrorChainBusy;
    }
    return Loc_enuErrorStatus;
}

ADC_tenuErrorStatus ADC_enuGetChainState(pu8 add_pu8State)
{
    ADC_tenuErrorStatus Loc_enuErrorStatus;
    *add_pu8State = ADC_enuChainState;
    Loc_enuErrorStatus = ADC_enuOk;
    return Loc_enuErrorStatus;
}

ADC_tenuErrorStatus ADC_enuSetADCCallBack(void (*cbf) (void))
{
    ADC_tenuErrorStatus Loc_enuErrorStatus = ADC_enuNotOk;
    if(cbf == NULL)
    {
        Loc_enuErrorStatus = ADC_enuNullPointer;
    }
    else
    {
        ADC_u8ChainSelected = 2;
        ADC_ptrCallBack = cbf;
        Loc_enuErrorStatus = ADC_enuOk;
    }
    return Loc_enuErrorStatus;
}

/* ISR Handler */
ADC_ISR(16)
{
    if(ADC_u8ChainSelected == 0)
    {
        /* default (neither ADC_enuSetADCCallBack or ADC_enuStartConversionAsync called)*/
        // do nothing
    }
    else if(ADC_u8ChainSelected == 1)
    {
        /* ADC_enuStartConversionAsync */
        if(ADC_u8CurrentIndex < ADC_strChain.chainLength)
        {
            if(GET_BIT(ADMUX, ADMUX_ADLAR) == ADMUX_ADLAR_RIGHT)
            {
                ADC_strChain.chainResults[ADC_u8CurrentIndex] = (u16) ADCL + ((ADCH) << 8);
            }
            else
            {
                ADC_strChain.chainResults[ADC_u8CurrentIndex] = (u16) (ADCL >> 6) + ADCH;
            }
            ADC_u8CurrentIndex++;
        }
        else if(ADC_u8CurrentIndex == ADC_strChain.chainLength)
        {
            ADC_u8CurrentIndex = 0;
            ADC_enuChainState = ADC_enuChainReady;
            ADC_strChain.EOJ();
        }
    }
    else if(ADC_u8ChainSelected == 2)
    {
        /* ADC_enuSetADCCallBack */
        if(ADC_ptrCallBack != NULL)
        {
            ADC_ptrCallBack();
        }
    }
}