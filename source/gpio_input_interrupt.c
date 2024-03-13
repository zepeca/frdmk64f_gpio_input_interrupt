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
#include "scheduler.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void general_init (void);
void SysTick_Handler(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
* calls vfnTask_Scheduler_Cbk
 */
void SysTick_Handler(){
    vfnTask_Scheduler_Cbk();
}

#ifdef BOTON_ENABLE
/*
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

    /*carlosa always activating task g for testing priority functionality*/
    vfnScheduler_TaskActivate(&tasks_table[TASK_STATE_G]);
    SDK_ISR_EXIT_BARRIER;
}

/*
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

    vfnScheduler_TaskActivate(&tasks_table[TASK_STATE_G]);

    SDK_ISR_EXIT_BARRIER;
}
#endif/*BOTON_ENABLE*/


/*!
 * @brief Main function
 * carlosa calls the scheduler
 */
int main(void)
{

    general_init();

    //to do call after creating the tasks
    PRINTF("carlosa \nscheduler \nTotal task (%d)\n",TASK_MAX);

	for(;;)
    {
		vfnTask_Scheduler();
	}
}

/*
* init function called in main
*/
void general_init (void){

#ifdef BOTON_ENABLE
    /* Define the init structure for the input switch pin */
    gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };
#endif /*BOTON_ENABLE*/

#ifdef LED_ENABLE
    /* Define the init structure for the output LED pin */
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
#endif /*LED_ENABLE*/

#ifdef BOTON_ENABLE    
	PORT_SetPinInterruptConfig(BOARD_SW_PORT, BOARD_SW_GPIO_PIN, kPORT_InterruptFallingEdge);
	PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
	EnableIRQ(BOARD_SW_IRQ);
	EnableIRQ(BOARD_SW2_IRQ);

	GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);
	/*carlosa init input sw2 GPIO*/
	GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &sw_config);
#endif /*BOTON_ENABLE*/

#ifdef LED_ENABLE
	/* Init output LED GPIO. */
	GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
	/*carlosa to do: init output led gpio blue*/
	GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
	/*carlosa to do: init output led gpio green*/
	GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);
#endif /*LED_ENABLE*/

	/*scheduler init*/
	vfnTask_Scheduler_Init();
}
