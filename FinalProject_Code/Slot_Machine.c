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
 * For more information reference the wiring schematic
 *
 ********************** PIN DESCRIPTIONS **********************************
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
 *                       (WIN LEDS)
 *                      P3.0 -> BLUE LED
 *                      P3.2 -> ORANGE LED
 *                      P3.3 -> YELLOW LED
 *                       (LOSE LEDS)
 *                      P3.5 -> RED LED
 *                      P3.6 -> RED LED
 *                      P3.7 -> RED LED
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
 *          ************ SERVO MOTOR *************
 *                      P8.2 -> INPUT Pin
 *
 ************************************************************************/

//Formatting and commenting completed finish sounds menu

#include "SysTick_Library.h"
#include "LCD_Library.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Tunes_Library.h"
#include <time.h>

/*************Global Variables Used Throughout Libraries****************
************************************************************************/
uint8_t i = 0, n = 0, x = 0,  j = 0;
int Credits = 0;
int one = 0, two = 0, three = 0;
uint8_t play = 0;

enum Reel_state {DISPLAY_SCREEN, INPUT_BET, SPIN_RESULTS}
Reel_state = DISPLAY_SCREEN;

/*************Global Variables Used Throughout Libraries****************
************************************************************************/

/// ************| Menu_Screen |*******************
/// * Brief:  Main menu on LCD Display that
/// *         gives user options to other
/// *         display screen locations
/// * Parm:
/// *     N/A
/// * Return:
/// *      N/A
/// **********************************************/
void Menu_Screen(void){

    if(i != 3  &&  ((BetUp || BetDown || Start) == 1)){
      Bet = 0;
      BetUp = 0;                //Error checking interrupted buttons
      BetDown = 0;              //Resetting if play menu is not present
      Start = 0;
   }

    lcdSetText("MENU", 0, 0);
    lcdSetText("1- Win Sounds", 0, 1);
    lcdSetText("2- Enter Credits", 0, 2);
    lcdSetText("3- Play", 0, 3);
    SysTick_delay_ms(50);
}

/// ************| Intro_Screen |*********************
/// * Brief: Displays names and the words
/// *   slot machine when devices is powered on.
/// *   Display changes to menu after 3 second delay
/// * Param:
/// *      N/A
/// * Return:
/// *      N/A
/// *************************************************/
void Intro_Screen(void){

    lcdWriteCmd(DISPLAY_100);   //Turning off cursor
    SysTick_delay_us(10);

    lcdSetText("Josh Johnston", 2, 0);
    lcdSetText("Jordan Hayes", 2, 1);
    lcdSetText("SLOT MACHINE", 2, 3);
    SysTick_delay_ms(3000);     //Delays screen for 3 seconds

    lcdWriteCmd(CLEAR);         //Clears Display
    lcdWriteCmd(HOME);          //Sets cursor back to home position
    SysTick_delay_us(10);
}

