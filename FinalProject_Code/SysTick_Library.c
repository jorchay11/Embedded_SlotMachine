/**************************************************************************************
***************************************************************************************
*                                SysTick_Library.c
*                           Trevor Ekin / Nabeeh Kandalaft
*                         EGR226      Date: March, 6, 2019
*                       (Updated by Joshua Johnston Date: March 26, 2019)
*
*  This is a library for the SysTick Timer Peripheral on the MSP432.
*
*  All functions are briefly described in their comment blocks.  The /// notation makes
*  it so the function description block is visible when you hovering over a function call
*  in any file (this feature is called Intellisense).
*
/// * UPDATE
* Initialization functions added for Standard 12 Key Keypad, Momentary Push Buttons and LEDs.
* A function used to read the Keypad and return the number pressed
* See Slot_Machine.c Library for pin out and reference schematic for wiring
* ********************************************************************************************/

#include "SysTick_Library.h"
#include "msp.h"
#include <stdio.h>

/*************Global Variables Used Throughout Libraries****************
************************************************************************/
volatile uint8_t ButtonPress = 0;
volatile uint8_t BetUp = 0;
volatile uint8_t BetDown = 0;
volatile uint8_t Start = 0;
volatile uint8_t CashOut = 0;
uint8_t num;
volatile int Bet = 0;
/*************Global Variables Used Throughout Libraries****************
************************************************************************/

/// ****| SysTickInit_NoInterrupts | ****************//*
/// * Brief: Initialize the SysTick peripheral for use
/// *          without interrupts (busy-waits)
/// * param:
/// *      N/A
/// * return:
/// *      N/A
/// ****************************************************/
void SysTickInit_NoInterrupts(void){
    SysTick->CTRL  &= ~BIT0;                             //clears enable to stop the counter
    SysTick->LOAD   = 0x00FFFFFF;                        //sets the period... note: (3006600/1000 - 1) = 1ms
    SysTick->VAL    = 0;                                 //clears the value
    SysTick->CTRL   = (STCSR_CLKSRC | STCSR_EN);         //enable SysTick, core clock, no interrupts, this is the ENABLE and CLKSOURSE
}

/// ****| SysTickInit_WithInterrupts | **************//*
/// * Brief: Initialize the SysTick peripheral for use
/// *          with interrupts (interrupt delays)
/// * param:
/// *      N/A
/// * return:
/// *      N/A
/// ****************************************************/
void SysTickInit_WithInterrupts(void){
    SysTick->CTRL  &= ~BIT0;                                             //clears enable to stop the counter
    SysTick->LOAD   = 0x00FFFFFF;                                        //sets the period... note: (3006600/1000 - 1) = 1ms
    SysTick->VAL    = 0;                                                 //clears the value
    SysTick->CTRL   = (STCSR_CLKSRC | STCSR_INT_EN | STCSR_EN);          // this is the ENABLE, TICKINT, CLKSOURSE a WITH interrupts Systic->CTRL |= 0x07;
}

/// ****| SysTick_delay_ms | *************************//*
/// * Brief: Use the SysTick timer to delay a specified
/// *          number of milliseconds
/// * param:
/// *      (uint32_t) ms_delay:  number of milliseconds
/// *                              to delay
/// * return:
/// *      N/A
/// ****************************************************/
 void SysTick_delay_ms(uint32_t ms_delay){
    //Delays time_ms number of milliseconds
    //Assume 3MHz clock -> 3000 cycles per millisecond
    SysTick->LOAD  = 3000 * (uint32_t)ms_delay;
    SysTick->VAL   = 0;                               // starts counting from 0
    SysTick->CTRL |= (STCSR_CLKSRC | STCSR_EN);       // ENABLE, CLKSOURSE bits  .... Systic->CTRL |= 0x05;
     while(!(SysTick->CTRL & ((uint32_t)1)<<16));      // Continue while bit 16 is high or use   ....while( (SysTick->CTRL & BIT16) == 0);
    SysTick->CTRL &= ~(STCSR_CLKSRC | STCSR_EN);      // Disable the Systic timer               .... Systic->CTRL =0 ;
}

