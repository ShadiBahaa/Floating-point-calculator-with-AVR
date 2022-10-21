/*********************************************************/
/******** Author     : Shadi Bahaa        ****************/
/******** File name  : DIO_INTERFACE.h    ****************/
/******** Date       : 1/10/2022          ****************/
/******** Version    : V5                 ****************/
/******** Desc       : ...                ****************/
/*********************************************************/
/* header guard */
#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_
/* macro for pin output direction */
#define OUTPUT 1
/* macro for pin input direction */
#define INPUT 0
/* macro for pin high value */
#define HIGH 1
/* macro for pin low value */
#define LOW 0
/* macro for port output direction */
#define PORT_OUTPUT 255
/* macro for port input direction */
#define PORT_INPUT 0
/* DIO functions prototypes */
void DIO_VidSetPinDirection(u8 port,u8 pin,u8 dir);
void DIO_VidSetPortDirection(u8 port,u8 dir);
void DIO_VidSetPinValue(u8 port,u8 pin,u8 value);
void DIO_VidSetPortValue(u8 port,u8 value);
s8 DIO_U8GetPinValue(u8 port,u8 pin);
void DIO_VidTogglePinValue(u8 port,u8 pin);
#endif // _DIO_INTERFACE_H_