/// ************| Menu_Options |*******************
/// * Brief: Allows user to navigate through
/// *        the different menu screens from
/// *        Menu screen. Uses Keypad
/// *        initialized is SysTick_Library.c
/// *
/// * Global Variables:
/// *         i, num
/// * Return:
/// *      N/A
/// **********************************************/
 void Menu_Options(void){

    if(i == 0 && Read_Keypad()){    //Condition for i variable value and reads for keypad entry

     if( i != 3 && (BetUp == 1)){
         Bet = 0;
         BetUp = 0;                 //Error checking interrupts
         BetDown = 0;               //Resetting if play screen is not present
         Start = 0;
   }

        if(num == 1){               //Goes to sounds menu when num == 1 and i == 0

         lcdWriteCmd(CLEAR);        //Clears display
         lcdWriteCmd(HOME);         //Sets cursor home position
         SysTick_delay_ms(10);

         lcdSetText("1- Song 1 ", 0, 0);
         lcdSetText("2- Song 2", 0, 1);
         lcdSetText("3- Win Bells", 0, 2);
         lcdSetText("*- Confirm Sound", 0, 3);
         SysTick_delay_ms(50);
         i = 1;                     //Sets value of i to 1
       }

       else if(num == 2){           //Goes to Credit enter screen when num == 2 and i == 0

         lcdWriteCmd(CLEAR);        //Clears display
         lcdWriteCmd(HOME);         //Sets cursor to home position
         SysTick_delay_us(10);

         lcdSetText("Enter Credits: ", 0, 0);
         lcdSetText("* = Cancel", 0, 1);
         lcdSetText("# = Accept", 0, 2);
         SysTick_delay_ms(10);
         i = 2;                     //Sets value of i to 2
       }

       else if(num  == 3){          //Condition for 3rd screen
           i = 3;                   //Sets i to 3
           Bet = 0;                 //Clears bet
           lcdWriteCmd(CLEAR);      //Clears display
           lcdWriteCmd(HOME);       //Sets cursor to home position
           SysTick_delay_us(10);

       }
    }
}

/// ************| Bet_Input |*******************
/// * Brief: Stores user bet when conditions
/// *         are met. Uses port interrupts
/// *         initialized in SysTick_Library.c
/// *         on Bet-up and Bet-down buttons
/// *
/// * Global Variables:
/// *         BetUp, BetDown, Bet
/// ****Note: BetUp and BetDown are used as port
/// *    interrupts initialized in SysTick_Library.c
/// * Return:
/// *      N/A
/// **********************************************/
void Bet_Input(void){

  if(BetUp == 1 && Bet < 5 && i == 3){              //Condition for Bet to increment, checks interrupt and bet value
        SysTick_delay_ms(350);                      //Delays 350ms for debounce purposes

           if(BetUp == 1 && i == 3){                //After delay value of interrupt flag is checked again
              Bet ++;                               //If conditions are met bet is incremented
              BetUp = 0;                            //Interrupt flag is reset
           }
      }

    else if(BetDown == 1 && Bet > 0 && i == 3){     //Conditions for decreasing bet
           SysTick_delay_ms(350);                   //Delays 350ms for debounc

           if(BetDown == 1 && i == 3){              //Checks interrupt flag value again
              Bet--;                                //If conditions are met bet is subtracted by one
              BetDown = 0;                          //Bet down flag is reset
            }
       }
}

/// ************| Home_Option |*******************
/// * Brief: Navigation back to menu screen while
/// *        on any screen by inputing the * on
/// *        the Keypad
/// *
/// * Global Variables:
/// *         num, i, n
/// * Return:
/// *      N/A
/// **********************************************/
void Home_Option(void){

    if(num == 10){               //Condition if * is pressed

       lcdWriteCmd(CLEAR);       //Clears display
       lcdWriteCmd(HOME);        //Sets cursor to home position
       SysTick_delay_us(10);

       Menu_Screen();            //Displays menu screen on LCD
        i = 0;                   //Resets i to zero
        n = 0;                   //Resets n to zero
    }
}

/// ************| Lose_Lights |*******************
/// * Brief: Displays losing LED sequence when
/// *        characters don't match
/// *
/// * Global Variables:
/// *         N/A
/// * Return:
/// *      N/A
/// **********************************************/
void Lose_Lights(void){

    Speaker(A_4,2);
    P3->OUT |= (BIT5);
    SysTick_delay_ms(500);
    Speaker(0,0);
    SysTick_delay_ms(100);

    P3->OUT = 0;
    P3->OUT |= BIT6;
    Speaker(E_4, 2);
    SysTick_delay_ms(500);
    Speaker(0,0);
    SysTick_delay_ms(200);

    P3->OUT = 0;                      //Turns off LEDs
    P3->OUT |= (BIT5 | BIT6 | BIT7);  //Turns red LEDs on
    Speaker(C_4, 2);
    SysTick_delay_ms(1000);

    Speaker(0,0);
    P3->OUT = 0;

  }

