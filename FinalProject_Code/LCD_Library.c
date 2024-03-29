 /**************************************************************************************
***************************************************************************************
*                                LCD_Library.c
*                        Trevor Ekin (Adapted from Dr. Nabeeh Kandalaft)
*                         EGR226      Date: February-21-2019
*                         (Updated by Josh Johnston Date: 04/02/2019)
*
*  This is a library for the 4x16 LCD.
*
*  All functions are briefly described in their comment blocks.  The /// notation makes
*  it so the function description block is visible when you hovering over a function call
*  in any file (this feature is called Intellisense).
*
*  All pins are set with default values (see below) but they can be easily changed with
*  in LCD_Library.h to any pin configuration (follow instructions in header file)
*
/// * UPDATE
 * Custom character function was added called: Character_init()
 * Initial location to display on 16 x 4 LCD for custom characters
 * Function called: Characters()
*****************************  Pins   **************************************************
*                   MSP432 PINS (Default, see LCD_Library.h to change these)
*                   P4.0 -> LCD D4
*                   P4.1 -> LCD D5
*                   P4.2 -> LCD D6
*                   P4.3 -> LCD D7
*                   P4.4 -> LCD E
*                   P4.5 -> LCD RS
* **************************************************************************************/

#include <stdint.h>
#include "LCD_Library.h"
#include <stdio.h>
#include "SysTick_Library.h"

/*************Global Variables Used Throughout Libraries****************
************************************************************************/
char Diamond_index;
char Arrows_index;
char Dollar_index;
char Stick_Person_index;
/*************Global Variables Used Throughout Libraries****************
************************************************************************/

/// ****| lcdInit | *********************************//*
/// * Brief: Initialize the LCD with chosen connection
/// *          pins.  Send configuration sequence.
/// * param:
/// *      N/A
/// * return:
/// *      N/A
/// ****************************************************/
void lcdInit() {
    // Initialize all communication pins as outputs (see LCD_Library.h for PDIR macro definitions)
    RS_DIR |= RS;
    EN_DIR |= EN;
    D4_DIR |= D4;
    D5_DIR |= D5;
    D6_DIR |= D6;
    D7_DIR |= D7;

    // Initialize all communication pins as low (see LCD_Library.h for Bit Toggling macro definitions)
    RS_LOW;
    EN_LOW;
    D4_LOW;
    D5_LOW;
    D6_LOW;
    D7_LOW;

    // Send initialization command sequence (see LCD_Library.h for command macro definitions)
    // Many init commands are sent multiple times for redundancy (takes time to latch in LCD)
    SysTick_delay_ms(100);

    // CLEAR command is 0x01
    lcdWriteCmd(CLEAR);         SysTick_delay_ms(100);  //clear screen

    //-------------------------------------------------------------------------------------
    // FUNCTION SET COMMAND: 0b001[DL] [N][F] * * -> DL = Data length, N = display lines, F = character font
    //FSET_000        0x20    -- 4-bit data, 1 line, 5x8 dot font
    //FSET_001        0x24    -- 4-bit data, 1 line, 5x10 dot font
    //FSET_010        0x28    -- 4-bit data, 2 lines, 5x8 dot font
    //FSET_011        0x2C    -- 4-bit data, 2 lines, 5x10 dot font
    //FSET_100        0x30    -- 8-bit data, 1 line, 5x8 dot font     (standard)
    //FSET_101        0x34    -- 8-bit data, 1 line, 5x10 dot font
    //FSET_110        0x38    -- 8-bit data, 2 lines, 5x8 dot font
    //FSET_111        0x3C    -- 8-bit data, 2 lines, 5x10 dot font
    //-------------------------------------------------------------------------------------
    lcdWriteCmd(FSET_100);      SysTick_delay_ms(100);  //start reset
    lcdWriteCmd(FSET_100);      SysTick_delay_ms(100);  //reinforce reset
    lcdWriteCmd(FSET_100);      SysTick_delay_ms(100);  //reset captured
    lcdWriteCmd(FSET_100);      SysTick_delay_ms(100);  //send real "function set" call (same as others but it is still needed)

    // HOME command is 0x02
    lcdWriteCmd(HOME);          SysTick_delay_ms(100);  //send cursor home

    //-------------------------------------------------------------------------------------
    // ENTRY MODE COMMAND: 0b0000 01[I][S] -> I = Increment, S = Shift
    //ENTRYMODE_00    0x04    // no auto increment, no display shift  (DEFAULT)
    //ENTRYMODE_01    0x05    // no auto increment, display shift
    //ENTRYMODE_10    0x06    // auto increment, no display shift
    //ENTRYMODE_11    0x07    // auto increment, display shift
    //-------------------------------------------------------------------------------------
    lcdWriteCmd(ENTRYMODE_10);  SysTick_delay_ms(100);  //set up for auto incrementing

    lcdWriteCmd(CLEAR);         SysTick_delay_ms(100);  //clear screen (again)

    //-------------------------------------------------------------------------------------
    // DISPLAY CONTORL COMMAND: 0b0000 1[D][C][B] -> D = Display, C = Cursor, B = Blinking
    //DISPLAY_000     0x08    -- display off, cursor off, blinking off    (DEFAULT)
    //DISPLAY_001     0x09    -- display off, cursor off, blinking on     (not useful)
    //DISPLAY_010     0x0A    -- display off, cursor on, blinking off     (not useful)
    //DISPLAY_011     0x0B    -- display off, cursor on, blinking on      (not useful)
    //DISPLAY_100     0x0C    -- display on, cursor off, blinking off
    //DISPLAY_101     0x0D    -- display on, cursor off, blinking on
    //DISPLAY_110     0x0E    -- display on, cursor on, blinking off
    //DISPLAY_111     0x0F    -- display on, cursor on, blinking on
    //-------------------------------------------------------------------------------------
    lcdWriteCmd(DISPLAY_111);   SysTick_delay_ms(100);  //turn on display with blinking cursor

    // reset CGRAM offset address
    _offset = 0;
}

