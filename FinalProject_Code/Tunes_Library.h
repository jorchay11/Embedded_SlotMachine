/***************************************************************************
 ***************************************************************************
 *                       Tunes_Library.c
 *             Joshua Johnston and Jordan Hayes
 *                          EGR226
 *            Instructor: Dr. Nabeeh Kandalaft
 *               Created on: April 4, 2019
 *
 *       For use with the MSP432 LaunchPad Development Board
 *
 * Library is used for songs created with PWM from Timer A.
 * LEDs Initialized in SysTick_Library.c and used throughout for effect.
 *
 * The /// notation makes it so the function description block
 * is visible when you hovering over a function call in any
 * file (this feature is called Intellisense).
 *
 * Functions are each briefly described in comment blocks
 * Functions are commented out throughout program
 * Pin descriptions are listed below
 ****************************************************************************/

#ifndef TUNES_LIBRARY_H_
#define TUNES_LIBRARY_H_

/*********************** PIN DESCRIPTIONS ****************************************
 *
 *          *********** Piezo Speaker ***************
 *                   P2.4 -> Speaker input pin
 *
 **********************************************************************************/

#include "msp.h"
#include <stdint.h>

//Note frequencies
#define A_2     110
#define A_S2    117
#define B_2     123
#define C_3     131
#define C_S3    139
#define D_3     147
#define D_S3    156
#define E_3     165
#define F_3     175
#define F_S3    185
#define G_3     196
#define G_S3    208
#define A_3     220
#define A_S3    233
#define B_3     247
#define C_4     262
#define C_S4    277
#define D_4     294
#define D_S4    311
#define E_4     330
#define F_4     349
#define F_S4    370
#define G_4     392
#define G_S4    415
#define A_4     440
#define A_S4    466
#define B_4     494
#define C_5     523
#define C_S5    554
#define D_5     587
#define D_S5    622
#define E_5     659
#define F_5     698
#define F_S5    740
#define G_5     784
#define G_S5    831
#define A_5     880
#define A_S5    932
#define B_5     988


extern uint8_t song;

/********************* Function Prototypes *****************************
************************************************************************/
void Speaker(int Note, uint8_t on);
void Pirates_C(void);
void Despacito(void);
void Bells(void);
/********************* Function Prototypes *****************************
************************************************************************/

#endif /* TUNES_LIBRARY_H_ */
