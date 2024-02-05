/*
* carlosa
* Here are declared the task functions
*/

#include "task_app.h"
#include "board.h"
#include "gpio_input_interrupt.h"
#include "fsl_debug_console.h"
#include "stdint.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void task_general_function(uint8_t led_config);

/*******************************************************************************
 * code
 ******************************************************************************/

void p2f_state_a(void){
    if (gu8curr_state == gu8prev_state){
        /*during*/
    }
    else{
        /*entry*/
        task_general_function(RED_BIT);
    }
}

void p2f_state_b(void){
    if (gu8curr_state == gu8prev_state){
        /*during*/
    }
    else{
        /*entry*/
        task_general_function(BLUE_BIT);
    }
}

void p2f_state_c(void){
    if (gu8curr_state == gu8prev_state){
        /*during*/
    }
    else{
        /*entry*/
        task_general_function(GREEN_BIT);
    }
}

void p2f_state_d(void){
    if (gu8curr_state == gu8prev_state){
        /*during*/
    }
    else{
        /*entry*/
        task_general_function(PURPRLE_BIT);
    }
}

void p2f_state_e(void){
    if (gu8curr_state == gu8prev_state){
        /*during*/
    }
    else{
        /*entry*/
        task_general_function(TORQUOISE_BIT);
    }
}

void p2f_state_f(void){
    if (gu8curr_state == gu8prev_state){
        /*during*/
    }
    else{
        /*entry*/
        task_general_function(WHITE_BIT);
    }
}

void task_general_function(uint8_t led_config){
    PRINTF("Entering sate (%d) from state (%d)\n", gu8curr_state, gu8prev_state);
    if (led_config & RED_BIT){
        LED_RED_ON();
    }
    else{
        LED_RED_OFF();
    }

        if (led_config & BLUE_BIT){
        LED_BLUE_ON();
    }
    else{
        LED_BLUE_OFF();
    }

        if (led_config & GREEN_BIT){
        LED_GREEN_ON();
    }
    else{
        LED_GREEN_OFF();
    }
}
