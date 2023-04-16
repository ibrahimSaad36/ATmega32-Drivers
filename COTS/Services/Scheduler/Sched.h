/*******************************************************************
*   File name:    Sched.h
*   Author:       Ibrahim Saad
*   Description:  This file contains all APIs declarations to deal with scheduler module
*                 for ATmega32
*   Version: v1.0
*******************************************************************/

#ifndef SCHED_H
#define SCHED_H

#include "Sched_Cfg.h"
#include "GIE.h"
#include "TMR0.h"

typedef struct 
{
    const TaskInfo_t* taskInfo;
    u16 remainingTimeMs;
}Runnable_Handler_t;


typedef enum {
    Scheduler_enuNotOk = 0,
    Scheduler_enuOk,
    sched_retInvalidTick,
}Scheduler_enuErrorStatus_t;

Scheduler_enuErrorStatus_t Scheduler_enuInit(void);
void Scheduler_vidStart(void);

#endif