/// ************| Play_Game |*******************
/// * Brief: Finite State Machine, this allows
/// *        for slot machine reel to randomize.
/// *        As well, displays outcome of reel
/// *        with display message, credit update,
/// *        bet clear, and LED sequence
/// *
/// * Global Variables:
/// *         Reel_state, Credits, Bet, Start, play
/// ****Note: Start is used as a port interrupt
/// *          initialized in SysTick_Library.c
/// * Return:
/// *      N/A
/// **********************************************/
 void Play_Game(void){

   uint8_t a, b, c, e, f, g;
   char Symbols[5] = {Diamond_index, Stick_Person_index, Dollar_index};
   char row1_1, row1_2, row1_3;
   char row2_1, row2_2, row2_3;



 switch(Reel_state){                        //Finite State Machine

   case DISPLAY_SCREEN:

     if(ButtonPress == 1){                  //Checks for keypad press with port interrupt
        Read_Keypad();                      //Reads keypad function for number

        if(num == 10){                      //Condition to go back to menu screen

           lcdWriteCmd(CLEAR);              //Clears display
           lcdWriteCmd(HOME);               //Sets cursor to home position
           SysTick_delay_ms(50);
           Menu_Screen();                   //Goes to menu screen
           SysTick_delay_ms(10);
           ButtonPress = 0;                 //Resets keypad interrupt flag
           Bet = 0;                         //Resets Bet back to zero
         }
   }

     if(num == 3 && i == 3){                //Condition to print the play screen to LCD

         lcdSetText("GOOD", 0 , 0);
         lcdSetText("LUCK!", 0, 1);
         Characters();                      //Displays special characters
         lcdSetText("CR", 0, 2);
         lcdSetText("MENU", 6, 2);
         lcdSetText("BET", 12, 2);
         lcdSetInt(Credits, 0,3);
         lcdSetInt(Bet, 13, 3);
         lcdSetText("*", 7, 3);
         SysTick_delay_ms(25);
  }

    Reel_state = INPUT_BET;
    break;


   case INPUT_BET:

     if(Credits > 0 && i == 3){             //Inputting bet condition

         Bet_Input();                       //Goes into bet input function
         lcdSetInt(Bet, 13, 3);             //Displays updated bet value
         SysTick_delay_ms(10);
  }

    Reel_state = SPIN_RESULTS;
    break;


   case SPIN_RESULTS:

       if(Credits > 0 && Credits >= Bet && Bet > 0){

           if(Start == 1){                  //If conditions are met game can start if interrupt flag is triggered
            SysTick_delay_ms(250);          //Delays 250ms for debounce purposes

           if(Start == 1)                   //Reads flag value again

        for(j = 0; j < 30; j++){            //For loop for timing == approx 5 seconds
            Start = 0;                      //Resets start variable

            Speaker(D_4,2);                 //Plays note frequency D_4
            SysTick_delay_ms(60 + (j * 2)); //Delay increases as time increases to hold note longer for slot machine affect
            Speaker(A_4, 2);                //Plays note A_4 frequency
            SysTick_delay_ms(60 + (j * 2)); //Delay increases as time increases

             a = rand() % 3;                //Setting variables equal to a random number generator
             b = rand() % 3;                //To build a random number sequence
             c = rand() % 3;                //Which will then randomize the position of each character

             e = rand() % 3;
             f = rand() % 3;
             g = rand() % 3;

             row1_1 = Symbols[a];           //Sets char variable to an array set equal to the characters
             row1_2 = Symbols[b];           //The location is determined by the random number generated
             row1_3 = Symbols[c];

             row2_1 = Symbols[e];
             row2_2 = Symbols[f];
             row2_3 = Symbols[g];

             lcdSetChar(row1_1, 6, 0);      //Prints each character based off their random array position
             lcdSetChar(row1_2, 8, 0);
             lcdSetChar(row1_3, 10, 0);
             SysTick_delay_us(100);

             lcdSetChar(row2_1, 6, 1);
             lcdSetChar(row2_2, 8, 1);
             lcdSetChar(row2_3, 10, 1);
             SysTick_delay_us(100);



             if(Start == 1){                //Condition to stop the randomization and leave the for loop if spin button is pressed
                 SysTick_delay_ms(250);     //Delays 250ms for debouncing
                  if(Start == 1)            //Checks flag value again
                     play = 1;              //Sets play to 1 to leave the loop
                 break;                     //Break out statement used to leave
             }

        }

    }

         if(play == 1 || j == 30){            //Condition for if either button was pressed or loop ended

            if((a == b && b == c) && (e == f && f == g)){
                                                 //Both rows have wins condition
                Speaker(0,0);

               Credits = Credits + (Bet * Bet);  //Credits are now credits plus bet times itself due to multiple win spin
               Start = 0;                        //Spin flag is reset

              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetText(" ", 8, 0);
              lcdSetText(" ", 8, 1);
              lcdSetText(" ", 10, 0);
              lcdSetText(" ", 10, 1);
              Speaker(C_4,2);
              SysTick_delay_ms(300);

              Speaker(0,0);
              SysTick_delay_ms(100);
              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetChar(row1_2, 8, 0);
              lcdSetChar(row2_2, 8, 1);
              lcdSetText(" ", 10, 0);
              lcdSetText(" ", 10, 1);
              Speaker(E_4, 2);
              SysTick_delay_ms(300);

              Speaker(0,0);
              SysTick_delay_ms(200);
              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetChar(row1_2, 8, 0);
              lcdSetChar(row2_2, 8, 1);
              lcdSetChar(row1_3, 10, 0);
              lcdSetChar(row2_3, 10, 1);
              Speaker(G_4,2);
              SysTick_delay_ms(300);
              Speaker(0,0);

              lcdWriteCmd(CLEAR);              //Clears display
              lcdWriteCmd(HOME);               //Sets cursor to home position
              SysTick_delay_ms(50);

              lcdSetText("CONGRADULATIONS!", 0, 0);
              lcdSetText("YOU WIN: ",0, 2);
              lcdSetInt((Bet * Bet), 0, 3);
              lcdSetText("Credits", 3, 3);

              if(song == 1){
                  Pirates_C();
              }
              else if(song == 2){
                  Despacito();
              }
              else if(song == 3){
                  Bells();
              }

             lcdWriteCmd(CLEAR);
             lcdWriteCmd(HOME);
             SysTick_delay_us(10);

             Bet = 0;
             play = 0;
             j = 0;
     }


             else if(a == b && b == c){   //If first row number sequence matches it is a win

              Speaker(0,0);                 //Turn off speakers

              Credits += (Bet * 2);         //New value of credits is credits + bet * 2 because of winnning sequence
              Start = 0;                    //Start interrupt flag is reset

              lcdSetChar(row1_1, 6, 0);     //Display the first column of characters for slot machine effect
              lcdSetChar(row2_1, 6, 1);
              lcdSetText(" ", 8, 0);
              lcdSetText(" ", 8, 1);
              lcdSetText(" ", 10, 0);
              lcdSetText(" ", 10, 1);
              Speaker(C_4,2);               //Play C_4 note frequency
              SysTick_delay_ms(300);        //For 300ms

              Speaker(0,0);                 //Turn speaker off
              SysTick_delay_ms(100);        //Delay 100ms before displaying next column
              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetChar(row1_2, 8, 0);     //Display the first and second column of characters
              lcdSetChar(row2_2, 8, 1);
              lcdSetText(" ", 10, 0);
              lcdSetText(" ", 10, 1);
              Speaker(E_4, 2);              //Play E_4 note frequency
              SysTick_delay_ms(300);        //Delay 300ms

              Speaker(0,0);                 //Turn speaker off
              SysTick_delay_ms(200);        //Delay for 200ms gradually display slower for slot machine appearance
              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetChar(row1_2, 8, 0);
              lcdSetChar(row2_2, 8, 1);
              lcdSetChar(row1_3, 10, 0);     //Display 3rd column of characters
              lcdSetChar(row2_3, 10, 1);
              Speaker(G_4,2);               //Play G_4 note frequency
              SysTick_delay_ms(300);        //Delay for 300ms

              Speaker(0,0);                 //Turn Speaker off

              lcdSetText("YOU",12, 0);
              SysTick_delay_us(10);
              lcdSetText("WIN!", 12, 1);    //Win condition so displays a you win message
              SysTick_delay_us(10);

              lcdWriteCmd(CLEAR);           //Clears display
              lcdWriteCmd(HOME);            //Sets cursor to home position
              SysTick_delay_ms(50);

              lcdSetText("CONGRADULATIONS!", 0, 0);
              lcdSetText("YOU WIN: ",0, 2);
              lcdSetInt((Bet * 2), 0, 3);
              lcdSetText("Credits", 3, 3);


              if(song == 1){

                  Pirates_C();
              }

              else if(song == 2){

                  Despacito();
              }

              else if(song == 3){

                  Bells();
              }

              lcdWriteCmd(CLEAR);           //Clear display
              lcdWriteCmd(HOME);            //Return cursor to home position
              SysTick_delay_us(10);
              Bet = 0;                      //Reset Bet to zero
              play = 0;                     //Resets play value to zero
              j = 0;                        //Resets j back to zero to repeat loop

        }

          else if(e == f && f == g){
                                            //Same as top row except bottom row win condition
              Speaker(0,0);

              Credits += (Bet * 2);         //Bet is multiplied by 2 and added to credits
              Start = 0;                    //Reset start interrupt

              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetText(" ", 8, 0);
              lcdSetText(" ", 8, 1);
              lcdSetText(" ", 10, 0);
              lcdSetText(" ", 10, 1);
              Speaker(C_4,2);
              SysTick_delay_ms(300);

              Speaker(0,0);
              SysTick_delay_ms(100);
              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetChar(row1_2, 8, 0);
              lcdSetChar(row2_2, 8, 1);
              lcdSetText(" ", 10, 0);
              lcdSetText(" ", 10, 1);
              Speaker(E_4, 2);
              SysTick_delay_ms(300);

              Speaker(0,0);
              SysTick_delay_ms(200);
              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetChar(row1_2, 8, 0);
              lcdSetChar(row2_2, 8, 1);
              lcdSetChar(row1_3, 10, 0);
              lcdSetChar(row2_3, 10, 1);
              Speaker(G_4,2);
              SysTick_delay_ms(300);

              Speaker(0,0);

              lcdSetText("YOU",12, 0);
              SysTick_delay_ms(10);
              lcdSetText("WIN!", 12, 1);
              SysTick_delay_ms(10);

              lcdWriteCmd(CLEAR);              //Clears display
              lcdWriteCmd(HOME);               //Sets cursor to home position
              SysTick_delay_ms(50);

              lcdSetText("CONGRADULATIONS!", 0, 0);
              lcdSetText("YOU WIN: ",0, 2);
              lcdSetInt((Bet * 2), 0, 3);
              lcdSetText("Credits", 3, 3);

              if(song == 1){

                  Pirates_C();
               }

              else if(song == 2){

                  Despacito();

              }

             else if(song == 3){

                    Bells();
              }

              lcdWriteCmd(CLEAR);
              lcdWriteCmd(HOME);
              SysTick_delay_us(10);
              Bet = 0;
              play = 0;
              j = 0;

       }


          else{                                 //Condition if no rows match

              Speaker(0,0);                     //Turn speaker off

              Credits -= Bet;                   //Loss so credits equal credits minus bet
              Bet = 0;                          //Bet is reset
              Start = 0;                        //spin flag is reset

              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetText(" ", 8, 0);
              lcdSetText(" ", 8, 1);
              lcdSetText(" ", 10, 0);
              lcdSetText(" ", 10, 1);

              Speaker(C_4,2);
              SysTick_delay_ms(300);

              Speaker(0,0);
              SysTick_delay_ms(100);
              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetChar(row1_2, 8, 0);
              lcdSetChar(row2_2, 8, 1);
              lcdSetText(" ", 10, 0);
              lcdSetText(" ", 10, 1);

              Speaker(E_4, 2);
              SysTick_delay_ms(300);

              Speaker(0,0);
              SysTick_delay_ms(200);
              lcdSetChar(row1_1, 6, 0);
              lcdSetChar(row2_1, 6, 1);
              lcdSetChar(row1_2, 8, 0);
              lcdSetChar(row2_2, 8, 1);
              lcdSetChar(row1_3, 10, 0);
              lcdSetChar(row2_3, 10, 1);

              Speaker(G_4,2);
              SysTick_delay_ms(300);

              Speaker(0,0);

              lcdSetText("BET", 12, 0);         //Bet lost message is displayed
              SysTick_delay_ms(10);
              lcdSetText("LOST", 12, 1);
              SysTick_delay_ms(10);

              Lose_Lights();                    //Red LED Sequence is displayed
              SysTick_delay_ms(500);
              lcdWriteCmd(CLEAR);
              lcdWriteCmd(HOME);
              SysTick_delay_us(10);

              play = 0;
              j = 0;
          }
      }
 }

   Reel_state = DISPLAY_SCREEN;
   break;
   }
}

