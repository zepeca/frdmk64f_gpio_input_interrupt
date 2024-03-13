/*
 * File: scheduler.h
 * Author: Carlos Alberto Zepeda Lopez
 *
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/*******************************************************************************
 * include
 ******************************************************************************/
#include "scheduler_type.h"
#include "scheduler_cfg.h"

/*******************************************************************************
 * prototype
 ******************************************************************************/
void vfnTask_Scheduler_Init(void);
void vfnTask_Scheduler_Cbk(void);
void vfnTask_Scheduler(void);
void vfnScheduler_TaskStart(tSchedulingTask *Task);
void vfnScheduler_TaskActivate(tSchedulingTask *Task);

#endif /*SCHEDULER_H_*/
