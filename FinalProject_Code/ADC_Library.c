/***************************************************************************
 ***************************************************************************
 *                       ADC_Library.c
 *             Joshua Johnston and Jordan Hayes
 *                          EGR226
 *            Instructor: Dr. Nabeeh Kandalaft
 *               Created on: March 26, 2019
 *
 *       For use with the MSP432 LaunchPad Development Board
 *
 * Library is used for ADC conversion with 7 Segment Display and potentiometer
 *
 * The /// notation makes it so the function description block
 * is visible when you hovering over a function call in any
 * file (this feature is called Intellisense).
 *
 * Functions are each briefly described in comment blocks
 * Functions are commented out throughout program
 * Pin descriptions are listed below
 ********************** PIN DESCRIPTIONS ****************************************
 *
 *          *********** Potentiometer ***************
 *                      P5.0 -> Pin 2
 *                     V0 LCD -> Pin 2
 *
 *          ********** 7 SEGMENT DISPLAY ************
 *                      P7.0 -> Pin 1
 *                      P7.1 -> Pin 2
 *                      P7.2 -> Pin 4
 *                      P7.3 -> Pin 5
 *                      P7.4 -> Pin 6
 *                      P7.5 -> Pin 7
 *                      P7.6 -> Pin 9
 *                      P7.7 -> Pin 10
 *
 **********************************************************************************/

#include "msp.h"
#include "SysTick_Library.h"
#include "ADC_Library.h"
#include <stdio.h>
#include <stdint.h>

/// *****************| sevenSegment_init | **********************
/// * Brief: Initializes all four buttons: BetUp, BetDown, Spin
/// *         and CashOut as input port interrupts
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// ************************************************************/
void sevenSegment_init(void) {

    P7 -> SEL0 = 0;
    P7 -> SEL1 = 0;
    P7 -> DIR |= (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7);
    P7 -> OUT = 0;
}

/// *****************| ADC_pin_init | **********************
/// * Brief: Initializes P5.0 for ADC
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// ************************************************************/
void ADC_pin_init(void) {

    P5->SEL0 |= BIT0;   //Set P5.0 for ADC
    P5-> SEL0 |= BIT0;
}

/// *****************| ADC_init | **********************
/// * Brief: Initializes ADC
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// ************************************************************/
void ADC_init(void) {

    ADC14-> CTL0 &= ~ADC14_CTL0_ENC;    //disable, no conversions runnning
    ADC14-> CTL0 |= 0x04200210;         //creates the ADC using SMCLK, 1 turns it on, 2 sec cycle
    ADC14-> CTL1 = 0x00000030;          //14 bit resolution
    ADC14-> CTL1 |= 0x0000000;
    ADC14-> MCTL[0] =0x05;
    ADC14-> CTL0 |= ADC14_CTL0_ENC;     //enable, start conversion
}

/// *****************| ADC_Reading | **********************
/// * Brief: Takes in ADC raw value converts it to voltage
/// * and displays numbers 0 - 9 on 7 - Segment display
/// * based on voltage conditions.
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// ************************************************************/
void ADC_Reading(void) {

    static volatile uint16_t result;
    float V;

    ADC14->CTL0 |= ADC14_CTL0_SC;

    while(!ADC14->IFGR0 & BIT0);       //wait until conversion is finished

    result = ADC14 -> MEM[0];          //result equals converted value
    V = ((result * 5.0) / 16384);      //Voltage conversion from raw ADC readings

    if(V <= .5) {
       P7 -> OUT = 0;
       P7 -> OUT |= NINE;              //Displays defined 9 on 7 - Segment display
       SysTick_delay_ms(100);
    }

    if(V > .5 && V <= 1.0) {
       P7 -> OUT = 0;
       P7 -> OUT |= EIGHT;             //Displays defined 8 on 7 - Segment display
       SysTick_delay_ms(100);
    }

    if(V >1.0 && V <= 1.5) {
       P7 -> OUT = 0;
       P7 -> OUT |= SEVEN;             //Displays defined 7 on 7 - Segment display
       SysTick_delay_ms(100);
    }

    if(V > 1.5 && V <= 2.0) {
       P7 -> OUT = 0;
       P7 -> OUT |= SIX;               //Displays defined 6 on 7 - Segment display
       SysTick_delay_ms(100);
    }

    if(V > 2.0 && V <= 2.5) {
       P7 -> OUT = 0;
       P7 -> OUT |= FIVE;              //Displays defined 5 on 7 - Segment display
       SysTick_delay_ms(100);
    }

    if(V > 2.5 && V <= 3.0) {
       P7 -> OUT = 0;
       P7 -> OUT |= FOUR;              //Displays defined 4 on 7 - Segment display
       SysTick_delay_ms(100);
    }

    if(V > 3.0 && V <= 3.5) {
       P7 -> OUT = 0;
       P7 -> OUT |= THREE;             //Displays defined 3 on 7 - Segment display
       SysTick_delay_ms(100);
    }

    if(V > 3.5 && V <= 4.0) {
       P7 -> OUT = 0;
       P7 -> OUT |= TWO;               //Displays defined 2 on 7 - Segment display
       SysTick_delay_ms(100);
    }

    if(V > 4.0 && V <= 4.5) {
       P7 -> OUT = 0;
       P7 -> OUT |= ONE;               //Displays defined 1 on 7 - Segment display
       SysTick_delay_ms(100);
    }

    if(V > 4.5) {
       P7 -> OUT = 0;
       P7 -> OUT |= ZERO;              //Displays defined 0 on 7 - Segment display
       SysTick_delay_ms(100);
    }
}