/// ****| lcdTriggerEN | ****************************//*
/// * Brief: Pulse the enable pin to notify the LCD to
/// *          latch the current data inputs.
/// * param:
/// *      (unsigned char) data: 8-bit data to send
/// * return:
/// *      N/A
/// ****************************************************/
void lcdTriggerEN() {
    EN_HIGH;
    SysTick_delay_us(50);
    EN_LOW;
    SysTick_delay_us(50);
}

/// ****| lcdWriteData | ****************************//*
/// * Brief: Send data one nibble at a time to LCD via
/// *          SetNibble macro (see LCD_Library.h)
/// * param:
/// *      (unsigned char) data: 8-bit data to send
/// * return:
/// *      N/A
/// ****************************************************/
void lcdWriteData(unsigned char data) {
    RS_HIGH;
    SysTick_delay_us(50);
    SetNibble(data >> 4);   // Upper nibble
    SysTick_delay_us(50);
    lcdTriggerEN();
    SetNibble(data);        // Lower nibble
    SysTick_delay_us(50);
    lcdTriggerEN();
    SysTick_delay_us(50);
    SetNibble(0x00);        // clear output
}

/// ****| lcdWriteCmd | *****************************//*
/// * Brief: Send command one nibble at a time to LCD
/// *          via SetNibble macro (see LCD_Library.h)
/// * param:
/// *      (unsigned char) cmd: 8-bit command to send
/// * return:
/// *      N/A
/// ****************************************************/
void lcdWriteCmd(unsigned char cmd) {
    RS_LOW;
    SysTick_delay_us(50);
    SetNibble(cmd >> 4);     // Upper nibble
    SysTick_delay_us(50);
    lcdTriggerEN();
    SetNibble(cmd);          // Lower nibble
    SysTick_delay_us(50);
    lcdTriggerEN();
    SysTick_delay_us(50);
    SetNibble(0x00);        // clear output
}

/// ****| lcdSetText | ******************************//*
/// * Brief: Display character string on the LCD at the
/// *          chosen coordinates.
/// * param:
/// *      (char*) text: character string to display
/// *      (int) x:      x-coordinate
/// *      (int) y:      y-coordinate
/// * return:
/// *      N/A
/// ****************************************************/
void lcdSetText(char* text, int x, int y) {
    int i;
    if (x < 16) {
        x |= 0x80;      // Set LCD for first line write
        switch (y){
        case 0:
            x |= 0x00;  // Set LCD for first line write
            break;
        case 1:
            x |= 0x40;  // Set LCD for Second line write
            break;
        case 2:
            x |= 0x10;  // Set LCD for Third line write
            break;
        case 3:
            x |= 0x50;  // Set LCD for Fourth line write
            break;
        case 5:
            x |= 0x20;  // Set LCD for second line write reverse
            break;
        }
        lcdWriteCmd(x);
    }
    i = 0;
    while (text[i] != '\0') {
        lcdWriteData(text[i]);
        i++;
    }
}