/// ************| Spin_and_Play |*****************
/// * Brief: Sets condition to go enter play
/// *              game function.
/// *
/// * Global Variables:
/// *         N/A
/// * Return:
/// *      N/A
/// **********************************************/
void Spin_and_Play(void){

     if(i == 3){
      Play_Game();
     }
}

/// **********| Sounds_Options |**************
/// * Brief: Used as sound preview
/// *        and win sound selection
/// *
/// * Global Variables:
/// *         i, num
/// * Return:
/// *      N/A
/// *******************************************/
 void Sounds_Options(void){

   if(i == 1 && Read_Keypad()){     //Reads keypad and looks for number

      if(num == 1){                 //condition to play first sound

        Pirates_C();                //Plays song 1
        song = 1;                   //Sets global variable to one
      }

      else if(num == 2){           //Condition from num 2

        Despacito();               //Plays song 2
        song = 2;                  //Sets song to 2
       }

      else if(num == 3){           //Third song option

       Bells();                    //Plays song 3
       song = 3;                   //Sets value of song to 3
      }
   }
}

/// ***************| Credits_Input |*******************
/// * Brief: Stores user keypad credit input
/// *        when acceptance condition is met.
/// *        value is then stored in variable Credits
/// *
/// *Global Variables:
/// *       i, ButtonPress, num, x, n, one, two, three
/// ****Note: ButtonPress is used as port interrupt for
/// *      keypad initialized in SysTick_Libraries.c
/// * Return:
/// *      N/A
/// ****************************************************/
void Credits_Input(void){

    if(i == 2 && Read_Keypad()){           //Looks for i value and value from keypad

       if(ButtonPress == 1) n++;           //If keypad flag is triggered n is incremented

           if(num == 11){

               num = 0;                    //Sets num to the value of 0 when it is pressed on keypad
               SysTick_delay_us(10);
           }

           if(n == 1 && (num == 12))       //Error check if pound is pressed but no number before the value will not display

               x = 0;

           if(n == 1 && (num != 12)){      //If digit is entered and pound is not pressed

               lcdSetInt(num, 0, 3);       //Num will display on LCD
               one = num;                  //Variable one set to hold the value of num
               x = 1;                      //A variable is set to one to show it was the first value pressed
           }

           if(n == 2 && (num != 12)){      //If a second digit was entered and pound was not pressed

               lcdSetInt(num, 1, 3);       //The num will be displayed next to the first entry
               two = num;                  //A second variable is set equal to the num
               x = 2;                      //Place holder variable is used to identify which order number was pressed
           }

           if(n == 3 && (num != 12)){      //Condition for third digit being pressed

               lcdSetInt(num, 2, 3);       //Displays number next to second digit
               three = num;                //Third variable used to hold value of num
               x = 3;                      //Place holder variable used for digit position
           }
        }

           if(num == 12 && x == 1){        //First condition if one number was pressed and pound was used to accept the value

               Credits = one;              //Credits is set equal to the value of num which was the first number pressed

             lcdWriteCmd(CLEAR);           //Clears Display
             lcdWriteCmd(HOME);            //Sets cursor back to home position
             SysTick_delay_ms(10);
             Menu_Screen();                //Displays menu screen showing user their credit value has been accepted
             SysTick_delay_ms(10);

             i = 0;                        //Resets i
             n = 0;                        //Resets n
             x = 0;                        //Resets x
           }

           if(num == 12 && x == 2){        //Condition for a 2 number entry

               Credits = (one * 10) + two; //First value is multiplied by 10 and added to the second value entered

               lcdWriteCmd(CLEAR);         //Clears display
               lcdWriteCmd(HOME);          //Returns cursor to home position
               SysTick_delay_us(40);
               Menu_Screen();              //Goes to menu screen to show user credit value has been accepted
               SysTick_delay_us(40);

               i = 0;                      //Resets i
               n = 0;                      //Resets n
               x = 0;                      //Resets x
           }

           if(num == 12 && x == 3){        //Condition for a 3 digit number

               Credits = (one * 100) + (two * 10) + three;
                                           //Multiplies first number by 100 second by 10 and third stays as ones and adds all together
               lcdWriteCmd(CLEAR);         //Clears Display
               lcdWriteCmd(HOME);          //Returns cursor to home position
               SysTick_delay_ms(10);
               Menu_Screen();              //Returns to menu screen to show value was accepted
               SysTick_delay_us(10);

               i = 0;                      //Resets i
               n = 0;                      //Resets n
               x = 0;                      //Resets x
           }

           if(num == 10 && n > 0 && n < 4){
                                           //Condition if a value was entered but * was pressed to cancel
               Credits = 0;                //Resets credits

               Menu_Screen();              //Returns to menu screen
               SysTick_delay_us(10);

               i = 0;                      //Resets i
               n = 0;                      //Resets n
               x = 0;                      //Resets x
              Credits = 0;                 //Confirms credits reset

           }

           else if(n > 4){                 //Condition if a number greater than 999 or more then 4 keys were pressed

               lcdWriteCmd(CLEAR);
               lcdWriteCmd(HOME);
               SysTick_delay_ms(10);

               lcdSetText("LIMIT EXCEEDED", 1, 0);
               lcdSetText("ENTER AMOUNT", 2, 1);
               lcdSetText("WITHIN RANGE:", 2, 2);
               lcdSetText("0 - 999", 4, 3);
               SysTick_delay_ms(5000);

               n = 0;                      //Resets n
               x = 0;                      //Resets x

               lcdWriteCmd(CLEAR);
               lcdWriteCmd(HOME);
               SysTick_delay_ms(10);
                                           //Goes back to credit screen when message of exceeding range is removed
               lcdSetText("Enter Credits: ", 0, 0);
               lcdSetText("* = Cancel", 0, 1);
               lcdSetText("# = Accept", 0, 2);
               SysTick_delay_us(10);

               i = 2;                      //Sets i to 2 to confirm credit screen is valid
       }
}

