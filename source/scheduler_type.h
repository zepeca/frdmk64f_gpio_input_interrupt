/*
 * File: scheduler_type.h
 * Author: Carlos Alberto Zepeda Lopez
 *
 */

#ifndef SCHEDULER_TYPE_H_
#define SCHEDULER_TYPE_H_

/*******************************************************************************
 * include
 ******************************************************************************/
#include "stdbool.h"
#include "stdint.h"

/*******************************************************************************
 * type def
 ******************************************************************************/

typedef enum
{
    SUSPENDED,
    READY,
    RUNNING
}tTaskStates;

typedef enum  
{   
    TASK_STATE_A,
    TASK_STATE_B,
    TASK_STATE_C,
    TASK_STATE_D,
    TASK_STATE_E,
    TASK_STATE_F,
    TASK_STATE_G,
    TASK_MAX,
}tSchedulerTasks_ID;

typedef  void  ( * tPtr_to_function )( void );

typedef struct 
{
    tSchedulerTasks_ID     TaskId;
    tPtr_to_function       ptrTask;
    tTaskStates            enTaskState;
    uint8_t                u8Priority;

}tSchedulingTask;

typedef bool tScheduler_bool;

#endif /*SCHEDULER_TYPE_H_*/
