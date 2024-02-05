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

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*zepeca6 states prototype functions*/
void p2f_state_a (void);
void p2f_state_b (void);
void p2f_state_c (void);
void p2f_state_d (void);
void p2f_state_e (void);
void p2f_state_f (void);

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

/*******************************************************************************
 * Typedefs
 ******************************************************************************/

/*zepeca6 state enum*/
typedef enum {
    state_a,
    state_b,
    state_c,
    state_d,
    state_e,
    state_f,
    total_states
} state_type;

/*zepeca6 type machine struct*/
typedef struct {
    state_type state;
    void(*p2f_state)(void);
} machine_struct;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Whether the SW button is pressed */
volatile bool g_ButtonPress = false;

/* zepeca6 SW 2 is pressed is pressed */
volatile bool g_ButtonPress_switch2 = false;

/*zepeca6 stae machine array*/
machine_struct state_machine_table[] = {
    /*state*/   /*p2funct*/
    {state_a,   p2f_state_a},
    {state_b,   p2f_state_b},
    {state_c,   p2f_state_c},
    {state_d,   p2f_state_d},
    {state_e,   p2f_state_e},
    {state_f,   p2f_state_f}
};

/*zepeca6 current state variable*/
state_type current_state = state_a;
state_type previous_state = state_f;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Interrupt service fuction of switch.
 *
 * This function toggles the LED
 */
void BOARD_SW_IRQ_HANDLER(void)
{
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
    /* Clear external interrupt flag. */
    GPIO_GpioClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
#else
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
#endif
    /* Change state of button. */
    g_ButtonPress = true;
    SDK_ISR_EXIT_BARRIER;
}

/*zepeca interrupt function*/
void BOARD_SW2_IRQ_HANDLER(void)
{
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
    /* Clear external interrupt flag. */
    GPIO_GpioClearInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);
#else
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW2_GPIO, 1U << BOARD_SW2_GPIO_PIN);
#endif
    /* Change state of button. */
    g_ButtonPress_switch2 = true;
    SDK_ISR_EXIT_BARRIER;
}


/*!
 * @brief Main function
 */
int main(void)
{

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

    /* Print a note to terminal. */
    //PRINTF("\r\n GPIO Driver example\r\n");
    //PRINTF("\r\n Press %s to turn on/off a LED \r\n", BOARD_SW_NAME);

    PRINTF("\r\n STATE MACHINE, CARLOS ZEPEDA \r\n");
    PRINTF("\r\n total number of states is %d\r\n", total_states);

/* Init input switch GPIO. */
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
	GPIO_SetPinInterruptConfig(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, kGPIO_InterruptFallingEdge);
    GPIO_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kGPIO_InterruptFallingEdge);
#else
	PORT_SetPinInterruptConfig(BOARD_SW_PORT, BOARD_SW_GPIO_PIN, kPORT_InterruptFallingEdge);
	/* zepeca6 init input switch 2 GPIO. */
	PORT_SetPinInterruptConfig(BOARD_SW2_PORT, BOARD_SW2_GPIO_PIN, kPORT_InterruptFallingEdge);
#endif
	EnableIRQ(BOARD_SW_IRQ);
	/*zepeca6 enable IRQ of switch 2*/
	EnableIRQ(BOARD_SW2_IRQ);

	GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);
	/*zepeca6 init input sw2 GPIO*/
	GPIO_PinInit(BOARD_SW2_GPIO, BOARD_SW2_GPIO_PIN, &sw_config);

	/* Init output LED GPIO. */
	GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
	/*zepeca6 to do: init output led gpio blue*/
	GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
	/*zepeca6 to do: init output led gpio green*/
	GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);

    while (1)
    {
		/*zepeca6 state machine main run*/
		if (current_state < total_states){
			(*state_machine_table[current_state].p2f_state)();
		}
		else{
			/*nothing*/
		}
    }
}

/*zepeca6 state functions*/
void p2f_state_a( void){

    /*check if comming from another state*/
    if(previous_state == current_state){
        /*nothing*/
    }
    else{
        PRINTF("\r\n entering state %d from state %d \r\n", current_state, previous_state);
        
        LED_RED_ON();
	    LED_BLUE_OFF();
	    LED_GREEN_OFF();
        
        /*updating previous state*/
        previous_state = current_state;
    }

    /*add 1 to the current state*/
     if (g_ButtonPress && !g_ButtonPress_switch2)
    {
    	current_state = state_b;
        g_ButtonPress = false;
    }

    /*susbtract 1 to the current state*/
    if (g_ButtonPress_switch2 && !g_ButtonPress)
    {
    	current_state = state_f;
        g_ButtonPress_switch2 = false;
    }
}

