/*
 * File: scheduler_cfg.c
 * Author: Carlos Alberto Zepeda Lopez
 *
 */

/*******************************************************************************
 * include
 ******************************************************************************/
#include "scheduler_cfg.h"
#include "task_app.h"

/*******************************************************************************
 * global var
 ******************************************************************************/

tSchedulerTasks_ID gu8curr_state = TASK_STATE_A;
tSchedulerTasks_ID gu8prev_state = TASK_STATE_F;

/*carlosa stae machine array*/
tSchedulingTask tasks_table[] = {
    /*TaskId*/       /*ptrTask*/     /*enTaskState*/    /*u8Priority*/
    {TASK_STATE_A,  p2f_state_a,    READY,              5},
    {TASK_STATE_B,  p2f_state_b,    SUSPENDED,          5},
    {TASK_STATE_C,  p2f_state_c,    SUSPENDED,          5},
    {TASK_STATE_D,  p2f_state_d,    SUSPENDED,          5},
    {TASK_STATE_E,  p2f_state_e,    SUSPENDED,          5},
    {TASK_STATE_F,  p2f_state_f,    SUSPENDED,          5},
    {TASK_STATE_G,  p2f_state_g,    READY,              5}
};