/// ****| lcdSetChar | ******************************//*
/// * Brief: Display character on the LCD at the
/// *          chosen coordinates.
/// * param:
/// *      (char) c:     character to display (can be
/// *                       custom character if c = offset
/// *                       of custom character)
/// *      (int) x:      x-coordinate
/// *      (int) y:      y-coordinate
/// * return:
/// *      N/A
/// ****************************************************/
void lcdSetChar(char c, int x, int y) {
    if (x < 16) {
        x |= 0x80;      // Set LCD for first line write
        switch (y){
        case 0:
            x |= 0x00;  // Set LCD for first line write
            break;
        case 1:
            x |= 0x40;  // Set LCD for Second line write
            break;
        case 2:
            x |= 0x10;  // Set LCD for Third line write
            break;
        case 3:
            x |= 0x50;  // Set LCD for Fourth line write
            break;
        case 5:
            x |= 0x20;  // Set LCD for second line write reverse
            break;
        }
        lcdWriteCmd(x);
    }

    lcdWriteData(c);
}

/// ****| lcdSetInt | *******************************//*
/// * Brief: Convert integer into character string to be
/// *          displayed on LCD at chosen coordinates.
/// * param:
/// *      (int) val: value to convert to display
/// *      (int) x:   x-coordinate
/// *      (int) y:   y-coordinate
/// * return:
/// *      N/A
/// ****************************************************/
void lcdSetInt(int val, int x, int y){
    char number_string[16];
    sprintf   (number_string, "%d\0", val); // Convert the integer to character string
    lcdSetText(number_string, x, y);
}

/// ****| lcdCreateCustomChar | **********************//*
/// * Brief: Creates a custom character in CGRAM based on
/// *          character structure passed.
/// * param:
/// *      (custom_char_t)* cc: custom character struct
/// *                             to place in CGRAM
/// * return:
/// *      (uint8_t) _offset:   offset index of new
/// *                               custom char
/// ****************************************************/
uint8_t lcdCreateCustomChar(custom_char_t* cc) {
    lcdWriteCmd(CGRAM+(8*_offset));     // characters placed in intervals of 8 bytes
    lcdWriteData(cc->line0);            // send byte 0 of new character
    lcdWriteData(cc->line1);            // send byte 1 of new character
    lcdWriteData(cc->line2);            // send byte 2 of new character
    lcdWriteData(cc->line3);            // send byte 3 of new character
    lcdWriteData(cc->line4);            // send byte 4 of new character
    lcdWriteData(cc->line5);            // send byte 5 of new character
    lcdWriteData(cc->line6);            // send byte 6 of new character
    lcdWriteData(cc->line7);            // send byte 7 of new character
    return _offset++;                   // return then increment offset value for next character
}


/// ****| lcdClear | ********************************//*
/// * Brief: Clear all visible characters from the
/// *          screen.
/// * param:
/// *      N/A
/// * return:
/// *      N/A
/// ****************************************************/
void lcdClear() {

    lcdWriteCmd(CLEAR);
    SysTick_delay_ms(10);
}

/// ************| Character_init | *********************
/// * Brief: Creates custom characters using structs
/// *        with specific binary numbers that indicates
/// *        specific bits to turn on
/// *
/// * Global Variables:
/// *      Diamond_index, Dollar_index, Stick_person_index
/// * return:
/// *      N/A
/// ****************************************************/
void Character_init(void){

 custom_char_t Diamond_layout = {

            0b00000,
            0b00100,
            0b01110,
            0b11111,
            0b01110,
            0b00100,
            0b00000,
            0b00000
     };

 custom_char_t Dollar_layout = {

           0b00100,
           0b01111,
           0b10100,
           0b01110,
           0b00101,
           0b11110,
           0b00100,
           0b00000
     };

 custom_char_t Stick_Person_layout = {

           0b01110,
           0b01110,
           0b00100,
           0b11111,
           0b00100,
           0b00100,
           0b01010,
           0b10001

     };


 Diamond_index  = lcdCreateCustomChar(&Diamond_layout);             //Sets the address of Diamond_layout into Diamond_index
 Dollar_index  = lcdCreateCustomChar(&Dollar_layout);               //Sets the address of Dollar_layout into Dollar_index
 Stick_Person_index  = lcdCreateCustomChar(&Stick_Person_layout);   //Sets the address of Stick_Person_layout into Stick_Person_index

}

/// *************| Characters | *********************
/// * Brief: Sets initial position of custom characters
/// *        with a good luck message before.
/// *
/// * Global Variables:
/// *     N/A
/// * return:
/// *      N/A
/// ****************************************************/
void Characters(void){

    lcdSetText("GOOD", 0 ,0);
    lcdSetText("LUCK!", 0, 1);
    SysTick_delay_us(1);

    lcdSetChar(Diamond_index, 6, 0);
    lcdSetChar(Stick_Person_index, 8, 0);
    lcdSetChar(Dollar_index, 10, 0);

    lcdSetChar(Diamond_index, 6, 1);
    lcdSetChar(Dollar_index, 8, 1);
    lcdSetChar(Dollar_index, 10, 1);

}