void p2f_state_b( void){

    /*check if comming from another state*/
    if(previous_state == current_state){
        /*nothing*/
    }
    else{
        PRINTF("\r\n entering state %d from state %d \r\n", current_state, previous_state);
        
        LED_RED_OFF();
	    LED_BLUE_ON();
	    LED_GREEN_OFF();

        /*updating previous state*/
        previous_state = current_state;
    }

    /*add 1 to the current state*/
     if (g_ButtonPress && !g_ButtonPress_switch2)
    {
    	current_state = state_c;
        g_ButtonPress = false;
    }

    /*susbtract 1 to the current state*/
    if (g_ButtonPress_switch2 && !g_ButtonPress)
    {
    	current_state = state_a;
        g_ButtonPress_switch2 = false;
    }
}

void p2f_state_c( void){

    /*check if comming from another state*/
    if(previous_state == current_state){
        /*nothing*/
    }
    else{
        PRINTF("\r\n entering state %d from state %d \r\n", current_state, previous_state);
        
        LED_RED_OFF();
	    LED_BLUE_OFF();
	    LED_GREEN_ON();

        /*updating previous state*/
        previous_state = current_state;
    }

    /*add 1 to the current state*/
     if (g_ButtonPress && !g_ButtonPress_switch2)
    {
    	current_state = state_d;
        g_ButtonPress = false;
    }

    /*susbtract 1 to the current state*/
    if (g_ButtonPress_switch2 && !g_ButtonPress)
    {
    	current_state = state_b;
        g_ButtonPress_switch2 = false;
    }
}

void p2f_state_d( void){

    /*check if comming from another state*/
    if(previous_state == current_state){
        /*nothing*/
    }
    else{
        PRINTF("\r\n entering state %d from state %d \r\n", current_state, previous_state);
        
        LED_RED_ON();
	    LED_BLUE_ON();
	    LED_GREEN_OFF();

        /*updating previous state*/
        previous_state = current_state;
    }

    /*add 1 to the current state*/
     if (g_ButtonPress && !g_ButtonPress_switch2)
    {
    	current_state = state_e;
        g_ButtonPress = false;
    }

    /*susbtract 1 to the current state*/
    if (g_ButtonPress_switch2 && !g_ButtonPress)
    {
    	current_state = state_c;
        g_ButtonPress_switch2 = false;
    }
}

void p2f_state_e( void){

    /*check if comming from another state*/
    if(previous_state == current_state){
        /*nothing*/
    }
    else{
        PRINTF("\r\n entering state %d from state %d \r\n", current_state, previous_state);
        
        LED_RED_OFF();
	    LED_BLUE_ON();
	    LED_GREEN_ON();

        /*updating previous state*/
        previous_state = current_state;
    }

    /*add 1 to the current state*/
     if (g_ButtonPress && !g_ButtonPress_switch2)
    {
    	current_state = state_f;
        g_ButtonPress = false;
    }

    /*susbtract 1 to the current state*/
    if (g_ButtonPress_switch2 && !g_ButtonPress)
    {
    	current_state = state_d;
        g_ButtonPress_switch2 = false;
    }
}

void p2f_state_f( void){

    /*check if comming from another state*/
    if(previous_state == current_state){
        /*nothing*/
    }
    else{
        PRINTF("\r\n entering state %d from state %d \r\n", current_state, previous_state);
        
        LED_RED_ON();
	    LED_BLUE_ON();
	    LED_GREEN_ON();

        /*updating previous state*/
        previous_state = current_state;
    }

    /*add 1 to the current state*/
     if (g_ButtonPress && !g_ButtonPress_switch2)
    {
    	current_state = state_a;
        g_ButtonPress = false;
    }

    /*susbtract 1 to the current state*/
    if (g_ButtonPress_switch2 && !g_ButtonPress)
    {
    	current_state = state_e;
        g_ButtonPress_switch2 = false;
    }
}
