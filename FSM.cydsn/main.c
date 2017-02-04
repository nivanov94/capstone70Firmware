/*******************************************************************************
* File Name: main.c
*
* Version: 3.00
*
* Description:
*  This is the source code for the datasheet example of the TCPWM (Timer / 
*  Counter mode) component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>
#include <stdlib.h>

#include "filter.h"
#include "print.h"
#include "queue.h"
#include "PWM.h"
#include "IDAC.h"
#include "adc.h"
#include "PGA.h"

/* LED control defines (active low)*/
#define LIGHT_OFF                       (1u)
#define LIGHT_ON                        (0u)
#define SIZE 2000U

#define LOW_FILT  0
#define MID_FILT  1
#define HIGH_FILT 2

#define MIC_GAIN 68/2.2

/* Selects the active blinking LED */
uint8 activeLed;
// Flag to indicate when to sample digital lines.
uint8 sample_lines;


/*******************************************************************************
* Defines the interrupt service routine and allocates a vector to the interrupt.
* We use one handler for both the Capture and Terminal Count interrupts
* We toggle the active LED upon each Terminal Count interrupt
* We toggle the color (active LED) between blue and green upon each Capture 
* interrupt
********************************************************************************/

CY_ISR(InterruptHandler)
{    
    if (Timer_INTR_MASK_TC == Timer_GetInterruptSource()) {
        // Timer has overflowed, 1ms has elapsed.
        // Clear interrupt, then set flag to execute finite state control loop.
        Timer_ClearInterrupt(Timer_INTR_MASK_TC);
        sample_lines = 1;        
    }
    
    
}