/// ****| SysTick_delay_us | ************************//*
/// * Brief: Use the SysTick timer to delay a specified
/// *          number of microseconds
/// * param:
/// *      (uint32_t) us_delay:  number of microseconds
/// *                              to delay
/// * return:
/// *      N/A
/// ****************************************************/
void SysTick_delay_us(uint32_t us_delay){
    //Delays time_ms number of milliseconds
    //Assume 3MHz clock -> 3 cycles per microsecond
    SysTick->LOAD  = us_delay*3 - 1;                 //counts up to delay
    SysTick->VAL   = 0;                              //starts counting from 0
    SysTick->CTRL |= (STCSR_CLKSRC | STCSR_EN);      // ENABLE, CLKSOURSE bits  .... Systic->CTRL |= 0x05;
    while(!(SysTick->CTRL & ((uint32_t)1)<<16));     // Continue while bit 16 is high   .... while( (SysTick->CTRL & BIT16) == 0);
    SysTick->CTRL &= ~(STCSR_CLKSRC | STCSR_EN);     // Disable the Systic timer        .... Systic->CTRL =0 ;
}

/// **********| PORT5_IRQHandler | ************************
/// * Brief: When Port5 interrupt is triggered
/// *         by pressing the keypad, function and sets
/// *         variable value to one
/// *
/// * Global Variables:
/// *        ButtonPress
/// ****Note: ButtonPress used as a port interrupt
/// *         variable for Keypad recognition
/// * return:
/// *      N/A
/// ****************************************************/
void PORT5_IRQHandler(void){

         if(P5->IFG & (BIT4 | BIT5 | BIT6 | BIT7))  //If keypad is pressed interrupt is triggered

          ButtonPress = 1;                          //Set value of one to volatile variable ButtonPress

         P5->IFG &= ~(BIT4 | BIT5 | BIT6 | BIT7);   //Clear all flags
}

/// **********| PORT1_IRQHandler | ****************************
/// * Brief: When Port1 interrupt is triggered by pressing
/// *        any of Spin, BetUp, or BetDown sets specific
/// *        variable to the value of one based off which
/// *        button is pressed.
/// *
/// * Global Variables:
/// *        Start, BetUp, BetDown
/// ****Note: Start, BetUp, and BetDown used as port
/// *         interrupt variables
/// * return:
/// *      N/A
/// ************************************************************/
void PORT1_IRQHandler(void){

    if(P1->IFG & BIT5)                  //If spin interrupt is triggered

        Start = 1;                      //Set value of one to volatile variable start

    if(P1->IFG & BIT6)                  //If bet up interrupt is triggered

        BetUp = 1;                      //Set value of one to volatile variable BetUp

    if(P1->IFG & BIT7)                  //If BetDown interrupt is triggered

        BetDown = 1;                    //Set value of one to volatile variable BetDown

    P1->IFG &= ~(BIT5 | BIT6 | BIT7);   //Clear all interrupt flags

}

/// **********| PORT6_IRQHandler | ****************************
/// * Brief: When Cashout button is pressed interrupt is
/// *        is triggered and sets CashOut variable to one.
/// *
/// * Global Variables:
/// *        CashOut
/// ****Note: CashOut is used as port interrupt variable
/// *
/// * return:
/// *      N/A
/// ************************************************************/
void PORT6_IRQHandler(void){

    if(P6->IFG & BIT0)      //If interrupt flag triggers

        CashOut = 1;        //Set value of one to volatile variable

    P6->IFG &= ~BIT0;       //Clear flag
}

/// *****************| KeyPad_Init | ***************************
/// * Brief: Initializes KeyPad, rows have internal pull-up
/// *        resistors and interrupts. Columns initialized
/// *        as GPIO inputs
/// *
/// * Global Variables:
/// *        N/A
/// * return:
/// *      N/A
/// ************************************************************/
void KeyPad_Init(void){

    P5->SEL0 = 0;
    P5->SEL1 = 0;                                   //GPIO
    P5->DIR &= ~(BIT4 | BIT5 | BIT6 | BIT7);        //Port 5 pins set to input
    P5->REN |= (BIT4 | BIT5 | BIT6 | BIT7);         //Enable internal resistor
    P5->OUT |= (BIT4 | BIT5 | BIT6 | BIT7);         //Enable resistor as pull-up
    P5->IES |= (BIT4 | BIT5 | BIT6 | BIT7);         //High to low interrupt trigger for rows
    P5->IFG = 0;                                    //Clear flags
    P5->IE |= (BIT4 | BIT5 | BIT6 | BIT7);          //Enable interrupts on rows


    P2->SEL0 = 0;
    P2->SEL1 = 1;                                   //GPIO
    P2->DIR &= ~(BIT5 | BIT6 | BIT7);               //Set columns as inputs
}

