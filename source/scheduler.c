/*
 * File: scheduler.c
 * Author: Carlos Alberto Zepeda Lopez
 *
 */

/*******************************************************************************
 * include
 ******************************************************************************/
#include "scheduler.h"
#include "MK64F12.h"

/*******************************************************************************
 * global var
 ******************************************************************************/
uint8_t gu8_task_to_run;
unsigned int TASK_stack[256*TASK_MAX] = {0};
unsigned int *TASK_stack_start[TASK_MAX];

/*******************************************************************************
 * code
 ******************************************************************************/

void vfnTask_Scheduler_Init(void){

    uint8_t index_1 = 1;

    /*stack start address for each task*/
    for (uint8_t index_0 = 0; index_0 < TASK_MAX; index_0++) {
        
        TASK_stack_start[index_0] = &TASK_stack[256 * index_1 - STACK_REGISTERS];

        /* Setting task function address for the link register */
        TASK_stack[256 * index_1 - STACK_REGISTERS + LINKER_REGISTER] = (unsigned int)(tasks_table[index_0].ptrTask);

        index_1++;
    }

    /*SysTick configuration*/
    SysTick_Config(SystemCoreClock/SYSTICK_FREQUENCY_HZ);
}

void vfnTask_Scheduler_Cbk(void){
    /*udpate previous state with current state*/
    gu8prev_state = gu8curr_state;

    /*update current state with the next task*/
    if(gu8curr_state < TASK_STATE_F){
        gu8curr_state++;
    }
    else{
        gu8curr_state = TASK_STATE_A;
    }

    /*activate a task acording to current state*/
    vfnScheduler_TaskActivate(&tasks_table[gu8curr_state]);
}

void vfnTask_Scheduler (void){
    tScheduler_bool    lboolRunTaskPrev_Flag = 0;
    tScheduler_bool    lboolRunTask_Flag =     0;
    uint8_t   lu8TaskToRun_Id =       0;
    uint8_t   lu8Task_Id = 0;

    /*linear search for the first TASK as READY*/
    /*linear search for the first TASK if prio is same for all task than FIFO behavior*/
    for(lu8Task_Id = 0; lu8Task_Id<TASK_MAX; lu8Task_Id++){

        if (tasks_table[lu8Task_Id].enTaskState == READY){

            /*at least one task is ready*/
            lboolRunTaskPrev_Flag = lboolRunTask_Flag;
            lboolRunTask_Flag = 1;

            /*task is max prio*/
            if (tasks_table[lu8Task_Id].u8Priority == MAX_PRIO){ 
                lu8TaskToRun_Id = lu8Task_Id;
                break;
            }
            else{

                /*no prio to compare with*/
                if (lboolRunTaskPrev_Flag == 0){
                    lu8TaskToRun_Id = lu8Task_Id;
                }
                else{
                    /*task priority is higher than current task to run*/
                    if (tasks_table[lu8Task_Id].u8Priority > tasks_table[lu8TaskToRun_Id].u8Priority){

                        lu8TaskToRun_Id = lu8Task_Id;
                    }  
                }
                
 
            }
        }
    }

    /*at least one task is in ready state*/
    if (lboolRunTask_Flag){

        /* start task */
        vfnScheduler_TaskStart (&tasks_table[lu8TaskToRun_Id]);
    }
}

/*
* Set task state to RUNNING
* Calls Task ptrTask
* Set task state to SUSPENDED
*/
void vfnScheduler_TaskStart( tSchedulingTask * Task )
{   
    Task->enTaskState = RUNNING;

    /*PendSV*/
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

    /*update task to run*/
    gu8_task_to_run = Task->TaskId;

    //Task->ptrTask();
    
    Task->enTaskState = SUSPENDED;
}

/*
* Set task state to READY
*/
void vfnScheduler_TaskActivate( tSchedulingTask * Task )
{
    Task->enTaskState = READY;
}
