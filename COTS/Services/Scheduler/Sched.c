/*******************************************************************
*   File name:    Sched.c
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs definitions to deal with scheduler module
*                 for ATmega32
*   Version: v1.0
*******************************************************************/

#include "Sched.h"

extern const TaskInfo_t Scheduler_arrTasksInfo [MAX_TASK_NUMBER];
Runnable_Handler_t Scheduler_arrTasksHandlers [MAX_TASK_NUMBER];

static volatile u8 Scheduler_u8OsFlag;

static void Scheduler_pfCallBack(void);
static void Scheduler_run(void);

Scheduler_enuErrorStatus_t Scheduler_enuInit(void)
{
    Scheduler_enuErrorStatus_t Loc_enuErrorStatus = Scheduler_enuNotOk;
    TMR0_enuErrorStatus_t Loc_enuTMR0ErrorStatus;
    TMR0Config_t Loc_strTMR0Config = {.clockSource = TMR0_PER8_PRESC, .compareMatchOutMode = TMR0_MODE_CTC_COM_DIS, .timerMode = TMR0_MODE_NORMAL};
    u8 Loc_u8Iterator;
    for(Loc_u8Iterator = 0; Loc_u8Iterator < MAX_TASK_NUMBER; Loc_u8Iterator++)
    {
        Scheduler_arrTasksHandlers[Loc_u8Iterator].taskInfo = &Scheduler_arrTasksInfo[Loc_u8Iterator];
        Scheduler_arrTasksHandlers[Loc_u8Iterator].remainingTimeMs = Scheduler_arrTasksInfo[Loc_u8Iterator].startDelayMs;
    }
    TMR0_vidInitPostCompile(Loc_strTMR0Config);
    Loc_enuTMR0ErrorStatus = TMR0_enuRegisterCallback(Scheduler_pfCallBack);
    Loc_enuTMR0ErrorStatus = TMR0_enuSetTickTimeMS(SCHED_TICK_MS, CPU_CLOCK_SRC);
    switch (Loc_enuTMR0ErrorStatus)
    {
        case TMR0_enuOk:
            Loc_enuErrorStatus = Scheduler_enuOk;
            break;
        case TMR0_enuUnknownConfigMode:
            Loc_enuErrorStatus = Scheduler_enuNotOk;
			break;
        case TMR0_enuNullPointer:
            Loc_enuErrorStatus = Scheduler_enuNotOk;
            break;
        default:
            Loc_enuErrorStatus = Scheduler_enuNotOk;
    }
    return Loc_enuErrorStatus;
}

void Scheduler_vidStart(void)
{
    GIE_enuEnable();
    TMR0_enuStart();
    while (1)
    {
        if(Scheduler_u8OsFlag)
        {
            Scheduler_run();
            Scheduler_u8OsFlag = 0;
        }
    }
}

static void Scheduler_pfCallBack(void)
{
    if(Scheduler_u8OsFlag == 0)
    {
        Scheduler_u8OsFlag = 1;
    }
    else
    {
        /* CPU load over 100% */
    }
}

static void Scheduler_run(void)
{
    u8 Loc_u8Iterator;
    for(Loc_u8Iterator = 0; Loc_u8Iterator < MAX_TASK_NUMBER; Loc_u8Iterator++)
    {
        if(Scheduler_arrTasksHandlers[Loc_u8Iterator].remainingTimeMs == 0)
        {
            if(Scheduler_arrTasksHandlers[Loc_u8Iterator].taskInfo->taskCallBack)
            {
                Scheduler_arrTasksHandlers[Loc_u8Iterator].taskInfo->taskCallBack();
                Scheduler_arrTasksHandlers[Loc_u8Iterator].remainingTimeMs = Scheduler_arrTasksHandlers[Loc_u8Iterator].taskInfo->periodMs;
            }
        }
        Scheduler_arrTasksHandlers[Loc_u8Iterator].remainingTimeMs -= SCHED_TICK_MS;
    }
}
