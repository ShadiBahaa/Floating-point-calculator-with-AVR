/*******************************************************/
/******** Author     : Shadi Bahaa      ****************/
/******** File name  : DIO_PRIVATE.h    ****************/
/******** Date       : 1/10/2022        ****************/
/******** Version    : V5               ****************/
/******** Desc       : ...              ****************/
/*******************************************************/
/* header guard */
#ifndef _DIO_PRIVATE_H_
#define _DIO_PRIVATE_H_
/* Direction registers for ports A,B,C,D */
#define DDRA  *((u8*)0x3A)
#define DDRB  *((u8*)0x37)
#define DDRC  *((u8*)0x34)
#define DDRD  *((u8*)0x31)
/* Output registers for ports A,B,C,D */
#define PORTA *((u8*)0x3B)
#define PORTB *((u8*)0x38)
#define PORTC *((u8*)0x35)
#define PORTD *((u8*)0x32)
/* Input registers for ports A,B,C,D */
#define PINA  *((volatile u8*)0x39)
#define PINB  *((volatile u8*)0x36)
#define PINC  *((volatile u8*)0x33)
#define PIND  *((volatile u8*)0x30)

#endif
