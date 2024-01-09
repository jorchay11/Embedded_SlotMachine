/**************************************************************************************
***************************************************************************************
*                                SysTick_Library.h
*                           Trevor Ekin / Nabeeh Kandalaft
*                         EGR226      Date: March, 6, 2019
*                  (Updated by Joshua Johnston Date: March 26, 2019)
*
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
* *******************************************************************************************/

#ifndef SYSTICK_LIBRARY_H_
#define SYSTICK_LIBRARY_H_

#include "msp.h"
#include <stdint.h>

// SysTick Control and Status Register (STCSR)
#define STCSR_COUNT_FG  (0x0100)
#define STCSR_CLKSRC    (0x0004)
#define STCSR_INT_EN    (0x0002)
#define STCSR_EN        (0x0001)

/*************Global Variables Used Throughout Libraries****************
************************************************************************/
extern volatile uint8_t ButtonPress;
extern volatile uint8_t BetUp;
extern volatile uint8_t BetDown;
extern volatile uint8_t Start;
extern volatile int Bet;
extern volatile uint8_t CashOut;
extern uint8_t num;
/*************Global Variables Used Throughout Libraries****************
************************************************************************/

/********************* Macro Prototypes ********************************
************************************************************************
   SysTick Control and Status Register (STCSR) as discussed in lectures

//#define STCSR_COUNT_FG  BIT16
//#define STCSR_CLKSRC    BIT2          // this is the CLKSOURSE bit
//#define STCSR_INT_EN    BIT1          // This is the TICKINT  bit
//#define STCSR_EN        BIT0          // This is the ENABLE bit

********************** Macro Prototypes ********************************
************************************************************************


********************** Function Prototypes *****************************
************************************************************************/
void SysTickInit_NoInterrupts  (void);
void SysTickInit_WithInterrupts(void);
void SysTick_delay_ms(volatile uint32_t);
void SysTick_delay_us(volatile uint32_t);
void KeyPad_Init(void);
uint8_t Read_Keypad(void);
void Buttons_init(void);
void LED_init(void);
/********************* Function Prototypes *****************************
************************************************************************/

#endif /* SYSTICK_LIBRARY_H_ */
