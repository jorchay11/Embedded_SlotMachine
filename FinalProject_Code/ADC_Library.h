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
 *******************************************************************************/

#ifndef ADC_LIBRARY_H_
#define ADC_LIBRARY_H_

 /********************** PIN DESCRIPTIONS ****************************************
 *
 *          *********** Potentiometer ***************
 *                      P2.4 -> Pin 2
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
#include <stdint.h>

//7 Segment display
#define ZERO  0x77              //0x01110111
#define ONE   0x14              //0x00010100
#define TWO   0xB3              //0x10110001
#define THREE 0xB6              //0x10110110
#define FOUR  0xD4              //0x11010100
#define FIVE  0xE6              //0x11100110
#define SIX   0xC7              //0x11000111
#define SEVEN 0x34              //0x00110100
#define EIGHT 0xF7              //0x11110111
#define NINE  0xF4              //0x11110100


/********************* Function Prototypes *****************************
************************************************************************/
void sevenSegment_init(void);
void ADC_Reading(void);
void ADC_pin_init(void);
void ADC_init(void);
/********************* Function Prototypes *****************************
************************************************************************/

#endif /* ADC_LIBRARY_H_ */
