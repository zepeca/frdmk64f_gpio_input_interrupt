/*
*carlosa
*/

#ifndef _GPIO_INPUT_INTERRUPT_H_
#define _GPIO_INPUT_INTERRUPT_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

#define BOARD_SW_GPIO        BOARD_SW3_GPIO
#define BOARD_SW_PORT        BOARD_SW3_PORT
#define BOARD_SW_GPIO_PIN    BOARD_SW3_GPIO_PIN
#define BOARD_SW_IRQ         BOARD_SW3_IRQ
#define BOARD_SW_IRQ_HANDLER BOARD_SW3_IRQ_HANDLER
#define BOARD_SW_NAME        BOARD_SW3_NAME

#define MAX_PRIO             6

/*****************************************************************************************************
* Type def
*****************************************************************************************************/

typedef enum
{
    SUSPENDED,
    READY,
    RUNNING
}tTaskStates;

/* Task Scheduler Tasks IDs definitions */
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

/*******************************************************************************
 * extern var
 ******************************************************************************/

extern uint8_t gu8curr_state;
extern uint8_t gu8prev_state;

#endif /* _GPIO_INPUT_INTERRUPT_H_ */