/// ***************| Cash_Out_Lights |*******************
/// * Brief: Flashes lights after cash out song and
/// *        lights finish
/// *
/// *Global Variables:
/// *       N/A
/// * Return:
/// *      N/A
/// ****************************************************/
void Cash_Out_Lights(void){

    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
    SysTick_delay_ms(250);
    P3->OUT = 0;
    SysTick_delay_ms(250);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
    SysTick_delay_ms(250);
    P3->OUT = 0;
    SysTick_delay_ms(250);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
    SysTick_delay_ms(250);
    P3->OUT = 0;
    SysTick_delay_ms(250);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
    SysTick_delay_ms(250);
    P3->OUT = 0;
    SysTick_delay_ms(250);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
    SysTick_delay_ms(250);
    P3->OUT = 0;
    SysTick_delay_ms(250);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
    SysTick_delay_ms(250);
    P3->OUT = 0;
    SysTick_delay_ms(250);
    P3->OUT |= (BIT0 | BIT2 | BIT3 | BIT5 | BIT6 | BIT7);
    SysTick_delay_ms(1000);
    P3->OUT = 0;
    SysTick_delay_ms(1000);
}

/// ***************| Servo |*******************
/// * Brief: Moves the servo to drop the coin
/// *         out of the coin box
/// *
/// *Global Variables:
/// *       N/A
/// * Return:
/// *      N/A
/// ****************************************************/
void Servo(void){

        P8->SEL0 |= BIT2;             //P8.2 set to TA3.2
        P8->SEL1 &= ~BIT2;            //GPIO
        P8->DIR |= BIT2;              //P8.2 Set to Output

        TIMER_A3->CCR[0] = 6000;     //Period to be set between 1 and 2ms
        TIMER_A3->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;   //CCR1 reset
        TIMER_A3->CCR[2] = 0;        //PWM duty cycle
        TIMER_A3->CTL = 0x0214;      //SMCLK, Up Mode, Clear TAR to start
}

