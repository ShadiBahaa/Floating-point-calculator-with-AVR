/**********************************************************/
/******** Author     : Shadi Bahaa         ****************/
/******** File name  : LCD_CFG.h           ****************/
/******** Date       : 1/10/2022           ****************/
/******** Version    : V5                  ****************/
/******** Desc       : ...                 ****************/
/**********************************************************/
/* header guard */
#ifndef _LCD_CFG_H_
#define _LCD_CFG_H_
/*
* The port used for LCD sending data or command
* OPTIONS:
* 0->PORTA 1->PORTB 2->PORTC 3->PORTD
*/
#define DATA_PORT 2
/*
* The port used for LCD controlling
* OPTIONS:
* 0->PORTA 1->PORTB 2->PORTC 3->PORTD
*/
#define CONTROL_PORT 3
/*
* The pin used for LCD register select (1->data - 0->command)
* OPTIONS:
* Range[0-7]->pins
*/
#define RS 0
/*
* The pin used for LCD read/write (1->read - 0->write)
* OPTIONS:
* Range[0-7]->pins
*/
#define RW 1
/*
* The pin used for LCD enable (1->enabled - 0->disabled)
* OPTIONS:
* Range[0-7]->pins
*/
#define EN 2
/* Sets the interface data length, number of lines, and character font
* OPTIONS: (0b001(DL)(N)(F)(-)(-))
* DL (Data length)  : range[0-1] (0->4-bit length    , 1->8-bit length)
* N  (Lines number) : range[0-1] (0->1-line display  , 1->2-lines display)
* DL (char  font)   : range[0-1] (0->5x7 dots        , 1->5x10 dots)
*/
#define FUNCTION_SET 0b00111000
/* Controls the display on/off status, cursor on/off and cursor blink function
* OPTIONS: (0b00001(D)(C)(B))
* D (Display)  : range[0-1] (0->OFF , 1->ON)
* C (Cursor)   : range[0-1] (0->OFF , 1->ON)
* B (Blink)    : range[0-1] (0->OFF , 1->ON)
*/

#define DISPLAY_ON_OFF 0b00001111
/* Clears the entire display */
#define DESPLAY_CLEAR  0b00000001
/* Shifts the cursor position and display to the left without reading or writing
* OPTIONS: (0b0001(S/C)(R/L)(-)(-))
* S/C = 0 and R/L = 0 : cursor shifts to left
* S/C = 0 and R/L = 1 : cursor shifts to right
* S/C = 1 and R/L = 0 : display and cursor shift to left
* S/C = 1 and R/L = 1 : display and cursor shift to right
*/
#define DESPLAY_LEFT  0b00011000
/* Shifts the cursor position and display to the right without reading or writing
* OPTIONS: (0b0001(S/C)(R/L)(-)(-))
* S/C = 0 and R/L = 0 : cursor shifts to left
* S/C = 0 and R/L = 1 : cursor shifts to right
* S/C = 1 and R/L = 0 : display and cursor shift to left
* S/C = 1 and R/L = 1 : display and cursor shift to right
*/
#define DESPLAY_RIGHT 0b00011100
#endif // _LCD_CFG_H_

