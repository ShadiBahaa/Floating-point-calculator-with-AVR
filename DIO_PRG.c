/****************************************************/
/******** Author     : Shadi Bahaa   ****************/
/******** File name  : DIO_PRG.c     ****************/
/******** Date       : 1/10/2022     ****************/
/******** Version    : V5            ****************/
/******** Desc       : ...           ****************/
/****************************************************/
/* Standard types header */
#include "STD_TYPES.h"
/* Bits mathematical operations header */
#include "BIT_MATH.h"
/* Private DIO info header */
#include "DIO_PRIVATE.h"
/* DIO interfacing info header */
#include "DIO_INTERFACE.h"
/* Function to set a pin to be output or input
 * Options:
 * port: range[0-3] (represents the port character A-D)
 * pin : range[0-7] (represents the pin number 1-8)
 * dir : range[0-1] (0->input , 1->output)
*/
void DIO_VidSetPinDirection(u8 port,u8 pin,u8 dir)
{
    if (INPUT==dir)
    {
        switch (port)
        {
        case 0:
            CLR_BIT(DDRA,pin);
            break;
        case 1:
            CLR_BIT(DDRB,pin);
            break;
        case 2:
            CLR_BIT(DDRC,pin);
            break;
        case 3:
            CLR_BIT(DDRD,pin);
            break;
        }
    }
    else if (OUTPUT==dir)
    {
        switch (port)
        {
        case 0:
            SET_BIT(DDRA,pin);
            break;
        case 1:
            SET_BIT(DDRB,pin);
            break;
        case 2:
            SET_BIT(DDRC,pin);
            break;
        case 3:
            SET_BIT(DDRD,pin);
            break;
        }
    }
    else
    {
        /* Do nothing */
    }
}
/* Function to set port pins' directions to be output or input
 * Options:
 * port: range[0-3] (represents the port character A-D)
 * dir : range[0-255] (each bit in the number represents the state of one pin to be: 0->input or 1->output)
*/
void DIO_VidSetPortDirection(u8 port,u8 dir)
{
    switch (port)
    {
    case 0:
        DDRA=dir;
        break;
    case 1:
        DDRB=dir;
        break;
    case 2:
        DDRC=dir;
        break;
    case 3:
        DDRD=dir;
        break;
    }
}
/* Function to set a pin to be high or low
 * Options:
 * port  : range[0-3] (represents the port character A-D)
 * pin   : range[0-7] (represents the pin number 1-8)
 * value : range[0-1] (0->low , 1->high)
*/
void DIO_VidSetPinValue(u8 port,u8 pin,u8 value)
{

    if (HIGH==value)
    {
        switch (port)
        {
        case 0:
            SET_BIT(PORTA,pin);
            break;
        case 1:
            SET_BIT(PORTB,pin);
            break;
        case 2:
            SET_BIT(PORTC,pin);
            break;
        case 3:
            SET_BIT(PORTD,pin);
            break;
        }
    }
    else if (LOW==value)
    {
        switch (port)
        {
        case 0:
            CLR_BIT(PORTA,pin);
            break;
        case 1:
            CLR_BIT(PORTB,pin);
            break;
        case 2:
            CLR_BIT(PORTC,pin);
            break;
        case 3:
            CLR_BIT(PORTD,pin);
            break;
        }
    }
    else
    {
        /* Do nothing */
    }
}
/* Function to set port values to be high or low
 * Options:
 * port  : range[0-3] (represents the port character A-D)
 * value : range[0-255] (each bit in the number represents the state of one pin to be: 0->low or 1->high)
*/
void DIO_VidSetPortValue(u8 port,u8 value)
{
    switch (port)
    {
    case 0:
        PORTA=value;
        break;
    case 1:
        PORTB=value;
        break;
    case 2:
        PORTC=value;
        break;
    case 3:
        PORTD=value;
        break;
    }
}
/* Function to get a pin value
 * Input:
 * port  : range[0-3] (represents the port character A-D)
 * pin   : range[0-7] (represents the pin number 1-8)
 * Output:
 * 0->low 1->high -1->wrong
*/
s8 DIO_U8GetPinValue(u8 port,u8 pin)
{
    s8 value = -1;
    switch(port)
    {
    case 0:
        value = GET_BIT(PINA,pin);
        break;
    case 1:
        value = GET_BIT(PINB,pin);
        break;
    case 2:
        value = GET_BIT(PINC,pin);
        break;
    case 3:
        value = GET_BIT(PIND,pin);
        break;
    default:
        break;
        /*Do nothing*/
    }
    return value;
}
/* Function to toggle a pin to be high if low or low if high
 * Options:
 * port  : range[0-3] (represents the port character A-D)
 * pin   : range[0-7] (represents the pin number 1-8)
*/
void DIO_VidTogglePinValue(u8 port,u8 pin)
{
    switch (port)
    {
    case 0:
        TOGGLE_BIT(PORTA,pin);
        break;
    case 1:
        TOGGLE_BIT(PORTB,pin);
        break;
    case 2:
        TOGGLE_BIT(PORTC,pin);
        break;
    case 3:
        TOGGLE_BIT(PORTD,pin);
        break;
    }
}
