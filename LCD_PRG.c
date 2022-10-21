/****************************************************/
/******** Author     : Shadi Bahaa   ****************/
/******** File name  : LCD_PRG.c     ****************/
/******** Date       : 1/10/2022     ****************/
/******** Version    : V5            ****************/
/******** Desc       : ...           ****************/
/****************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_INTERFACE.h"
#include <util/delay.h>
#include "LCD_CFG.h"
//#include <stdio.h>
//#include <stdlib.h>
/* Function used to prepare the LCD for sending commands and data */
void LCD_VidInitialize()
{
    /* RS = 1 (output) */
    DIO_VidSetPinDirection(CONTROL_PORT,RS,OUTPUT);
    /* RW = 1 (output) */
    DIO_VidSetPinDirection(CONTROL_PORT,RW,OUTPUT);
    /* EN = 1 (output) */
    DIO_VidSetPinDirection(CONTROL_PORT,EN,OUTPUT);
    /* Making Data_PORT as the default port for sending data and commands (output) */
    DIO_VidSetPortDirection(DATA_PORT,PORT_OUTPUT);
    _delay_ms(40);
    /* Sending initialization commands */
    LCD_VidSendCommand(FUNCTION_SET);
    _delay_ms(1);
    LCD_VidSendCommand(DISPLAY_ON_OFF);
    _delay_ms(1);
    LCD_VidSendCommand(DESPLAY_CLEAR);
    _delay_ms(3);
}
/* Function used for sending data ascii to LCD
* Options:
* value : range[0-255] (value representing the ascii of the character)
*/
void LCD_VidSendData(u8 value)
{
    /* RS = 1 (data) */
    DIO_VidSetPinValue(CONTROL_PORT,RS,HIGH);
    /* RW = 0 (Write) */
    DIO_VidSetPinValue(CONTROL_PORT,RW,LOW);
    /* Send data Ascii */
    DIO_VidSetPortValue(DATA_PORT,value);
    /* Enable sequence */
    DIO_VidSetPinValue(CONTROL_PORT,EN,HIGH);
    _delay_ms(1);
    DIO_VidSetPinValue(CONTROL_PORT,EN,LOW);
    _delay_ms(1);
}
/* Function used for clearing LCD */
void LCD_VidClearLCD()
{
    LCD_VidSendCommand(DESPLAY_CLEAR);
    _delay_ms(3);
}
/* Function used for shifting LCD Left */
void LCD_VidShiftDisplayLeft()
{
    LCD_VidSendCommand(DESPLAY_LEFT);
}
/* Function used for shifting LCD Right */
void LCD_VidShiftDisplayRight()
{
    LCD_VidSendCommand(DESPLAY_RIGHT);
}
/* Function used for sending command ascii to LCD
* Options:
* value : range[0-255] (value representing the ascii of the instruction)
*/
void LCD_VidSendCommand(u8 command)
{
    /* RS = 0 (command) */
    DIO_VidSetPinValue(CONTROL_PORT,RS,LOW);
    /* RW = 0 (write)*/
    DIO_VidSetPinValue(CONTROL_PORT,RW,LOW);
    /* Send command Ascii */
    DIO_VidSetPortValue(DATA_PORT,command);
    /* Enable sequence */
    DIO_VidSetPinValue(CONTROL_PORT,EN,HIGH);
    _delay_ms(1);
    DIO_VidSetPinValue(CONTROL_PORT,EN,LOW);
    _delay_ms(1);
}
/* Function used for sending a complete string to LCD
* Options:
* arr : character array each character in range[0-255]
*/
void LCD_VidSendString(u8* arr)
{
    u8 index = 0;
    while (arr[index]!='\0')
    {
        /* Sending every letter */
        LCD_VidSendData(arr[index]);
        index++;
    }
}
/* Function used for moving to a specific location on LCD identified by a row and column
* Options:
* row    :  range[1-2]  (specify which line on LCD)
* Column :  range[1-16] (specify which cell on the line)
*/
void LCD_VidMoveTo(u8 row, u8 column)
{
    if (column>=1 && column<=16)
    {
        switch(row)
        {
        case 1:
            /* Setting the DDRAM address to the cell in line 1 */
            LCD_VidSendCommand(column+127);
            break;
        case 2:
            /* Setting the DDRAM address to the cell in line 2 */
            LCD_VidSendCommand(column+191);
        }
    }
    else
    {
        /* Do Nothing */
    }
}
/* Function to reverse a number
 * Input:
 * num: range[(-(2^63))-((2^63)-1)] (number to be reversed)
 * Output:
 * the number in a reversed way
*/
static s64 LCD_S64ReverseNumber(s64 num){
    s64 rev = 1;
    while (num!=0){
        s64 digit = num%10;
        rev = rev*10+digit;
        num/=10;
    }
    return rev;
}
/* Function to send an integer number to LCD
 * Options:
 * num: range[(-(2^63))-((2^63)-1)] (number to be printed)
*/
void LCD_VidSendIntNumber(s64 num)
{
    /* handling negative numbers */
    if (num<0)
    {
        LCD_VidSendData('-');
        num*=-1;
    }
    /* reversing the number */
    if (num==0)
    {
        LCD_VidSendData('0');
        return;
    }
    s64 cur = LCD_S64ReverseNumber(num);
    while (cur!=1)
    {
        /* sending every character to LCD */
        LCD_VidSendData(cur%10+'0');
        cur/=10;
    }
}
/* Function to draw a custom character on LCD using CGRAM
 * options:
 * arr : array of 8 bytes representing the character
 * pos : range[0-7] (each number represents the corresponding block in CGRAM)
 * row : range[1-2] (Rows of LCD Display)
 * col : range[1-16] (Columns of LCD Display)
*/
void LCD_VidDrawChar(u8 arr[], u8 pos, u8 row, u8 col){
    LCD_VidSendCommand(64+8*pos);
    for (u8 i = 0; i<8; ++i){
    	LCD_VidSendData(arr[i]);
    }
    LCD_VidMoveTo(row,col);
    LCD_VidSendData(pos);
}
/* Function to send a floating number to LCD
 * options:
 * num : range[-1.7E-308 - 1.7E+308] (number to be printed)
*/
void LCD_VidSendFloatingNumber(f64 num){
	if (num<0){
		LCD_VidSendData('-');
		num*=-1;
	}
	s64 realPart = num;
	LCD_VidSendIntNumber(realPart);
	LCD_VidSendData('.');
	s64 floaPart = (num-(f64)realPart)*10000.0;
	LCD_VidSendIntNumber(floaPart);
}