int main()
{   
    #if (CY_PSOC4_4000)
        CySysWdtDisable();
    #endif /* (CY_PSOC4_4000) */
       
    motor_Write(0);
    /* Enable global interrupt */
    CyGlobalIntEnable;
    
    UART_1_Start();
    
    PGA_set_gain(MIC_GAIN);
    
    /*enable ADC, PWM, and IDAC for threshold initialization */
    init_PWM();
    init_IDAC();
    ADC_init();
    
    /*set comparator thresholds*/
    CyDelay(5);
    set_PWM_threshold(LOW_FILT);
    set_PWM_threshold(MID_FILT);
    set_PWM_threshold(HIGH_FILT);
    set_IDAC_threshold();
    
    /*put ADC to sleep*/
    ADC_sleep();
    
    
    /* Enable interrupt component connected to interrupt */
    TC_CC_ISR_StartEx(InterruptHandler);

    /* Start sampling timer */
    Timer_Start();
    
    
    
    
    // The state of the FSM.
    uint8 state = 0;
    
    

    UART_1_UartPutString("\r\nTest Line\r\n");
    print_int(123);
    UART_1_UartPutString("\r\n");
    print_int(12);
    UART_1_UartPutString("\r\n");
    print_int(100);
    UART_1_UartPutString("\r\n");
    print_int(1901);
    UART_1_UartPutString("\r\n");
    print_int(0);
    UART_1_UartPutString("\r\n");
    
    queue_t low_prev;
    queue_t med_prev;
    queue_t high_prev;
    queue_t fire_prev;
    queue_t slope_detect;
    
    int low_count;
    int med_count;
    int high_count;
    int fire_count;
    int liveness_count;
    int prev_low_count;
    
    
    //int i = 0;
    
    init_queue(&low_prev);
    init_queue(&med_prev);
    init_queue(&high_prev);
    init_queue(&fire_prev);
    init_queue(&slope_detect);
    
    for(;;) {
        if (sample_lines) {
            sample_lines = 0;
            
            switch(state) {
                
                /* This is the state that is entered upon reset.
                 * In the future, this state should be returned to upon 
                 * event detection if the user applies an input (possibly a
                 * pushbutton to start with, and a BLE signal in the future).
                 */
                case 0:
                    low_count = 0;
                    med_count = 0;
                    high_count = 0;
                    fire_count = 0;
                    LED_GREEN_Write(LIGHT_OFF);
                    LED_BLUE_Write(LIGHT_OFF);
                    LED_RED_Write(LIGHT_OFF);
                    state = 1;
                    break;
                
                /* In this state, keep a running count of each filtered input.
                 * If the counts exceed certain thresholds, proceed to either the
                 * alarm recognition state or the siren recognition state.
                 */
                // TODO break up count into helper functions, make new header file.
                case 1:
                    prev_low_count = low_count;
                    low_count = filter_count(LOW_FILTER_INPUT_Read(), &low_prev, low_count);
                    med_count = filter_count(MED_FILTER_INPUT_Read(), &med_prev, med_count);
                    high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count);
                    fire_count = filter_count(FIRE_FILTER_INPUT_Read(), &fire_prev, fire_count);
                    push(&slope_detect, low_count - prev_low_count);
                    
                    if ((sum(&slope_detect) == 0) && (peek(&slope_detect) != 0)) {
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                        prev_low_count = 0;
                    }
                    
                    UART_1_UartPutString("S1 ");
                    UART_1_UartPutString(" ");
                    print_int(low_count);
                    UART_1_UartPutString(" ");
                    print_int(med_count);
                    UART_1_UartPutString(" ");
                    print_int(high_count);
                    UART_1_UartPutString(" ");
                    print_int(fire_count);
                    //UART_1_UartPutString("SD: ");
                    //print_int(sum(&slope_detect));
                    //UART_1_UartPutString(" ");
                    //print_int(peek(&slope_detect));
                    UART_1_UartPutString("\r\n");             
                    
                    /* Check for fire alarm threshold. */
                    if (fire_count > 100) {
                        state = 5;
                        liveness_count = 0;
                        init_queue(&slope_detect);
                        LED_RED_Write(LIGHT_ON);
                    }
                    
                    /* Check for siren threshold. */
                    else if ((low_count > 50) && (med_count > 5) && (high_count < 5)) {
                        state = 2;
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                        fire_count = 0;
                        liveness_count = 0;
                        init_queue(&slope_detect);
                        LED_BLUE_Write(LIGHT_ON);
                                                
                        motor_Write(1);
                        CyDelay(5000);
                        motor_Write(0);
                    }
                    
                    break;
                
                /* In this state, check to see if the medium frequency range has been
                 * captured. If the signal remains too low for too long, return back to the 
                 * initial stage.
                 */
                case 2:
                    liveness_count++;
                    low_count = filter_count(LOW_FILTER_INPUT_Read(), &low_prev, low_count);
                    med_count = filter_count(MED_FILTER_INPUT_Read(), &med_prev, med_count);
                    high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count); 
                    UART_1_UartPutString("S2 ");
                    print_int(low_count);
                    UART_1_UartPutString(" ");
                    print_int(med_count);
                    UART_1_UartPutString(" ");
                    print_int(high_count);
                    UART_1_UartPutString(" ");
                    print_int(fire_count);
                    UART_1_UartPutString(" ");
                    print_int(liveness_count);
                    UART_1_UartPutString("\r\n");
                    
                    if (liveness_count > 120) {
                        state = 0;
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                        fire_count = 0;
                        liveness_count = 0;                        
                        LED_BLUE_Write(LIGHT_OFF);
                    }
                    else if ((low_count < 50) && (med_count > 50) && (high_count > 5)) {
                        state = 3;
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                        fire_count = 0;
                        liveness_count = 0;
                    }                                            
                    break;
                    
                case 3:
                    liveness_count++;
                    low_count = filter_count(LOW_FILTER_INPUT_Read(), &low_prev, low_count);
                    med_count = filter_count(MED_FILTER_INPUT_Read(), &med_prev, med_count);
                    high_count = filter_count(HIGH_FILTER_INPUT_Read(), &high_prev, high_count);
                    
                    UART_1_UartPutString("S3 ");
                    print_int(low_count);
                    UART_1_UartPutString(" ");
                    print_int(med_count);
                    UART_1_UartPutString(" ");
                    print_int(high_count);
                    UART_1_UartPutString(" ");
                    print_int(fire_count);
                    UART_1_UartPutString(" ");
                    print_int(liveness_count);
                    UART_1_UartPutString("\r\n");
                    
                    if (liveness_count > 140) {
                        state = 0;
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                        fire_count = 0;
                        liveness_count = 0;
                        LED_BLUE_Write(LIGHT_OFF);
                    }
                    else if ((low_count < 10) && (med_count < 30) && (high_count > 50)) {
                        state = 4;
                        low_count = 0;
                        med_count = 0;
                        high_count = 0;
                        fire_count = 0;
                        liveness_count = 0;
                        LED_BLUE_Write(LIGHT_OFF);
                        LED_GREEN_Write(LIGHT_ON);
                        UART_1_UartPutString("Siren Detected\r\n");
                    }
                    break;
                /* Wait for user input to reset state machine. */
                case 4:
                    while(USER_INPUT_Read());
                    while(!USER_INPUT_Read());
                    state = 0;
                    LED_GREEN_Write(LIGHT_OFF);
                    break;
                    
                /* In this state, begin detection of the fire alarm.
                 */
                case 5:
                    UART_1_UartPutString("Fire Alarm Detected\r\n");
                    LED_RED_Write(LIGHT_ON);
                    while(USER_INPUT_Read());
                    while(!USER_INPUT_Read());
                    LED_RED_Write(LIGHT_OFF);
                    state = 0;                   
                    break;
                    
                /* In this state, wait until user input to reset the
                 * FSM.
                 */
                case 6:
                    break;
                    
                default:
                    break;
            }        
        }
    }
    
    return 1;
}




/* [] END OF FILE */
