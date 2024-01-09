/***************************************************************************
 ***************************************************************************
 *                       Slot_Machine.c
 *             Joshua Johnston and Jordan Hayes
 *                          EGR226
 *            Instructor: Dr. Nabeeh Kandalaft
 *               Created on: March 26, 2019
 *
 *       For use with the MSP432 LaunchPad Development Board
 *
 * Library is used for a custom slot machine gives functions
 * and provides menu screens and functionality for
 * user friendly game play
 *
 * The /// notation makes it so the function description block
 * is visible when you hovering over a function call in any
 * file (this feature is called Intellisense).
 *
 * Functions are each briefly described in comment blocks
 * Functions are commented out throughout program
 * Devices used and pin descriptions are listed below
 *
 * Libraries needed for initializations and other screen functionalities
 *                      LCD_library.h
 *                      SysTick_Library.h
 *
 ********************** DEVICES AND PARTS **********************************
 * 16 x 4 HHD44780 LCD DISPLAY
 * STANDARD 12 KEY KEYPAD
 * 4 MOMENTARY PUSH BUTTONS
 * 6 LEDs
 * 7 SEGMENT DISPLAY
 * AUDIO SPEAKER
 *
 * Reference Pin Description Below
 *****************************************************************************/

#ifndef SLOT_MACHINE_H_
#define SLOT_MACHINE_H_

/********************** PIN DESCRIPTIONS **********************************
 *
 *            ********* 16 X 4 LCD DISPLAY *********
 *                       P4.0 -> LCD D4
 *                       P4.1 -> LCD D5
 *                       P4.2 -> LCD D6
 *                       P4.3 -> LCD D7
 *                       P4.4 -> LCD E
 *                       P4.5 -> LCD RS
 *
 *           ******* STANDARD 12 KEY KEYPAD *******
 *                       P5.4 -> ROW 0
 *                       P5.5 -> ROW 1
 *                       P5.6 -> ROW 2
 *                       P5.7 -> ROW 3
 *                       P2.5 -> COL 0
 *                       P2.6 -> COL 1
 *                       P2.7 -> COL 2
 *
 *          ************ PUSH BUTTONS *************
 *                       P1.5 -> SPIN
 *                       P1.6 -> BET-UP
 *                       P1.7 -> BET-DOWN
 *                       P6.0 -> CASHOUT
 *
 *          **************  LEDS  ******************
 *                        (WIN LEDS)
 *                       P3.0 -> BLUE LED
 *                       P3.2 -> ORANGE LED
 *                       P3.3 -> YELLOW LED
 *                        (LOSE LEDS)
 *                       P3.5 -> RED LED
 *                       P3.6 -> RED LED
 *                       P3.7 -> RED LED
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
 *          *********** AUDIO SPEAKER ************
 *                      P2.4 -> PWM Pin
 *
 ************************************************************************/

/*************Global Variables Used Throughout Libraries****************
************************************************************************/
extern uint8_t i, n, x, j;
extern int Credits;
extern int one, two, three;
extern uint8_t play;
/*************Global Variables Used Throughout Libraries****************
************************************************************************/

/********************* Function Prototypes *****************************
************************************************************************/
void Menu_Screen(void);
void Intro_Screen(void);
void Menu_Options(void);
void Sounds_Options(void);
void Credits_Input(void);
void Bet_Input(void);
void Home_Option(void);
void Play_Game(void);
void Lose_Lights(void);
void Cash_Out(void);
void Cash_Out_Lights(void);
void Spin_and_Play(void);
void Servo(void);
/********************* Function Prototypes *****************************
************************************************************************/

#endif /* SLOT_MACHINE_H_ */