/// *****************| Read_Keypad | ***************************
/// * Brief: Reads number pressed on keypad based of column
/// *         and row state.
/// *
/// * Global Variables:
/// *        num
/// * return:
/// *      num: number pressed on keypad
/// ************************************************************/
uint8_t Read_Keypad(void){

    uint8_t col;
    uint8_t row;

    for(col = 0; col < 3; col++)
    {
        P2->DIR = 0;
        P5->DIR = 0;                            //Set port 4 to input
        P2->DIR |= BIT(5 + col);                //Set columns 0 - 2 to output by incrementing
        P2->OUT &= ~BIT(5 + col);               //Set columns 0 - 2 to LOW by incrementing

        SysTick_delay_ms(10);                   //Delays while loop 10ms
        row = P5->IN & 0xF0;                    //Read all rows

        while ( !(P5IN & BIT4) | !(P5IN & BIT5) | !( P5IN & BIT6) | !( P5IN & BIT7) );

        if(row != 0xF0) break;                  //If low reading some key is pressed
    }

    P2->DIR &= ~(BIT5 | BIT6 | BIT7);           //Set columns to inputs
    if(col == 3)


        return 0;

    if(row == 0xE0) num = col + 1;              //Key press in row 0
    if(row == 0xD0) num = 3 + col + 1;          //Key press in row 2
    if(row == 0xB0) num = 6 + col + 1;          //Key press in row 2
    if(row == 0x70) num = 9 + col + 1;          //Key press in row 3



    return 1;
}

/// *****************| Button_init | ***************************
/// * Brief: Initializes all four buttons: BetUp, BetDown, Spin
/// *         and CashOut as input port interrupts
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// ************************************************************/
void Buttons_init(void){

    P1->SEL0 = 0;
    P1->SEL1 = 0;                           //Sets port 1 as GPIO
    P1->DIR &= ~(BIT5 | BIT6 | BIT7);       //Set as input
    P1->REN |= (BIT5 | BIT6 | BIT7);        //Enable internal resistor
    P1->OUT |= (BIT5 | BIT6 | BIT7);        //Enable resistor as pull-up
    P1->IES |= (BIT5 | BIT6 | BIT7);        //Set to trigger interrupt from high to low
    P1->IFG = 0;                            //Clears all interrupt flags
    P1->IE |= (BIT5 | BIT6 | BIT7);         //Enables interrupt

    P6->SEL0 = 0;
    P6->SEL1 = 0;                           //GPIO
    P6->DIR &= ~BIT0;                       //Input
    P6->REN |= BIT0;                        //Enable internal resistor
    P6->OUT |= BIT0;                        //Enable resistor as pull-up
    P6->IES |= BIT0;                        //High to low trigger
    P6->IFG = 0;                            //Clear flags
    P6->IE |= BIT0;                         //Enable interrupt
}

/// *****************| LED_init | ***************************
/// * Brief: Initializes all six LEDs initially in the off
/// *        or set to zero.
/// *
/// * Global Variables:
/// *         N/A
/// * return:
/// *         N/A
/// ************************************************************/
void LED_init(void){

    P3->SEL0 = 0;
    P3->SEL1 = 0;                       //Sets Port 3 to GPIO
    P3->DIR |= (BIT0 | BIT2 | BIT3);    //Sets Bit 0, 2, and 3 to output
    P3->DIR |= (BIT5 | BIT6 | BIT7);    //Sets Bit 5, 6, and 7 to output
    P3->OUT = 0;                        //Sets initial state of port to 0
}