/// **************| Cash_Out |******************
/// * Brief: Displays cash out screen when user
/// *        pushes cash out button. Cash out
/// *        displays how many credits remain
/// *        and plays a song and light show.
/// *        As well, resets credits back to 0.
/// *
/// * Global Variables:
/// *         CashOut, Credits
/// ****Note: CashOut is used as a port interrupt
/// *         initialized in SysTick_libraries.c
/// * Return:
/// *      N/A
/// **********************************************/
void Cash_Out(void){

    if(CashOut == 1){                      //If cashout button interrupt is triggered
        SysTick_delay_ms(250);             //Delay for debounce

        if(CashOut == 1)                   //Check flag value again

            lcdWriteCmd(CLEAR);            //Clear display
            lcdWriteCmd(HOME);             //Return cursor to home position

            lcdSetText("Cash Out:", 0, 0);
            lcdSetInt(Credits, 10, 0);     //Display last recorded credits value
            SysTick_delay_ms(10);

            lcdSetText("Thanks 4 Playing", 0, 2);
            SysTick_delay_ms(10);

            lcdSetText("Slot Machine", 2, 3);
            SysTick_delay_ms(10);
            Pirates_C();
            Cash_Out_Lights();             //Displays cashout lights
            TIMER_A3->CCR[2] = 6000;       //Rotates servo 180 degrees counterclockwise to open door
            SysTick_delay_ms(2000);        //Delays for 2 seconds to allow full opening of the door
            TIMER_A3->CCR[2] = 3000;       //Rotates servo 180 degrees clockwise to close door
            SysTick_delay_ms(3000);        //Delays 3 seconds to confirm secure shut
            TIMER_A3->CCR[2] = 0;          //Turns servo off

            Credits = 0;                   //Resets credit to zero
            i = 0;                         //Resets i to zero

            lcdWriteCmd(CLEAR);            //Clears display
            lcdWriteCmd(HOME);             //Sets cursor back to home position
            SysTick_delay_us(10);

            Menu_Screen();                 //Returns to menu screen
            SysTick_delay_ms(10);

            CashOut = 0;                   //Resets cashout interrupt flag

      }
 }
