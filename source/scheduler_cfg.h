/*
 * File: scheduler_cfg.h
 * Author: Carlos Alberto Zepeda Lopez
 *
 */

#ifndef SCHEDULER_CFG_H_
#define SCHEDULER_CFG_H_

/*******************************************************************************
 * include
 ******************************************************************************/
#include "scheduler_type.h"

/*******************************************************************************
 * define
 ******************************************************************************/
#define SYSTICK_FREQUENCY_HZ 20
#define MAX_PRIO             6

/*******************************************************************************
 * extern
 ******************************************************************************/

extern tSchedulerTasks_ID gu8curr_state;
extern tSchedulerTasks_ID gu8prev_state;

extern tSchedulingTask tasks_table[TASK_MAX];

#endif /*SCHEDULER_CFG_H_*/
