/*************************************************************
 *Filename: EGR226Sec901_Johnston_Hayes_Final_Project.c
 *Title: Slot Machine
 *Author: Josh Johnston and Jordan Hayes
 *Date: 04/16/2019
 *Instructor: Dr. Nabeeh Kandalaft
 *Description: Program contains custom libraries that
 *operates buttons, a keypad, 16 x 4 LCD display, LEDs,
 *7 - Segment display, ADC conversions, and a piezo speaker.
 *All combined to make a user friendly functional slot machine.
 *
 *Libraries include:
 *  Slot_Machine.h
 *  LCD_Library.h
 *  SysTick_Library.h
 *  ADC_Library.h
 *  Tunes_Library.h
****************************************************************/
#include "msp.h"
#include <stdio.h>
#include "Slot_Machine.h"
#include "LCD_Library.h"
#include "SysTick_Library.h"
#include "ADC_Library.h"
#include "Tunes_Library.h"
#include <time.h>

 void main(void){

/********************* Function Initializations *************************
************************************************************************/
   lcdInit();
   Intro_Screen();
   Menu_Screen();
   SysTick_delay_us(10);
   SysTickInit_NoInterrupts();
   KeyPad_Init();
   Buttons_init();
   LED_init();
   Character_init();
   ADC_pin_init();
   sevenSegment_init();
   ADC_init();
   Servo();

   TIMER32_2->CONTROL = 0b11100011;
   NVIC_EnableIRQ(PORT1_IRQn);
   NVIC_EnableIRQ(PORT5_IRQn);
   NVIC_EnableIRQ(PORT6_IRQn);
   _enable_IRQ();
/********************* Function Initializations *************************
************************************************************************/

   WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    while(1)
    {

        Menu_Options();         //Menu selections
        Sounds_Options();       //Sound selections
        Credits_Input();        //Credits menu to input desired credits from 0 - 999
        Spin_and_Play();        //To go into the play function that spins reels and gives win outcome
        Cash_Out();             //Allows for cash out at any time
        Home_Option();          //Option to return to the menu screen with the * key
        ADC_Reading();          //Does ADC conversion for the 7 - segment display from potentiometer readings

    }
}

