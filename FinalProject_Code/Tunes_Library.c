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
 ********************** PIN DESCRIPTIONS ****************************************
 *
 *          *********** Piezo Speaker ***************
 *                   P2.4 -> Speaker input pin
 *
 **********************************************************************************/

//Needs header block with descriptions of added functions, add function comment headers, comment and format throughout

#include "msp.h"
#include "Tunes_Library.h"
#include "SysTick_Library.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

uint8_t song = 3;      //Global variable for song selection

/// *****************| Speaker | ****************************
/// * Brief: Initializes timer A PWM for speaker, function
/// * inputs note and 2 for on and 0 for off.
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// ************************************************************/
void Speaker(int Note, uint8_t on){

    int freq = 3000000 / Note;

    P2->SEL0 |= BIT4;                               //Set TimerA
    P2->SEL1 = 0;
    P2->DIR |= BIT4;                                //Set P2.4 for OutPut

    TIMER_A0->CCR[0] = freq;                        //Period based off note input
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;     //CCR1 reset
    TIMER_A0->CCR[1] = freq / on;                   //PWM duty cycle
    TIMER_A0->CTL = 0x0214;                         //SMCLK, Up Mode, Clear TAR to start
  }

/// *****************| Pirates_C | ********************************
/// * Brief: Plays pirates of Caribbean theme song with variations
/// * of notes and delays. As well displays a matching LED sequence
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// *****************************************************************/
void Pirates_C(void){

        //FIRST PART
          Speaker(E_4, 2);
          P3->OUT |= BIT0;
          SysTick_delay_ms(125);
          Speaker(G_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT2;
          SysTick_delay_ms(125);
          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(250);
          Speaker(A_4,2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(B_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT3;
          SysTick_delay_ms(125);
          Speaker(C_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(250);
          Speaker(C_5,2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(C_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(125);
          Speaker(D_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(B_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT3;
          SysTick_delay_ms(250);
          Speaker(B_4,2);
          P3->OUT = 0;
          P3->OUT |= BIT3;
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(G_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT2;
          SysTick_delay_ms(125);
          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(375);
          Speaker(0,0);
          P3->OUT = 0;
          SysTick_delay_ms(125);
        //END OF PART 1

        //PART 2
          Speaker(E_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT0;
          SysTick_delay_ms(125);
          Speaker(G_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT2;
          SysTick_delay_ms(125);
          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(250);
          Speaker(A_4,2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(B_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT3;
          SysTick_delay_ms(125);
          Speaker(C_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(250);
          Speaker(C_5,2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(C_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(125);
          Speaker(D_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(B_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT3;
          SysTick_delay_ms(250);
          Speaker(B_4,2);
          P3->OUT = 0;
          P3->OUT |= BIT3;
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(G_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT2;
          SysTick_delay_ms(125);
          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(375);
          Speaker(0,0);
          P3->OUT = 0;
          SysTick_delay_ms(125);
        //END OF PART 2

        //PART 3
          Speaker(E_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT0;
          SysTick_delay_ms(125);
          Speaker(G_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT2;
          SysTick_delay_ms(125);
          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(250);
          Speaker(A_4,2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(C_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(125);
          Speaker(D_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(250);
          Speaker(D_5,2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(D_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(E_5, 2);
          P3->OUT = 0;
          P3->OUT |= BIT0;
          SysTick_delay_ms(125);
          Speaker(F_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT3);
          SysTick_delay_ms(250);
          Speaker(F_5,2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT3);
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(E_5, 2);
          P3->OUT = 0;
          P3->OUT |= BIT0;
          SysTick_delay_ms(125);
          Speaker(D_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(E_5, 2);
          P3->OUT = 0;
          P3->OUT |= BIT0;
          SysTick_delay_ms(125);
          Speaker(A_4,2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(250);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);
        //END OF PART 3

        //PART 4
          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(B_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT3;
          SysTick_delay_ms(125);
          Speaker(C_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(250);
          Speaker(C_5,2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(D_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(250);
          Speaker(E_5, 2);
          P3->OUT = 0;
          P3->OUT |= BIT0;
          SysTick_delay_ms(125);
          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(250);
          Speaker(0,0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(C_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(125);
          Speaker(B_4, 2);
          P3->OUT = 0;
          P3->OUT |= BIT3;
          SysTick_delay_ms(250);
          Speaker(B_4,2);
          P3->OUT = 0;
          P3->OUT |= BIT3;
          SysTick_delay_ms(125);
          Speaker(0, 0);
          P3->OUT = 0;
          SysTick_delay_ms(125);

          Speaker(C_5, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3);
          SysTick_delay_ms(125);
          Speaker(A_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(125);
          Speaker(B_4, 2);
          P3->OUT = 0;
          P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
          SysTick_delay_ms(375);
          Speaker(0,0);
          P3->OUT = 0;
          SysTick_delay_ms(1000);
          //END OF PART 4
}

/// *****************| Despacito | ********************************
/// * Brief: Plays song Despacito with variations of notes and delays,
/// * displays matching LED sequence.
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// *****************************************************************/
void Despacito(void){

    Speaker(D_5, 2);
    P3->OUT |= BIT0;                    //Blue
    SysTick_delay_ms(575);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(200);
    Speaker(C_S5, 2);
    P3->OUT |= BIT2;                    //Orange
    SysTick_delay_ms(575);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(200);
    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(290);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);
    Speaker(F_S4, 2);
    P3->OUT |= (BIT5 | BIT6 | BIT7);    //Reds
    SysTick_delay_ms(290);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);

    Speaker(F_S4, 2);
    P3->OUT |= (BIT5 | BIT6 | BIT7);    //Reds
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(F_S4, 2);
    P3->OUT |= (BIT5 | BIT6 | BIT7);    //Reds
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                         //Off
    SysTick_delay_ms(50);
    Speaker(F_S4, 2);
    P3->OUT |= (BIT5 | BIT6 | BIT7);    //Reds
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(F_S4, 2);
    P3->OUT |= (BIT5 | BIT6 | BIT7);    //Reds
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(F_S4, 2);
    P3->OUT |= (BIT5 | BIT6 | BIT7);    //Reds
    SysTick_delay_ms(145);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);

    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(290);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);

    Speaker(A_4, 2);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7); //All
    SysTick_delay_ms(145);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(290);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);
    Speaker(G_4, 2);
    P3->OUT |= (BIT0 | BIT7);           //Blue and Red
    SysTick_delay_ms(290);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);

    Speaker(G_4, 2);
    P3->OUT |= (BIT0 | BIT7);           //Blue and Red
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(G_4, 2);
    P3->OUT |= (BIT0 | BIT7);           //Blue and Red
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(G_4, 2);
    P3->OUT |= (BIT0 | BIT7);           //Blue and Red
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(G_4, 2);
    P3->OUT |= (BIT0 | BIT7);           //Blue and Red
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(G_4,2);
    P3->OUT |= (BIT0 | BIT7);           //Blue and Red
    SysTick_delay_ms(145);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);

    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(290);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);

    Speaker(C_S5, 2);
    P3->OUT |= BIT2;                    //Orange
    SysTick_delay_ms(145);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(D_5, 2);
    P3->OUT |= BIT0;                    //Blue
    SysTick_delay_ms(290);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);

    Speaker(A_4, 2);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7); //All
    SysTick_delay_ms(290);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);

    Speaker(A_4, 2);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7); //All
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(A_4, 2);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7); //All
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(A_4, 2);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7); //All
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(A_4, 2);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7); //All
    SysTick_delay_ms(145);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);

    Speaker(D_5, 2);
    P3->OUT |= BIT0;                    //Blue
    SysTick_delay_ms(145);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(C_S5, 2);
    P3->OUT |= BIT2;                    //Orange
    SysTick_delay_ms(145);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(D_5, 2);
    P3->OUT |= BIT0;                    //Blue
    SysTick_delay_ms(145);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(C_S5, 2);
    P3->OUT |= BIT2;                    //Orange
    SysTick_delay_ms(145);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);

    Speaker(D_5, 2);
    P3->OUT |= BIT0;                    //Blue
    SysTick_delay_ms(290);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);

    Speaker(E_5,2);
    P3->OUT |= (BIT3 | BIT5);           //Red and Yellow
    SysTick_delay_ms(145);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(50);
    Speaker(E_5, 2);
    P3->OUT |= (BIT3 | BIT5);           //Red and Yellow
    SysTick_delay_ms(290);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);
    Speaker(C_S5,2);
    P3->OUT |= BIT2;                    //Orange
    SysTick_delay_ms(575);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(400);

    Speaker(D_5, 2);
    P3->OUT |= BIT0;                    //Blue
    SysTick_delay_ms(575);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(200);
    Speaker(C_S5, 2);
    P3->OUT |= BIT2;                    //Orange
    SysTick_delay_ms(575);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(200);
    Speaker(B_4, 2);
    P3->OUT |= BIT3;                    //Yellow
    SysTick_delay_ms(290);
    Speaker(0,0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);
    Speaker(F_S4, 2);
    P3->OUT |= (BIT5 | BIT6 | BIT7);    //Reds
    SysTick_delay_ms(290);
    Speaker(0, 0);
    P3->OUT = 0;                        //Off
    SysTick_delay_ms(100);
}

/// *****************| Bells | ********************************
/// * Brief: Plays song loud bell sounding noise for wins by
/// * using for loop to time it and small delays for faster rate.
/// * Displays matching LED flashing.
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// *****************************************************************/
void Bells(void){

    int a;

    for(a = 0; a < 50; a ++){               //For loop allows for repeating

        P3->OUT = 0;                        //LEDs off
        P3->OUT |= (BIT5 | BIT6 | BIT7);    //Red LEDS on
        Speaker(D_5, 2);                    //Note frequency D_5 plays
        SysTick_delay_ms(50);               //Delays for 50ms

        P3 -> OUT = 0;                      //LEDs off
        P3->OUT |= (BIT0 | BIT2 | BIT3);    //Multi color LEDs on
        Speaker(C_5, 2);                    //Plays note frequency C_5
        SysTick_delay_ms(50);               //Delays 50ms
    }

        P3->OUT = 0;                        //After completion of for loop LEDs off
        Speaker(0,0);                       //Speaker off
}
