/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "gpio_input_interrupt.h"
#include "task_app.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void vfnTask_Scheduler(void);
void vfnScheduler_TaskStart( tSchedulingTask * Task );
void vfnScheduler_TaskActivate( tSchedulingTask * Task );
void general_init (void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint8_t gu8curr_state = TASK_STATE_A;
uint8_t gu8prev_state = TASK_STATE_F;

/*carlosa stae machine array*/
tSchedulingTask tasks_table[] = {
    /*TaskId*/       /*ptrTask*/     /*enTaskState*/
    {TASK_STATE_A,  p2f_state_a,    READY},
    {TASK_STATE_B,  p2f_state_b,    SUSPENDED},
    {TASK_STATE_C,  p2f_state_c,    SUSPENDED},
    {TASK_STATE_D,  p2f_state_d,    SUSPENDED},
    {TASK_STATE_E,  p2f_state_e,    SUSPENDED},
    {TASK_STATE_F,  p2f_state_f,    SUSPENDED}
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
* BOARD_SW_IRQ_HANDLER
* Button 3 interruption handler
* Activate next state according to the tSchedulerTasks_ID enum
* Activate the task of that state
 */
void BOARD_SW_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);

    gu8prev_state = gu8curr_state;

    if(gu8curr_state < TASK_STATE_F){
        gu8curr_state++;
    }
    else{
        gu8curr_state = TASK_STATE_A;
    }

    vfnScheduler_TaskActivate(&tasks_table[gu8curr_state]);

    SDK_ISR_EXIT_BARRIER;
}

/*
* BOARD_SW2_IRQ_HANDLER
* Button 2 interruption handler
* Activate last state according to the tSchedulerTasks_ID enum
 */
void BOARD_SW2_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);

    gu8prev_state = gu8curr_state;

    if(gu8curr_state > TASK_STATE_A){
        gu8curr_state--;
    }
    else{
        gu8curr_state = TASK_STATE_F;
    }

    vfnScheduler_TaskActivate(&tasks_table[gu8curr_state]);

    SDK_ISR_EXIT_BARRIER;
}


/*!
 * @brief Main function
 * carlosa calls the scheduler
 */
int main(void)
{

    general_init();

    PRINTF("carlosa \nscheduler FIFO. \nTotal task (%d)\n",TASK_MAX);

	for(;;)
    {
		vfnTask_Scheduler();
	}
}

/*
* vfnTask_Scheduler
* Linear check of tasks_table
* Call vfnScheduler_TaskStart for the first task within the state as READY
*/
void vfnTask_Scheduler (void){
    uint8_t lu8TaskToRun_Id = 0;
    bool lboolRunTask_Flag = 0;

    for(uint8_t lu8Task_Id = 0; lu8Task_Id<TASK_MAX; lu8Task_Id++){

        if (tasks_table[lu8Task_Id].enTaskState == READY){
            lboolRunTask_Flag = 1;
            lu8TaskToRun_Id = lu8Task_Id;
            break;
        }
    }

    if (lboolRunTask_Flag){
        vfnScheduler_TaskStart (&tasks_table[lu8TaskToRun_Id]);
    }
}

/*
* vfnScheduler_TaskStart
* Set task state to RUNNING
* Calls Task ptrTask
* Set task state to SUSPENDED
*/
void vfnScheduler_TaskStart( tSchedulingTask * Task )
{   
    Task->enTaskState = RUNNING;
    Task->ptrTask();
    Task->enTaskState = SUSPENDED;
}

/*
* vfnScheduler_TaskStart
* Set task state to READY
*/
void vfnScheduler_TaskActivate( tSchedulingTask * Task )
{
    Task->enTaskState = READY;
}

/*
* general_init
* initialize all before calling the scheduler
*/
void general_init (void){
    /* Define the init structure for the input switch pin */
    gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };
    /* Define the init structure for the output LED pin */
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    
	PORT_SetPinInterruptConfig(BOARD_SW_PORT, BOARD_SW_GPIO_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
	EnableIRQ(BOARD_SW_IRQ);
	EnableIRQ(BOARD_SW2_IRQ);

	GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);
	/*carlosa init input sw2 GPIO*/
	GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &sw_config);

	/* Init output LED GPIO. */
	GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
	/*carlosa to do: init output led gpio blue*/
	GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
	/*carlosa to do: init output led gpio green*/
	GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);
}
